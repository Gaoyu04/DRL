#pragma once

#include <graphics.h>
#include <conio.h>
#include <vector>
#include <string>
#include <iostream>
#include <easyx.h>
using namespace std;

extern IMAGE plate;
extern vector<IMAGE> imgs;

// 棋盘尺寸
extern const int BOARD_ROW;  // 9x10的棋盘
extern const int BOARD_COL;
extern const int CELL_SIZE;  // 每个棋盘格子的尺寸
extern const int BOARD_WIDTH;
extern const int BOARD_HEIGHT; // 10行棋盘

void drawBoard(vector<vector<int>>& board, vector<vector<int>>& valid_moves);
void loadImage();
