#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class OnePlayerConfigScene : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(OnePlayerConfigScene);

private:
    cocos2d::ui::TextField* _player1Name;
    cocos2d::Label* _player2Name;
    cocos2d::Sprite* _player1Avatar;
    cocos2d::Sprite* _player2Avatar;
    int _firstMove = 1;      // 1 = người chơi, 2 = máy
    int _colorP1 = 1;        // 1 = cam, 2 = xanh
    int _difficulty = 2;     // 1 = dễ, 2 = TB, 3 = khó
    

    void updateColorUI();
    void updateFirstMoveUI();
    void updateDifficultyByPercent(int percent);

};
