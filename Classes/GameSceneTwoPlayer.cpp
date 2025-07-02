#include "GameSceneTwoPlayer.h"

USING_NS_CC;

Scene* GameSceneTwoPlayer::createScene() {
    auto scene = Scene::create();
    auto layer = GameSceneTwoPlayer::create();
    scene->addChild(layer);
    return scene;
}

bool GameSceneTwoPlayer::init() {
    if (!Scene::init()) return false;

    // ví dụ đơn giản
    auto label = Label::createWithTTF("Two Player Scene", "fonts/PoetsenOne-Regular.ttf", 36);
    label->setPosition(Director::getInstance()->getVisibleSize() / 2);
    this->addChild(label);

    return true;
}
void GameSceneTwoPlayer::onColumnTap(int column) {
    // TODO: xử lý khi người chơi chạm vào cột
    CCLOG("Two Player - Tapped column: %d", column);
}
