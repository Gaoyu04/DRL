#include "mctsnode.h"

MCTSNode* MCTSNode::select() {
	float max = -FLT_MAX;
	float temp = 0;
	MCTSNode* ans = nullptr;
	for(auto& child:children){
		temp = child.second->get_value();
		if (temp > max) {
			max = temp;
			ans = child.second;
		}
	}
	return ans;
}
float MCTSNode::get_value() {
	float u = c_puct * (0.3 + 0.7 * prior_p) * sqrt(parent->n_visits) / (1 + n_visits);
	return QValue + u;
}
void MCTSNode::update(float value) {
	if (parent != nullptr) {
		parent->update(-value);
	}
	n_visits += 1;
	QValue += 1.0 * (value - QValue) / n_visits;
}
float MCTSNode::expand(Net& net) {
	vector<float> predict = net.predict(state.get_tensor_board())[0];
	vector<vector<int>> all_valid_moves = state.get_all_valid_moves();
	float sum = 0;
	for (auto& v : all_valid_moves) {
		float temp = exp(predict[v[4]]);
		sum += temp;
		ChessState child_state = state;
		child_state.move(v[0], v[1], v[2], v[3]);
		array<int, 5> arr = { v[0], v[1], v[2], v[3], v[4] };
		if (child_state.end){
			for (auto& child : children) {
				delete child.second;
			}
			children.clear();
			children[arr] = new MCTSNode(std::move(child_state), this, 1);
			return -1;
		}
		children[arr] = new MCTSNode(std::move(child_state), this, temp);
	}
	for (auto& child : children) {
		child.second->prior_p /= sum;
	}
	return predict[192];
}

bool MCTSNode::is_leaf() {
	return children.empty();
}

bool MCTSNode::is_root() {
	return (parent == nullptr);
}

MCTSNode::~MCTSNode() {
	for (auto& child : children) {
		delete child.second;
	}
}