#include "StatsScene.h"
#include "StatsManager.h"
#include "UIManager.h"
#include "MainMenuScene.h"

using namespace cocos2d;

Scene* StatsScene::createScene() {
    auto scene = Scene::create();
    auto layer = StatsScene::create();
    scene->addChild(layer);
    return scene;
}

bool StatsScene::init() {
    if (!Scene::init()) return false;

    auto size = Director::getInstance()->getVisibleSize();
    auto stats = StatsManager::getInstance();

    // Thiết kế giao diện Stats
    
    

    // Nút quay lại menu
    

    return true;
}
