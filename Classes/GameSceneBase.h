#pragma once  
#include "cocos2d.h"  
#include "GameBoard.h"  
#include "ui/CocosGUI.h"  

class GameSceneBase : public cocos2d::Scene {
public:
    virtual bool initBase();
    virtual void onColumnTap(int col) = 0;
    static int getPlayer1Color();
    static int getPlayer2Color();
    static int getColorForTurn(int player);
    static int _colorP1;
    static bool _vsAI;
    static bool isVsAI() { return _vsAI; }
    static void setAIDifficulty(int diff);
    static int getAIDifficulty();
    static void setGameSettings(const std::string& name1, const std::string& name2, int color, int firstMove);
    static std::string getPlayer1Name();
    static std::string getPlayer2Name();
    static int getFirstMove();

    static void setPlayerAvatars(const std::string& avatar1, const std::string& avatar2);
    static std::string getPlayer1Avatar();
    static std::string getPlayer2Avatar();

    GameBoard* _board;

protected:
    int _currentPlayer;
    static int _aiDifficulty;

    cocos2d::ui::Text* _nameP1;
    cocos2d::ui::Text* _nameP2;
    cocos2d::ui::Text* _timerLabel;
    cocos2d::Sprite* _avatarP1;
    cocos2d::Sprite* _avatarP2;

    static std::string _player1Name;
    static std::string _player2Name;
    static int _player1Color;
    static int _firstMovePlayer;
    static int _firstMove;

    static std::string _player1Avatar;
    static std::string _player2Avatar;

    float _timeLeft;
    void switchTurn();
    void updatePieceUI();
    void showWinPopup(int winnerId);
};
