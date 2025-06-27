#include "OptionsScene.h"
#include "UIManager.h"
#include "MainMenuScene.h"

using namespace cocos2d;

Scene* OptionsScene::createScene() {
    auto scene = Scene::create();
    auto layer = OptionsScene::create();
    scene->addChild(layer);
    return scene;
}

bool OptionsScene::init() {
    if (!Scene::init()) return false;

    _soundEnabled = true;
    _materialType = 0;

    auto size = Director::getInstance()->getVisibleSize();

	// Thiết kế giao diện Options




    return true;
}

void OptionsScene::onSoundToggle() {
    _soundEnabled = !_soundEnabled;
}

void OptionsScene::onMaterialChange() {
    _materialType = (_materialType + 1) % 2;
}