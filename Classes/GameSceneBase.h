#pragma once  
#include "cocos2d.h"  
#include "GameBoard.h" // Ensure this include is present and correct  
#include "ui/CocosGUI.h"  


class GameSceneBase : public cocos2d::Scene {  
public:  
    virtual bool initBase();
    virtual void onColumnTap(int col) = 0;

    static void setAIDifficulty(int diff);
    static int getAIDifficulty();
    static void setGameSettings(const std::string& name1, const std::string& name2, int color, int firstMove);
    static int getColorForPlayer(int playerId); // trả về 1 = cam, 2 = xanh
    static std::string getPlayer1Name();
    static std::string getPlayer2Name();
    static int getFirstMove();
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
    static std::string _player2Name; // tên người chơi 1 và 2  
    static int _player1Color;     // 1 = cam, 2 = xanh  
    static int _firstMovePlayer;  // 1 = người, 2 = máy  

    float _timeLeft;  
    

    void checkWin(int lastRow, int lastCol);  
    void switchTurn();
    void startTurnTimer();
    void stopTurnTimer();

    void updatePieceUI();// avatar + tên  
    void showWinPopup(int winnerId);  
};
