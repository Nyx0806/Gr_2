#include "AIPlayer.h"
#include <cstdlib>

AIPlayer::AIPlayer(int difficulty) : Player(2, cocos2d::Color3B::ORANGE), _difficulty(difficulty) {}

int AIPlayer::chooseMove(GameBoard* board) {
    if (_difficulty == 1) {
        return pickRandom(board);
    }

    // C?p ?? 2+ ? ch?n ho?c th?ng
    int win = findWinningMove(board, 2); // ki?m tra AI có th? th?ng
    if (win != -1) return win;

    int block = findWinningMove(board, 1); // ch?n ng??i ch?i
    if (block != -1 && _difficulty >= 2) return block;

    return pickRandom(board); // fallback
}

int AIPlayer::pickRandom(GameBoard* board) {
    std::vector<int> available;
    for (int col = 0; col < MAX_COL; ++col) {
        if (board->getCell(0, col) == 0)
            available.push_back(col);
    }
    if (available.empty()) return -1;
    return available[rand() % available.size()];
}

int AIPlayer::findWinningMove(GameBoard* board, int pid) {
    for (int col = 0; col < MAX_COL; ++col) {
        // gi? l?p n??c ?i
        for (int row = MAX_ROW - 1; row >= 0; --row) {
            if (board->getCell(row, col) == 0) {
                board->dropPiece(col, pid);
                bool win = board->checkWin(row, col, pid);
                board->dropPiece(col, 0); // undo
                if (win) return col;
                break;
            }
        }
    }
    return -1;
}
