#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class TwoPlayerScene : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(TwoPlayerScene);

private:
    cocos2d::ui::TextField* _player1Name;
    cocos2d::ui::TextField* _player2Name;
    cocos2d::Sprite* _player1Avatar;
    cocos2d::Sprite* _player2Avatar;
    int _firstMove = 1;
    int _colorP1 = 1;
    int _difficulty = 2;

    void updateColorUI();
    void updateFirstMoveUI();
};