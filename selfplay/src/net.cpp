#include <net.h>

Net::Net() {
    const wchar_t* model_path = L"onnxdata/model18.onnx";

    try {
        Ort::Env env(ORT_LOGGING_LEVEL_WARNING, "ONNX_C_API");

        std::wcout << L"Attempting to load model from: " << model_path << std::endl;

        Ort::SessionOptions session_options;
        // Ort::ThrowOnError(OrtSessionOptionsAppendExecutionProvider_CUDA(session_options, 0));
        session_options.SetGraphOptimizationLevel(GraphOptimizationLevel::ORT_ENABLE_ALL);
        session = new Ort::Session(env, model_path, session_options);
        std::wcout << L"Model loaded successfully." << std::endl;

        // 获取输入节点信息并填充到向量中
        input_node_names.push_back("input");
        output_node_names.push_back("policy");
        output_node_names.push_back("value");
    }
    catch (const Ort::Exception& e) {
        // 处理 Ort::Exception 异常
        std::cerr << "Caught Ort::Exception: " << std::string(e.what()) << std::endl;

        // 在异常描述信息中查找错误代码
        size_t pos = std::string(e.what()).find("ErrorCode: ");
        if (pos != std::string::npos) {
            std::string error_code_str = std::string(e.what()).substr(pos + 12); // 12 是 "ErrorCode: " 的长度
            int error_code = std::stoi(error_code_str);
            std::cerr << "Error Code: " << error_code << std::endl;
        }
    }
}

vector<vector<float>> Net::predict(vector<float> input) {
    int batch_size = input.size() / input_size;
    std::vector<int64_t> input_node_dims = { batch_size, 15, 10, 9 };

    // 创建输入张量
    auto memory_info = Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeDefault);
    Ort::Value input_tensor = Ort::Value::CreateTensor<float>(
        memory_info,
        input.data(),
        input.size(),
        input_node_dims.data(),
        input_node_dims.size()
    );

    // 创建输出张量
    std::vector<float> output1_tensor_values(batch_size * output_size1);
    std::vector<int64_t> output1_shape = { batch_size, output_size1 };
    Ort::Value output1_tensor = Ort::Value::CreateTensor<float>(
        memory_info,
        output1_tensor_values.data(),
        output1_tensor_values.size(),
        output1_shape.data(),
        output1_shape.size()
    );
    std::vector<float> output2_tensor_values(batch_size * output_size2);
    std::vector<int64_t> output2_shape = { batch_size, output_size2 };
    Ort::Value output2_tensor = Ort::Value::CreateTensor<float>(
        memory_info,
        output2_tensor_values.data(),
        output2_tensor_values.size(),
        output2_shape.data(),
        output2_shape.size()
    );
    // 执行
    std::vector<Ort::Value> ort_inputs;
    ort_inputs.push_back(std::move(input_tensor));
    std::vector<Ort::Value> output_tensors;
    output_tensors.push_back(std::move(output1_tensor));
    output_tensors.push_back(std::move(output2_tensor));
    // score model & input tensor, get back output tensor
    (*session).Run(
        Ort::RunOptions{ nullptr },
        input_node_names.data(),
        ort_inputs.data(),
        ort_inputs.size(),
        output_node_names.data(),
        output_tensors.data(),
        2
    );
    /*
    for (size_t i = 0; i < output_tensors.size(); ++i) {
        auto output_type_info = (*session).GetOutputTypeInfo(i).GetTensorTypeAndShapeInfo();
        auto output_shape = output_type_info.GetShape();
        size_t output_size = 1;
        for (const auto& dim : output_shape) {
            output_size *= (dim > 0) ? dim : 1;
        }

        const float* output_data = output_tensors[i].GetTensorData<float>();
        std::cout << "Output " << i + 1 << ": ";
        for (size_t j = 0; j < output_size; ++j) {
            std::cout << output_data[j] << " ";
        }
        std::cout << "\n";
    }*/
    
    const float* output_data1 = output_tensors[0].GetTensorData<float>();
    const float* output_data2 = output_tensors[1].GetTensorData<float>(); \
    vector<vector<float>> ans;
    for (int i = 0; i < batch_size; ++i) {
        ans.push_back(vector<float>(output_data1 + i * output_size1, output_data1 + i * output_size1 + output_size1));
        ans[i].push_back(output_data2[i]);
    }
    return ans;
}

Net::~Net() {
    delete session;
}