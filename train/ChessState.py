from collections import defaultdict
import numpy as np
import copy
import torch
device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")

piece_to_id = {'r':0, 'n':1, 'b':2, 'a':3, 'k':4, 'c':5, 'p':6,
               'R':7, 'N':8, 'B':9, 'A':10, 'K':11, 'C':12, 'P':13}

class ChessState:
    def __init__(self, board=None, red_turn=True):
        # 初始化棋盘和棋子布局
        if board:
            self.board = board
        else :
            self.board = self.create_initial_board()
        self.red_turn = red_turn
        self.end = 0

    def create_initial_board(self):
        """ 创建初始棋盘布局 """
        return [[ 'r', 'n', 'b', 'a', 'k', 'a', 'b', 'n', 'r' ],
                  [ '0', '0', '0', '0', '0', '0', '0', '0', '0' ],
                  [ '0', 'c', '0', '0', '0', '0', '0', 'c', '0' ],
                  [ 'p', '0', 'p', '0', 'p', '0', 'p', '0', 'p' ],
                  [ '0', '0', '0', '0', '0', '0', '0', '0', '0' ],
                  [ '0', '0', '0', '0', '0', '0', '0', '0', '0' ], 
                  [ 'P', '0', 'P', '0', 'P', '0', 'P', '0', 'P' ],
                  [ '0', 'C', '0', '0', '0', '0', '0', 'C', '0' ],
                  [ '0', '0', '0', '0', '0', '0', '0', '0', '0' ],
                  [ 'R', 'N', 'B', 'A', 'K', 'A', 'B', 'N', 'R']]
    
    def move(self, from_row, from_col, to_row, to_col):
        if self.board[to_row][to_col] == 'k':
            self.end = 1
        elif self.board[to_row][to_col] == 'K':
            self.end = 1
        self.board[to_row][to_col] = self.board[from_row][from_col]
        self.board[from_row][from_col] = '0'
        self.red_turn = not self.red_turn
    
    def get_tensor(self):
        data = torch.zeros((15, 10, 9))
        if self.red_turn:
            data[14] = torch.ones(10,9)
        for row in range(10):
            for col in range(9):
                c = self.board[row][col]
                if c!='0':
                    data[piece_to_id[c]][row][col] = 1
        return data.to(device)
