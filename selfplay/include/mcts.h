#pragma once

#include <vector>
#include "net.h"
#include "mctsnode.h"
using namespace std;

void softmax(vector<float>& probs);
void DeleteNode(MCTSNode* root);

class MCTS{
public:
	Net& net;
	int n_playout;
	MCTS(Net& net, int n_playout):net(net), n_playout(n_playout){}
	map<array<int, 5>, float> get_move_probs(ChessState state, float temp=0.8);
	void _playout(MCTSNode& root);
};
