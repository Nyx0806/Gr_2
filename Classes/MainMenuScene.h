// MODULE 7: MainMenuScene – Menu chính
#pragma once
#include "cocos2d.h"
class MainMenuScene : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

private:
    void goToOnePlayer(cocos2d::Ref* sender); // Sang chế độ chơi 1 người
    void goToTwoPlayer(cocos2d::Ref* sender); // Sang chế độ chơi 2 người
    void goToStats(cocos2d::Ref* sender);     // Xem thống kê
    void goToOptions(cocos2d::Ref* sender);   // Tuỳ chọn

    CREATE_FUNC(MainMenuScene);
};
