#include "AIPlayer.h"
#include <cstdlib>
#include <limits>

AIPlayer::AIPlayer(int difficulty) : Player(2, cocos2d::Color3B::ORANGE), _difficulty(difficulty) {}

int AIPlayer::chooseMove(GameBoard* board) {
    if (_difficulty == 1)
        return pickRandom(board);

    int win = findWinningMove(board, 2);
    if (win != -1) return win;

    int block = findWinningMove(board, 1);
    if (block != -1) return block;

    if (_difficulty == 2)
        return pickCenterPriority(board);

    return minimaxRoot(board, 4);
}

int AIPlayer::pickRandom(GameBoard* board) {
    std::vector<int> available;
    for (int col = 0; col < COLS; ++col) {
        if (board->getCell(0, col) == 0)
            available.push_back(col);
    }
    if (available.empty()) return -1;
    return available[rand() % available.size()];
}

int AIPlayer::findWinningMove(GameBoard* board, int pid) {
    for (int col = 0; col < COLS; ++col) {
        int row = board->simulateDrop(col, pid);
        if (row != -1) {
            bool win = board->checkWin(row, col, pid);
            board->undoDrop(col);
            if (win) return col;
        }
    }
    return -1;
}

int AIPlayer::pickCenterPriority(GameBoard* board) {
    std::vector<int> centerOrder = { 3, 2, 4, 1, 5, 0, 6 };
    for (int col : centerOrder) {
        if (board->getCell(0, col) == 0)
            return col;
    }
    return -1;
}

int AIPlayer::evaluateBoard(GameBoard* board) {
    int aiCount = 0;
    int playerCount = 0;
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            int cell = board->getCell(row, col);
            if (cell == 2) aiCount++;
            else if (cell == 1) playerCount++;
        }
    }
    return aiCount - playerCount;
}

int AIPlayer::minimax(GameBoard* board, int depth, bool maximizingPlayer) {
    if (depth == 0)
        return evaluateBoard(board);

    int bestValue = maximizingPlayer ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();

    for (int col = 0; col < COLS; ++col) {
        int pid = maximizingPlayer ? 2 : 1;
        int row = board->simulateDrop(col, pid);
        if (row != -1) {
            int value = minimax(board, depth - 1, !maximizingPlayer);
            board->undoDrop(col);

            if (maximizingPlayer)
                bestValue = std::max(bestValue, value);
            else
                bestValue = std::min(bestValue, value);
        }
    }
    return bestValue;
}

int AIPlayer::minimaxRoot(GameBoard* board, int depth) {
    int bestScore = std::numeric_limits<int>::min();
    int bestMove = -1;

    for (int col = 0; col < COLS; ++col) {
        int row = board->simulateDrop(col, 2);
        if (row != -1) {
            int score = minimax(board, depth - 1, false);
            board->undoDrop(col);
            if (score > bestScore) {
                bestScore = score;
                bestMove = col;
            }
        }
    }

    return bestMove != -1 ? bestMove : pickRandom(board);
}
