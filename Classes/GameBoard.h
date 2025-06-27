// MODULE 2: GameBoard – X? lý logic bàn c?
#pragma once
#include "cocos2d.h"

#define MAX_ROW 6
#define MAX_COL 7

// L?p qu?n lý logic c?a bàn c? Connect 4
class GameBoard : public cocos2d::Node {
public:
    // Kh?i t?o bàn c?
    virtual bool init();

    // ??t quân vào c?t t??ng ?ng, tr? v? true n?u thành công
    bool dropPiece(int col, int playerId);

    // L?y giá tr? t?i ô (row, col), 0 = r?ng, 1 = player1, 2 = player2
    int getCell(int row, int col);

    // Ki?m tra chi?n th?ng t? v? trí v?a ?ánh
    bool checkWin(int lastRow, int lastCol, int playerId);

    // Reset bàn c? v? tr?ng thái ban ??u
    void resetBoard();

    CREATE_FUNC(GameBoard);

private:
    int _board[MAX_ROW][MAX_COL]; // Ma tr?n l?u tr?ng thái các ô c?
    cocos2d::Sprite* _gridSprites[MAX_ROW][MAX_COL]; // Sprite th? hi?n các ô c?

    // Ki?m tra theo h??ng vector (dx, dy)
    int countInDirection(int row, int col, int dx, int dy, int playerId);
};
