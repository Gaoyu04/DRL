#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include "idtransform.h"
using namespace std;

/* {'r':0, 'n':1, 'b':2, 'a':3, 'k':4, 'c':5, 'p':6,
    'R':7, 'N':8, 'B':9, 'A':10, 'K':11, 'C':12, 'P':13}
    14标记红黑
    -1为空
*/
class ChessState 
{
public:
    vector<vector<int>> board;
    bool red_turn = true;
    bool end = false;

    ChessState(){
        board = { { 0,  1,  2,  3,  4,  3,  2,  1,  0},
                  {-1, -1, -1, -1, -1, -1, -1, -1, -1},
                  {-1,  5, -1, -1, -1, -1, -1,  5, -1},
                  { 6, -1,  6, -1,  6, -1,  6, -1,  6},
                  {-1, -1, -1, -1, -1, -1, -1, -1, -1},
                  {-1, -1, -1, -1, -1, -1, -1, -1, -1},
                  {13, -1, 13, -1, 13, -1, 13, -1, 13},
                  {-1, 12, -1, -1, -1, -1, -1, 12, -1},
                  {-1, -1, -1, -1, -1, -1, -1, -1, -1},
                  { 7,  8,  9, 10, 11, 10,  9,  8,  7}};
    }

    void move(int from_row, int from_col, int to_row, int to_col);
    vector<vector<int>> get_valid_moves(int from_row, int from_col);
    vector<float> get_tensor_board();
    vector<vector<int>> get_all_valid_moves();
};
