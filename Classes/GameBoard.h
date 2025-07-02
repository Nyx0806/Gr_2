#pragma once
#include "cocos2d.h"

#define MAX_ROW 6
#define MAX_COL 7 
#define CELL_SIZE 100

class GameBoard : public cocos2d::Node {
public:
    virtual bool init();
    CREATE_FUNC(GameBoard);

    int dropPiece(int col, int playerId);
    void addPieceSprite(int row, int col, int playerId);
    int getCell(int row, int col) const;
    bool checkWin(int row, int col, int playerId) const;
    void resetBoard();

private:
    int _board[MAX_ROW][MAX_COL];
    cocos2d::Sprite* _gridSprites[MAX_ROW][MAX_COL];
};
