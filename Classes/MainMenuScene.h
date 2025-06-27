// MODULE 7: MainMenuScene – Menu chính
#pragma once
#include "cocos2d.h"
class MainMenuScene : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

private:
    void goToOnePlayer(); // Sang chế độ chơi 1 người
    void goToTwoPlayer(); // Sang chế độ chơi 2 người
    void goToStats();     // Xem thống kê
    void goToOptions();   // Tuỳ chọn

    CREATE_FUNC(MainMenuScene);
};
