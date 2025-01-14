import copy
import random
import torch
import torch.nn as nn
import numpy as np
from ChessValueNet import ChessValueNet
import torch.nn.functional as F
device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")


class datactrl:
    def __init__(self, filepath):
        self.lstdata = []
        self.loaddata(filepath)
        
    def getstate(self, state):
        state = state.split(" ")
        data = np.zeros((15, 10, 9))
        for i in range(15 * 10 * 9):
            data[i // 90][(i // 9) % 10][i % 9] = int(state[i])
        return data

    def getmove(self, moveprobs):
        moveprobs = moveprobs.split(' ')[:-1]
        all_probs = np.zeros((192))
        i = 0
        while i < len(moveprobs):
            all_probs[int(moveprobs[i])] = float(moveprobs[i+1])
            i += 2
        return all_probs

    def loaddata(self, filepath):
        with open(filepath, 'r') as file:
            state = file.readline()
            while state:
                moveprobs = file.readline()
                value = float(file.readline())
                data = {}
                data["state"] = self.getstate(state)
                data["moveprobs"] = self.getmove(moveprobs)
                data["value"] = value
                self.lstdata.append(data)
                state = file.readline()
    
    def getbatch(self, batchszie):
        batch = random.sample(self.lstdata, batchszie)
        lststates = [data["state"] for data in batch]
        states = np.stack(lststates)
        lstmoves = [data["moveprobs"] for data in batch]
        moves = np.stack(lstmoves)
        values = [data["value"] for data in batch]
        values = np.array(values)
        return states, moves, values
    
    def getlen(self):
        return len(self.lstdata)