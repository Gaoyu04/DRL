#pragma once
#include <unordered_map>
#include "chessstate.h"
#include "net.h"

class MCTSNode {
public:
	ChessState state;
	MCTSNode* parent;
	map<array<int, 5>, MCTSNode*> children = {};
	float c_puct = 1.4;
	int n_visits = 0;
	float QValue = 0;
	float prior_p;
	
	MCTSNode(ChessState state, MCTSNode* parent, float prior_p) :state(state), parent(parent), prior_p(prior_p) {}
	~MCTSNode();
	MCTSNode* select();
	float get_value();
	void update(float value);
	float expand(Net& net);
	bool is_leaf();
	bool is_root();
};
