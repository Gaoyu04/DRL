import torch
import onnx
import onnx.numpy_helper
import numpy as np

# 加载 ONNX 模型
model = onnx.load('data/model4.onnx')

# 进行推理（此时可以用 PyTorch 来加载 ONNX 模型，假设你的模型原本是用 PyTorch 训练的）
import torch.onnx

input_data = np.random.randn(1, 15, 10, 9).astype(np.float32)
# 转换成 PyTorch 模型（若转换）
pytorch_model = torch.onnx._export(model, input_data, 'data4.pth')

# 可以使用 PyTorch 继续推理（仅限 PyTorch 原生支持的转换）
