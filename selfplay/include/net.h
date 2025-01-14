#pragma once
#include <iostream>
#include <assert.h>
#include <onnxruntime_cxx_api.h>
#include <onnxruntime_c_api.h>
#include "chessstate.h"

class Net {
public:
	int input_size = 15 * 10 * 9;
	int output_size1 = 192;
	int output_size2 = 1;
	std::vector<const char*> output_node_names;
	std::vector<const char*> input_node_names;
	Ort::Session* session;
	Net();
	~Net();
	vector<vector<float>> predict(vector<float> input);
};