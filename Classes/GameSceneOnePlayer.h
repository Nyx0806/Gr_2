#pragma once
#include "GameSceneBase.h"
#include "AIPlayer.h"

class GameSceneOnePlayer : public GameSceneBase {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameSceneOnePlayer);

private:
    AIPlayer* _aiPlayer;

    void onColumnTap(int col) override;
    void performAIMove();
};
