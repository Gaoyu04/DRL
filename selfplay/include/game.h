#pragma once
#include "chessstate.h"
#include "ui.h"


class Game{
public:
    ChessState state = ChessState();
    MOUSEMSG m;
    bool select = false;
    int selectX, selextY;
    vector<vector<int>> valid_moves;

    Game();

    void play();
    void handleClick(int x, int y);

};
