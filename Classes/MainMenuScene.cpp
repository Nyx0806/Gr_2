#include "MainMenuScene.h"
#include "OptionsScene.h"
#include "StatsScene.h"
#include "OnePlayerConfigScene.h"
#include "TwoPlayerScene.h"
#include "UIManager.h"
#include "SoundManager.h"
#include "GameBoard.h"
#include "platform/CCFileUtils.h"

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
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Thiết kế Menu chính
	SoundManager::getInstance().playBackgroundMusic("sound/bg_sound.mp3");

	// Tạo nền cho Menu chính
    auto background = Sprite::create("image/Main UI/BG.png");
	background->setPosition(size / 2);
	this->addChild(background);

	//Tao Tiêu đề
    auto title = Sprite::create("image/Main UI/title.png");
    title->setAnchorPoint(Vec2(0.5f, 1.0f));
    title->setScale(0.6f);
    title->setPosition(Vec2(origin.x + size.width / 2, origin.y + size.height - 60));
    this->addChild(title);

	// Tạo nút cho Main Menu
    // Button positions
    float startY = size.height - 300;
    float spacing = 130.0f;
    float scale = 0.6f;

    // CONTINUE
    std::string savePath = FileUtils::getInstance()->getWritablePath() + "saved_game.json";
    if (FileUtils::getInstance()->isFileExist(savePath)) {
        auto btnCon = UIManager::getInstance()->createButton("image/Main UI/continue.png",
            Vec2(size.width / 2, startY - spacing * -1),
            CC_CALLBACK_1(MainMenuScene::goToContinue, this),
            scale);
        this->addChild(btnCon);
    }

    // ONE PLAYER
    auto btnOne = UIManager::getInstance()->createButton("image/Main UI/one player button.png",
        Vec2(size.width / 2, startY),
        CC_CALLBACK_1(MainMenuScene::goToOnePlayer, this),
        scale);
    this->addChild(btnOne);

	// TWO PLAYER
    auto btnTwo = UIManager::getInstance()->createButton("image/Main UI/two player button.png",
        Vec2(size.width / 2, startY - spacing),
        CC_CALLBACK_1(MainMenuScene::goToTwoPlayer, this),
        scale);
    this->addChild(btnTwo);

    // STATS
    auto btnStats = UIManager::getInstance()->createButton("image/Main UI/stat button.png",
        Vec2(size.width / 2, startY - spacing * 2),
        CC_CALLBACK_1(MainMenuScene::goToStats, this),
        scale);
    this->addChild(btnStats);

    // OPTIONS
    auto btnOptions = UIManager::getInstance()->createButton("image/Main UI/option button.png",
        Vec2(size.width / 2, startY - spacing * 3),
        CC_CALLBACK_1(MainMenuScene::goToOptions, this),
        scale);
    this->addChild(btnOptions);


    return true;
}

void MainMenuScene::goToContinue(cocos2d::Ref* sender) {
    auto gameBoard = GameBoard::create();
    if (gameBoard->loadGameState()) {
        auto scene = Scene::create();
        scene->addChild(gameBoard);
        Director::getInstance()->replaceScene(scene);
    }
    else {
        CCLOG("Failed to load saved game");
        // Có thể hiển thị thông báo lỗi hoặc chuyển về game mới
    }
}

void MainMenuScene::goToOnePlayer(cocos2d::Ref* sender) {
    UIManager::getInstance()->changeScene(OnePlayerConfigScene::createScene());
}

void MainMenuScene::goToTwoPlayer(cocos2d::Ref* sender) {
    UIManager::getInstance()->changeScene(TwoPlayerScene::createScene());
}

void MainMenuScene::goToStats(cocos2d::Ref* sender) {
    UIManager::getInstance()->changeScene(StatsScene::createScene());
}

void MainMenuScene::goToOptions(cocos2d::Ref* sender) {
    UIManager::getInstance()->changeScene(OptionsScene::createScene());
}