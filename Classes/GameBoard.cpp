// IMPLEMENTATION: GameBoard.cpp (m?t ph?n tri?n khai)
#include "GameBoard.h"
using namespace cocos2d;

bool GameBoard::init() {
    if (!Node::init()) return false;

    resetBoard();
    return true;
}

bool GameBoard::dropPiece(int col, int playerId) {
    for (int row = MAX_ROW - 1; row >= 0; --row) {
        if (_board[row][col] == 0) {
            _board[row][col] = playerId;
            return true;
        }
    }
    return false; // C?t ??y
}

int GameBoard::getCell(int row, int col) {
    return _board[row][col];
}

bool GameBoard::checkWin(int lastRow, int lastCol, int playerId) {
    // Ki?m tra t?t c? 4 h??ng: ngang, d?c, chéo /
    return countInDirection(lastRow, lastCol, 1, 0, playerId) + countInDirection(lastRow, lastCol, -1, 0, playerId) > 2 ||
        countInDirection(lastRow, lastCol, 0, 1, playerId) + countInDirection(lastRow, lastCol, 0, -1, playerId) > 2 ||
        countInDirection(lastRow, lastCol, 1, 1, playerId) + countInDirection(lastRow, lastCol, -1, -1, playerId) > 2 ||
        countInDirection(lastRow, lastCol, 1, -1, playerId) + countInDirection(lastRow, lastCol, -1, 1, playerId) > 2;
}

int GameBoard::countInDirection(int row, int col, int dx, int dy, int playerId) {
    int count = 0;
    int r = row + dy, c = col + dx;
    while (r >= 0 && r < MAX_ROW && c >= 0 && c < MAX_COL && _board[r][c] == playerId) {
        ++count;
        r += dy;
        c += dx;
    }
    return count;
}

void GameBoard::resetBoard() {
    for (int r = 0; r < MAX_ROW; ++r)
        for (int c = 0; c < MAX_COL; ++c)
            _board[r][c] = 0;
}
