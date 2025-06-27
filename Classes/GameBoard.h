// MODULE 2: GameBoard � X? l� logic b�n c?
#pragma once
#include "cocos2d.h"

#define MAX_ROW 6
#define MAX_COL 7

// L?p qu?n l� logic c?a b�n c? Connect 4
class GameBoard : public cocos2d::Node {
public:
    // Kh?i t?o b�n c?
    virtual bool init();

    // ??t qu�n v�o c?t t??ng ?ng, tr? v? true n?u th�nh c�ng
    bool dropPiece(int col, int playerId);

    // L?y gi� tr? t?i � (row, col), 0 = r?ng, 1 = player1, 2 = player2
    int getCell(int row, int col);

    // Ki?m tra chi?n th?ng t? v? tr� v?a ?�nh
    bool checkWin(int lastRow, int lastCol, int playerId);

    // Reset b�n c? v? tr?ng th�i ban ??u
    void resetBoard();

    CREATE_FUNC(GameBoard);

private:
    int _board[MAX_ROW][MAX_COL]; // Ma tr?n l?u tr?ng th�i c�c � c?
    cocos2d::Sprite* _gridSprites[MAX_ROW][MAX_COL]; // Sprite th? hi?n c�c � c?

    // Ki?m tra theo h??ng vector (dx, dy)
    int countInDirection(int row, int col, int dx, int dy, int playerId);
};
