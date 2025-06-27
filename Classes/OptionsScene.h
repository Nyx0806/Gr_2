// MODULE 6: OptionsScene – Giao di?n tu? ch?nh
#pragma once
#include "cocos2d.h"
class OptionsScene : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

private:
    void onSoundToggle();     // B?t/t?t âm thanh
    void onMaterialChange();  // ??i hi?u ?ng ch?t li?u c?

    bool _soundEnabled;
    int _materialType;        // 0: nh?a, 1: g?, ...

    CREATE_FUNC(OptionsScene);
};
