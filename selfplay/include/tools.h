#pragma once
#include <vector>
#include <iostream>
using namespace std;

vector<vector<int>> GetKingMove(vector<vector<int>>& board, int from_row, int from_col);
vector<vector<int>> GetAdvisorMove(vector<vector<int>>& board, int from_row, int from_col);
vector<vector<int>> GetBishopMove(vector<vector<int>>& board, int from_row, int from_col);
vector<vector<int>> GetKnightMove(vector<vector<int>>& board, int from_row, int from_col);
vector<vector<int>> GetRookMove(vector<vector<int>>& board, int from_row, int from_col);
vector<vector<int>> GetCannonMove(vector<vector<int>>& board, int from_row, int from_col);
vector<vector<int>> GetPawnMove(vector<vector<int>>& board, int from_row, int from_col);

bool check_color(vector<vector<int>>& board, int to_row, int to_col, bool mycolor);
