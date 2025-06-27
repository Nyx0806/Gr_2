#pragma once
#include "cocos2d.h"

class WinLoseScene : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene(bool isWin, int winnerId);
    virtual bool init(bool isWin, int winnerId);

    static WinLoseScene* create(bool isWin, int winnerId);
};
