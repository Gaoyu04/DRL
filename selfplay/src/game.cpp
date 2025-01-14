#include "game.h"

Game::Game(){
    initgraph(BOARD_WIDTH, BOARD_HEIGHT);  // 初始化图形窗口
	loadImage();
}

void Game::play(){
    drawBoard(state.board, valid_moves);
    while (true) {
		m = GetMouseMsg();
        // 获取鼠标点击事件
        if (m.mkLButton) {
            handleClick(m.x, m.y);
		    drawBoard(state.board, valid_moves);
        }
    }

    closegraph();  // 关闭图形窗口
}

void Game::handleClick(int x, int y){
    int board_x = y / 60;
    int board_y = x / 60;
    if(state.board[board_x][board_y]!=-1 && (state.red_turn==(state.board[board_x][board_y]>6))){
        select = true;
        selectX = board_x;
        selextY = board_y;
        valid_moves = state.get_valid_moves(selectX, selextY);
    }
    else if(select){
        vector<int> temp({selectX, selextY, board_x, board_y});
        for(auto v: valid_moves){
            if(v==temp){
                state.move(selectX, selextY, board_x, board_y);
                select = false;
                valid_moves.clear();
                break;
            }
        }
    }
}