#include "game.h"
#include "onnxruntime_cxx_api.h"
#include "net.h"
#include "idtransform.h"
#include "mcts.h"
#include "selfplay.h"


void train() {
    initgraph(BOARD_WIDTH, BOARD_HEIGHT);  // 初始化图形窗口
    loadImage();
    srand((unsigned)(time(NULL)));
    SelfPlay();
}

void play() {
    auto g = Game();
    g.play();
}

void test() {
    Net net = Net();
    MCTS mcts(net, 6000);
    vector<vector<int>> board =
                { { 0,  1,  2,  3,  4,  3,  2,  1,  0},
                  {-1, -1, -1, -1, -1, -1, -1, -1, -1},
                  {-1,  5, -1, -1, -1, -1, -1, -1, -1},
                  { 6, -1,  6, -1,  6, -1,  6, -1,  6},
                  {-1, -1, -1, -1, -1, -1, -1, -1, -1},
                  {-1, -1, -1, -1, -1, -1, -1, -1, -1},
                  {13, -1, 13, -1, 13, -1, 13, -1, 13},
                  {-1, 12, -1, -1, -1, -1, -1, 12,  9},
                  {-1, -1, -1,  8, 10, -1, -1, -1, -1},
                  {-1,  7, -1, 11, -1, 10,  9,  8,  7} };
    vector<vector<int>> empty;
    initgraph(BOARD_WIDTH, BOARD_HEIGHT);  // 初始化图形窗口
    loadImage();
    drawBoard(board, empty);
    auto c = ChessState();
    c.board = board;
    auto state = c.get_tensor_board();
    for (int j = 0; j < state.size(); ++j) {
        cout << int(state[j]) << " ";
    }
    auto ans = net.predict(state);
    auto map = mcts.get_move_probs(c); 
}


int main(){
    InitIdTransform();
    srand((unsigned)(time(0)));
    train();
    return 0;
}