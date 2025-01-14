#include "tools.h"

vector<vector<int>> GetKingMove(vector<vector<int>>& board, int from_row, int from_col){
    vector<vector<int>> ans;
    bool color = (board[from_row][from_col]>6);
    vector<vector<int>> possible_moves = {
        {from_row, from_col, from_row+1, from_col},
        {from_row, from_col, from_row-1, from_col},
        {from_row, from_col, from_row, from_col+1},
        {from_row, from_col, from_row, from_col-1},
    };
    for(auto& v : possible_moves){
        if(v[3]<3 || v[3]>5) continue;
        if((color && v[2]>=7 && v[2]<=9) || (!color && v[2]>=0 && v[2]<=2)){
            if(check_color(board, v[2], v[3], color)){
                ans.push_back(v);
            }
        }
    }
    return ans;
}
vector<vector<int>> GetAdvisorMove(vector<vector<int>>& board, int from_row, int from_col){
    vector<vector<int>> ans;
    bool color = (board[from_row][from_col]>6);
    vector<vector<int>> possible_moves = {
        {from_row, from_col, from_row+1, from_col+1},
        {from_row, from_col, from_row+1, from_col-1},
        {from_row, from_col, from_row-1, from_col+1},
        {from_row, from_col, from_row-1, from_col-1},
    };
    for(auto& v : possible_moves){
        if(v[3]<3 || v[3]>5) continue;
        if((color && v[2]>=7 && v[2]<=9) || (!color && v[2]>=0 && v[2]<=2)){
            if(check_color(board, v[2], v[3], color)){
                ans.push_back(v);
            }
        }
    }
    return ans;
}
vector<vector<int>> GetBishopMove(vector<vector<int>>& board, int from_row, int from_col){
    vector<vector<int>> ans;
    bool color = (board[from_row][from_col]>6);
    vector<vector<int>> possible_moves = {
        {from_row, from_col, from_row+2, from_col+2},
        {from_row, from_col, from_row+2, from_col-2},
        {from_row, from_col, from_row-2, from_col+2},
        {from_row, from_col, from_row-2, from_col-2}
    };
    for(auto& v : possible_moves){
        if(v[3]<0 || v[3]>8) continue;
        if((color && v[2]>=5 && v[2]<=9) || (!color && v[2]>=0 && v[2]<=4)){
            if(board[(v[0]+v[2])/2][(v[1]+v[3])/2] != -1) continue;
            if(check_color(board, v[2], v[3], color)){
                ans.push_back(v);
            }
        }
    }
    return ans;
}
vector<vector<int>> GetKnightMove(vector<vector<int>>& board, int from_row, int from_col){
    vector<vector<int>> ans;
    bool color = (board[from_row][from_col]>6);
    vector<vector<int>> possible_moves = {
        {from_row, from_col, from_row+2, from_col+1},
        {from_row, from_col, from_row+2, from_col-1},
        {from_row, from_col, from_row-2, from_col+1},
        {from_row, from_col, from_row-2, from_col-1},
        {from_row, from_col, from_row+1, from_col+2},
        {from_row, from_col, from_row+1, from_col-2},
        {from_row, from_col, from_row-1, from_col+2},
        {from_row, from_col, from_row-1, from_col-2},
    };
    for(auto& v : possible_moves){
        if(v[2]<0 || v[2]>9 || v[3]<0 || v[3]>8) continue;
        if((abs(v[2]-from_row)==2 && board[(from_row+v[2])/2][from_col]==-1) || 
            (abs(v[3]-from_col)==2 && board[from_row][(from_col+v[3])/2]==-1)){
                if(check_color(board, v[2], v[3], color)){
                    ans.push_back(v);
                }
        }
    }
    return ans;
}
vector<vector<int>> GetRookMove(vector<vector<int>>& board, int from_row, int from_col){
    vector<vector<int>> ans;
    bool color = (board[from_row][from_col]>6);
    for(int i=from_row-1; i>=0; --i){
        if(board[i][from_col] == -1){
            ans.push_back(vector<int>({from_row, from_col, i, from_col}));
        }
        else{
            if((board[i][from_col]>6) != color){
                ans.push_back(vector<int>({from_row, from_col, i, from_col}));
            }
            break;
        }
    }
    for(int i=from_row+1; i<10; ++i){
        if(board[i][from_col] == -1){
            ans.push_back(vector<int>({from_row, from_col, i, from_col}));
        }
        else{
            if((board[i][from_col]>6) != color){
                ans.push_back(vector<int>({from_row, from_col, i, from_col}));
            }
            break;
        }
    }
    for(int i=from_col-1; i>=0; --i){
        if(board[from_row][i] == -1){
            ans.push_back(vector<int>({from_row, from_col, from_row, i}));
        }
        else{
            if((board[from_row][i]>6) != color){
                ans.push_back(vector<int>({from_row, from_col, from_row, i}));
            }
            break;
        }
    }
    for(int i=from_col+1; i<9; ++i){
        if(board[from_row][i] == -1){
            ans.push_back(vector<int>({from_row, from_col, from_row, i}));
        }
        else{
            if((board[from_row][i]>6) != color){
                ans.push_back(vector<int>({from_row, from_col, from_row, i}));
            }
            break;
        }
    }
    return ans;
}
vector<vector<int>> GetCannonMove(vector<vector<int>>& board, int from_row, int from_col){
    vector<vector<int>> ans;
    bool color = (board[from_row][from_col]>6);

    int dx[4] = {-1, 1, 0,  0};
    int dy[4] = { 0, 0, 1, -1};
    for(int d=0; d<4; ++d){
        bool hasJumped = false;
        int nx = from_row+dx[d], ny = from_col+dy[d];
        while(nx>=0 && nx<10 && ny>=0 && ny<9){
            if(board[nx][ny]==-1){
                if(!hasJumped){
                    ans.push_back(vector<int>({from_row, from_col, nx, ny}));
                }
            }
            else {
                if(hasJumped){
                    if(check_color(board, nx, ny, color)){
                        ans.push_back(vector<int>({from_row, from_col, nx, ny}));
                    }
                    break;
                }
                hasJumped = true;
            }
            nx += dx[d];
            ny += dy[d];
        }
    }
    return ans;
}
vector<vector<int>> GetPawnMove(vector<vector<int>>& board, int from_row, int from_col){
    vector<vector<int>> ans;
    bool color = (board[from_row][from_col]>6);

    int forward = 1;
    if(color) forward = -1;
    vector<vector<int>> possible_moves = {
        {from_row, from_col, from_row+forward, from_col}
    };
    if((from_row<=4 && color) || (from_row>=5 && (!color))){
        possible_moves.push_back(vector<int>({from_row, from_col, from_row, from_col+1}));
        possible_moves.push_back(vector<int>({from_row, from_col, from_row, from_col-1}));
    }
    for(auto& v : possible_moves){
        if (v[3] >= 0 && v[3] < 9 && v[2] >= 0 && v[2] < 10) {
            if(check_color(board, v[2], v[3], color)){
                ans.push_back(v);
            }
        }
    }
    return ans;
}

bool check_color(vector<vector<int>>& board, int to_row, int to_col, bool mycolor){
    if((board[to_row][to_col]==-1) || ((board[to_row][to_col]>6)!=mycolor)){
        return true;
    }
    return false;
}