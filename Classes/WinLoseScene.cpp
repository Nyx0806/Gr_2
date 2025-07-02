#include "WinLoseScene.h"
#include "UIManager.h"
#include "MainMenuScene.h"


using namespace cocos2d;

Scene* WinLoseScene::createScene(bool isWin, int winnerId) {
    auto scene = Scene::create();
    auto layer = WinLoseScene::create(isWin, winnerId);
    if (layer) {
        scene->addChild(layer);
        return scene;
    }
    return nullptr;
}

WinLoseScene* WinLoseScene::create(bool isWin, int winnerId) {
    WinLoseScene* ret = new(std::nothrow) WinLoseScene();
    if (ret && ret->init(isWin, winnerId)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool WinLoseScene::init(bool isWin, int winnerId) {
    if (!Scene::init()) return false;

    auto size = Director::getInstance()->getVisibleSize();
    
	//Thiết kế màn hình Win/Lose

	// Tạo nút về menu

    return true;
}
