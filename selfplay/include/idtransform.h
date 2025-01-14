#pragma once
#include <map>
#include <vector>
#include <array>

extern std::map<int, std::array<int, 4>> id_to_action;
extern std::map<std::array<int, 4>, int> action_to_id;

void InitIdTransform();
std::vector<int> GetActionById(int id);
int GetIdByAction(std::vector<int>& action);