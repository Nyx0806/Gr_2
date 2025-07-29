#pragma once
#include "GameBoard.h"
#include "Player.h"
#include <vector>

class AIPlayer : public Player {
public:
    AIPlayer(int difficulty = 1); // Truyền cấp độ khó khi khởi tạo
    int chooseMove(GameBoard* board); // Chọn nước đi

private:
    int _difficulty;

    // Cấp độ 1
    int pickRandom(GameBoard* board);

    // Cấp độ 2
    int findWinningMove(GameBoard* board, int pid);
    int pickCenterPriority(GameBoard* board);

    // Cấp độ 3
    int minimaxRoot(GameBoard* board, int depth);
    int minimax(GameBoard* board, int depth, bool maximizingPlayer);
    int evaluateBoard(GameBoard* board);
};
