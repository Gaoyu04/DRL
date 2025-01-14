#include "chessstate.h"
#include "tools.h"

void ChessState::move(int from_row, int from_col, int to_row, int to_col){
    if(board[to_row][to_col]==4 || board[to_row][to_col]==11){
        end = true;
    }
    board[to_row][to_col] = board[from_row][from_col];
    board[from_row][from_col] = -1;
    red_turn = !red_turn;
}

vector<vector<int>> ChessState::get_valid_moves(int from_row, int from_col){
    int piece = board[from_row][from_col];
    vector<vector<int>> ans;
    switch(piece%7){
        case 0: // 车
            ans = GetRookMove(board, from_row, from_col);
            break;
        case 1: // 马 
            ans = GetKnightMove(board, from_row, from_col);
            break;
        case 2: // 象
            ans = GetBishopMove(board, from_row, from_col);
            break;
        case 3: // 士
            ans = GetAdvisorMove(board, from_row, from_col);
            break;
        case 4: // 将
            ans = GetKingMove(board, from_row, from_col);
            break;
        case 5: // 炮
            ans = GetCannonMove(board, from_row, from_col);
            break;
        case 6: // 卒
            ans = GetPawnMove(board, from_row, from_col);
            break;
    }
    if (piece == 4) {
        for (auto it = ans.begin(); it != ans.end();) {
            int col = (*it)[3];
            int row;
            for (row = (*it)[2] + 1; row < 10; ++row) {
                if (board[row][col] != -1) {
                    if (board[row][col] == 11) {
                        it = ans.erase(it);
                    }
                    else ++it;
                    break;
                }
            }
            if(row==10) ++it;
        }
        return ans;
    }
    if (piece == 11) {
        for (auto it = ans.begin(); it != ans.end();) {
            int col = (*it)[3];
            int row;
            for (row = (*it)[2] - 1; row >=0; --row) {
                if (board[row][col] != -1) {
                    if (board[row][col] == 4) {
                        it = ans.erase(it);
                    }
                    else ++it;
                    break;
                }
            }
            if(row==-1) ++it;
        }
        return ans;
    }

    bool Bg = false, Rg = false;
    for(int row=from_row-1; row>=0; --row){
        if(board[row][from_col]!=-1){
            if(board[row][from_col]==4){
                Rg = true;
                break;
            }
            else return ans;
        }
    }
    if(!Rg) return ans;
    for(int row=from_row+1; row<10; ++row){
        if(board[row][from_col]!=-1){
            if(board[row][from_col]==11){
                Bg = true;
                break;
            }
            else return ans;
        }
    }
    if(!Bg) return ans;
    for(auto it=ans.begin(); it!=ans.end();){
        if((*it)[3]!=from_col){
            it = ans.erase(it);
        }
        else ++it;
    }
    return ans;
}

vector<vector<int>> ChessState::get_all_valid_moves() {
    vector<vector<int>> ans;
    unordered_map<int, int> count;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 9; ++j) {
            if ((board[i][j] == -1) || (red_turn != (board[i][j] > 6))) continue;
            ++count[board[i][j]];
            vector<int> key = { board[i][j] % 7, count[board[i][j]], 0, 0 };
            vector<vector<int>> temp = get_valid_moves(i, j);
            for (auto& v : temp) {
                key[2] = v[2] - v[0];
                key[3] = v[3] - v[1];
                v.push_back(GetIdByAction(key));
            }
            ans.insert(ans.end(), make_move_iterator(temp.begin()), make_move_iterator(temp.end()));
        }
    }
    return ans;
}

vector<float> ChessState::get_tensor_board() {
    vector<float> ans(15 * 10 * 9, 0);
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (board[i][j] != -1) {
                ans[board[i][j] * 90 + i * 9 + j] = 1;
            }
        }
    }
    if (red_turn) {
        for (int i = 0; i < 90; ++i) {
            ans[14 * 90 + i] = 1;
        }
    }
    return ans;
}