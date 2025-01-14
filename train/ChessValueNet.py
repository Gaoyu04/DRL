import torch
import torch.nn as nn
import torch.nn.functional as F

class ChessValueNet(nn.Module):
    def __init__(self, out_size=192, num_res_blocks=7, num_channels=128):
        super(ChessValueNet, self).__init__()
        self.conv1 = nn.Conv2d(15, num_channels, kernel_size=3, padding=1)
        self.bn1 = nn.BatchNorm2d(num_channels)

        # Residual blocks
        self.res_blocks = nn.ModuleList([
            nn.Sequential(
                nn.Conv2d(num_channels, num_channels, kernel_size=3, padding=1),
                nn.BatchNorm2d(num_channels),
                nn.ReLU(),
                nn.Conv2d(num_channels, num_channels, kernel_size=3, padding=1),
                nn.BatchNorm2d(num_channels)
            ) for _ in range(num_res_blocks)
        ])

        # Policy head
        self.policy_conv = nn.Conv2d(num_channels, 2, kernel_size=1)
        self.policy_bn = nn.BatchNorm2d(2)
        self.policy_fc = nn.Linear(180, out_size)  # 平铺成一个向量

        # Value head
        self.value_conv = nn.Conv2d(num_channels, 1, kernel_size=1)
        self.value_bn = nn.BatchNorm2d(1)
        self.value_fc1 = nn.Linear(90, 128)
        self.value_fc2 = nn.Linear(128, 1)

    def forward(self, x):
        x = F.relu(self.bn1(self.conv1(x)))

        # Residual blocks
        for block in self.res_blocks:
            residual = x
            x = F.relu(block[1](block[0](x)))
            x = block[3](block[2](x))
            x += residual  # Skip connection
            x = F.relu(x)

        # Policy head
        policy = F.relu(self.policy_bn(self.policy_conv(x)))
        policy = policy.view(policy.size(0), -1)
        policy = F.log_softmax(self.policy_fc(policy), dim=1)

        # Value head
        value = F.relu(self.value_bn(self.value_conv(x)))
        value = value.view(value.size(0), -1)
        value = F.relu(self.value_fc1(value))
        value = torch.tanh(self.value_fc2(value))

        return policy, value
