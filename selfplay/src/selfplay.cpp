#include "selfplay.h"


array<int, 5> randomselect(map<array<int, 5>, float> map) {
	float slice = float(rand()) / RAND_MAX;
	float total = 0;
	array<int, 5> SelectedMove = map.begin()->first;
	for (auto& child : map) {
		total += child.second;
		if (total > slice) {
			SelectedMove = child.first;
			break;
		}
	}
	return SelectedMove;
}

void SelfPlay() {
	ChessState start = ChessState();
	ChessState temp;
	Net net = Net();
	MCTS mcts(net, 6000);
	std::ofstream outputFile("data.txt", ios::app);
	for (int i = 0; i < 2000; ++i) {
		temp = start;
		clock_t begin = clock();
		vector<vector<float>> states;
		vector<map<array<int, 5>, float>> allmoveprobs;
		vector<vector<int>> empty;
		for(int t=0; t<250; ++t){
			drawBoard(temp.board, empty);
			auto moveprobs = mcts.get_move_probs(temp);
			auto SelectedMove = randomselect(moveprobs);
			states.push_back(temp.get_tensor_board());
			allmoveprobs.push_back(moveprobs);
			temp.move(SelectedMove[0], SelectedMove[1], SelectedMove[2], SelectedMove[3]);
			if (temp.end) break;
		}

		if (outputFile.is_open()) {
			int win = 0;
			if(temp.end) win = -1;
			for (int i = states.size() - 1; i >= 0; --i) {
				for (int j = 0; j < states[i].size(); ++j) {
					outputFile << int(states[i][j]) << " ";
				}
				outputFile << endl;
				for (auto& moveprobs : allmoveprobs[i]) {
					outputFile << moveprobs.first[4] << " " << moveprobs.second <<" ";
				}
				outputFile << endl << win << endl;
				win *= -1;
			}
		}
		else {
			std::cout << "Failed to open the file." << std::endl; // 如果文件打开失败，输出错误信息
			return;
		}
		cout << "i=" << states.size() << "  time cost: " << static_cast<double>(clock() - begin) / CLOCKS_PER_SEC << endl;
	}
	outputFile.close(); // 关闭文件流
}