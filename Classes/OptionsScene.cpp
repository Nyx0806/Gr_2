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

	// Lấy kích thuoc man hinh
    auto size = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//Background
    auto background = Sprite::create("image/Main UI/BG.png");
    background->setPosition(size / 2);
    this->addChild(background);

    _soundEnabled = true;
    _materialType = 0;


	// Thiết kế giao diện Options




    return true;
}

void OptionsScene::onSoundToggle() {
    _soundEnabled = !_soundEnabled;
}

void OptionsScene::onMaterialChange() {
    _materialType = (_materialType + 1) % 2;
}