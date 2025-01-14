#pragma once

#include "chessstate.h"
#include "mcts.h"
#include "selfplay.h"
#include "ui.h"
#include <fstream>

array<int, 5> randomselect(map<array<int, 5>, float> map);
void SelfPlay();