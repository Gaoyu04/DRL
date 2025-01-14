#include "mcts.h"
#include <algorithm>
#include <numeric>

void softmax(vector<float>& probs) {
	float max = *max_element(probs.begin(), probs.end());
	float sum = 0;
	for (auto& x : probs) {
		x = exp(x - max);
		sum += x;
	}
	for (auto& x : probs) {
		x /= sum;
	}
}

map<array<int, 5>, float> MCTS::get_move_probs(ChessState state, float temp) {
	MCTSNode root(state, nullptr, 1);
	for (int i = 0; i < n_playout; ++i) {
		_playout(root);
	}
	map<array<int, 5>, float> move_probs;
	vector<array<int, 5>> moves;
	vector<float> probs;
	for(auto& child:root.children){
		moves.push_back(child.first);
		probs.push_back(1/temp * log(child.second->n_visits + 1e-10));
	}
	softmax(probs);
	for (int i = 0; i < moves.size(); ++i) {
		move_probs[moves[i]] = probs[i];
	}
	return move_probs;
}

void MCTS::_playout(MCTSNode& root) {
	MCTSNode* node = &root;
	while (1) {
		if (node->is_leaf()) break;
		node = node->select();
	}
	float leaf_value = 0;
	if (node->state.end) {
		leaf_value = 1;
	}
	else {
		leaf_value = node->expand(net);
	}
	node->update(leaf_value);
}


void DeleteNode(MCTSNode* root) {
	for (auto& child : root->children) {
		DeleteNode(child.second);
	}
	delete root;
}
