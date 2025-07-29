#pragma once

#include "cocos2d.h"

const int ROW = 6;
const int COL = 7;

class GameBoard2 : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    bool isBoardFull();
    void showEndGamePanel(const std::string& message);
    CREATE_FUNC(GameBoard2);

private:
    cocos2d::Vec2 boardOrigin;
    float cellWidth;
    float cellHeight;
    bool canPlay = true;
    bool gameOver = false;
    int currentPlayer = 1;
    int board[ROW][COL] = { 0 };
    bool blockOptionButton = false;

    cocos2d::Layer* gameplayLayer;

    cocos2d::Vec2 getCellPosition(int row, int col);
    void showPauseMenu();
    void dropDisc(int col, int player);
    bool checkWin(int player);
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
};
