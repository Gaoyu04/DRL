import torch
from ChessValueNet import ChessValueNet
from ChessState import ChessState
import onnxruntime
device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")
import numpy as np

policy_value_net = ChessValueNet().to(device)
policy_value_net.load_state_dict(torch.load("data/data18.pth"))


policy_value_net.eval()

torch.onnx.export(
        policy_value_net,
        ChessState().get_tensor().unsqueeze(0),
        "model18.onnx",
        input_names=['input'],
        output_names=['policy', 'value'],
        dynamic_axes = {'input':
                            {0: 'batch_size'},
                       'policy':
                            {0: 'batch_size'},
                       'value':
                            {0: 'batch_size'}
                       }
        )