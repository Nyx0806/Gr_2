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
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto stats = StatsManager::getInstance();

    //Background
    auto background = Sprite::create("image/Main UI/BG.png");
    background->setPosition(size / 2);
    this->addChild(background);

    // Thiết kế giao diện Stats
    
    

    // Nút quay lại menu
    

    return true;
}
