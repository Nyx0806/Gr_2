#include "MainMenuScene.h"
#include "GameScene.h"
#include "OptionsScene.h"
#include "StatsScene.h"
#include "UIManager.h"

using namespace cocos2d;

Scene* MainMenuScene::createScene() {
    auto scene = Scene::create();
    auto layer = MainMenuScene::create();
    scene->addChild(layer);
    return scene;
}

bool MainMenuScene::init() {
    if (!Scene::init()) return false;

    auto size = Director::getInstance()->getVisibleSize();
    // Thiết kế Menu chính





    return true;
}

void MainMenuScene::goToOnePlayer() {
    Director::getInstance()->replaceScene(GameScene::createScene(GameMode::ONE_PLAYER));
}

void MainMenuScene::goToTwoPlayer() {
    Director::getInstance()->replaceScene(GameScene::createScene(GameMode::TWO_PLAYER));
}

void MainMenuScene::goToStats() {
    Director::getInstance()->replaceScene(StatsScene::createScene());
}

void MainMenuScene::goToOptions() {
    Director::getInstance()->replaceScene(OptionsScene::createScene());
}