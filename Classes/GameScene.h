#pragma once
#include "cocos2d.h"
#include "GameBoard.h"
#include "Player.h"

enum class GameMode {
    ONE_PLAYER,
    TWO_PLAYER
};

class GameScene : public cocos2d::Scene {
public:
    // T?o m?t scene m?i d?a tr�n ch? ?? ch?i (1 ng??i / 2 ng??i)
    static cocos2d::Scene* createScene(GameMode mode);

    // Kh?i t?o m�n ch?i
    virtual bool init();

    // Callback khi ng??i ch?i ch?n m?t c?t ?? ?�nh
    void onColumnTapped(int col);

    // C?p nh?t giao di?n b�n c? sau khi ng??i ch?i ?�nh
    void updateBoard();

    // Ki?m tra ?i?u ki?n chi?n th?ng sau m?i l??t
    void checkWinCondition();

    // Reset l?i b�n c? v� l??t ch?i
    void resetGame();

    CREATE_FUNC(GameScene);

private:
    GameMode _mode;               // Ch? ?? ch?i: 1 ng??i hay 2 ng??i
    Player* _player1;             // Ng??i ch?i 1 (ho?c ng??i ch?i ch�nh trong ch? ?? 1 ng??i)
    Player* _player2;             // Ng??i ch?i 2 (ho?c AI trong ch? ?? 1 ng??i)
    GameBoard* _board;           // Logic b�n c?
    int _currentTurn;            // X�c ??nh l??t ch?i hi?n t?i (0 ho?c 1)
};
