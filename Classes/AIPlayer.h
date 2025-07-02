#pragma once
#include "GameBoard.h"
#include "Player.h"
#include <vector>

class AIPlayer : public Player {
public:
    AIPlayer(int difficulty = 1); // truy?n ?? khó khi kh?i t?o
    int chooseMove(GameBoard* board); // quy?t ??nh n??c ?i

private:
    int _difficulty;

    int pickRandom(GameBoard* board);
    int findWinningMove(GameBoard* board, int pid);
};
