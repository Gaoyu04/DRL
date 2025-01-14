import torch
from ChessState import ChessState
from ChessValueNet import ChessValueNet
from datactrl import datactrl
import torch.nn.functional as F
device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")

# 训练函数
def train():
    data = datactrl("data/data35.txt")
    #for i in range(13,37):
    #    data.loaddata(f"data/data{i}.txt")
    data.loaddata(f"data/data36.txt")
    policy_value_net = ChessValueNet().to(device)
    policy_value_net.load_state_dict(torch.load("data/data17.pth"))
    optimizer = torch.optim.Adam(params=policy_value_net.parameters(), lr=1e-3, betas=(0.9, 0.999), eps=1e-8)
    batchsize = 64
    print(data.getlen(), data.getlen()//batchsize)
    for eposide in range(100):
        allloss1 = 0
        allloss2 = 0
        for i in range(data.getlen() // batchsize):
           
            state_batch, probs, values = data.getbatch(batchsize)
            state_batch = torch.tensor(state_batch, dtype=torch.float32).to(device)
            mcts_probs = torch.tensor(probs, dtype=torch.float32).to(device)
            winner_batch = torch.tensor(values, dtype=torch.float32).to(device)
            # 清零梯度
            optimizer.zero_grad()
            # 前向运算
            log_act_probs, value = policy_value_net(state_batch)
            value = torch.reshape(x=value, shape=[-1])
            # 价值损失
            value_loss = F.mse_loss(input=value, target=winner_batch)
            # 策略损失
            policy_loss = -torch.mean(torch.sum(mcts_probs * log_act_probs, dim=1))  # 希望两个向量方向越一致越好
            # 总的损失，注意l2惩罚已经包含在优化器内部
            loss = value_loss + policy_loss
            # 反向传播及优化
            loss.backward()
            optimizer.step()
            allloss1 += value_loss.item()
            allloss2 += policy_loss.item()
        print("epoch: %d, loss: %f  %f" % (eposide, allloss1/i, allloss2/i))
    torch.save(policy_value_net.state_dict(), "data/data19.pth")

train()
