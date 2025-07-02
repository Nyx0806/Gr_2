#pragma once
#include "GameSceneBase.h"

class GameSceneTwoPlayer : public GameSceneBase {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameSceneTwoPlayer);

private:
    void onColumnTap(int col) override;
};