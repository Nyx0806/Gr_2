#include "UIManager.h"
#include "GameSceneTwoPlayer.h"
#include "StatsScene.h"
#include "GameSceneBase.h"
#include "MainMenuScene.h"
#include "FigmaLayoutHelper.h"
#include "TwoPlayerConfigScene.h"

USING_NS_CC;
using namespace ui;

Scene* TwoPlayerConfigScene::createScene() {
    auto scene = Scene::create();
    auto layer = TwoPlayerConfigScene::create();
    scene->addChild(layer);
    return scene;
}

bool TwoPlayerConfigScene::init() {
    if (!Scene::init()) return false;

    auto size = Director::getInstance()->getVisibleSize();
    Vec2 center = size / 2;
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto background = Sprite::create("image/Main UI/BG.png");
    background->setPosition(size / 2);
    this->addChild(background);

    auto title = Sprite::create("image/Main UI/title.png");
    FigmaLayoutHelper::apply(title, 65, 150, 970, 127);
    title->setAnchorPoint(Vec2(0.0f, 1.0f));
    title->setScale(720.0f / 970.0f);
    this->addChild(title);

    auto subtitle = Sprite::create("image/2 Player Mode/subtitle2.png");
    FigmaLayoutHelper::apply(subtitle, 365, 265, 410, 83);
    subtitle->setScale(0.8f);
    this->addChild(subtitle);

    this->addChild(UIManager::createLabelFigma("PLAYER 1", 26, 55, -260, 230, 70));
    auto nameBg1 = Sprite::create("image/2 Player Mode/namep1_border.png");
    FigmaLayoutHelper::apply(nameBg1, 360, 390, 613, 109);
    nameBg1->setScale(0.7f);
    this->addChild(nameBg1);

    _player1Name = TextField::create("Player 1", "fonts/PoetsenOne-Regular.ttf", 30);
    _player1Name->setPosition(nameBg1->getPosition());
    _player1Name->setTextColor(Color4B::WHITE);
    _player1Name->setMaxLength(10);
    _player1Name->setTextHorizontalAlignment(TextHAlignment::LEFT);
    this->addChild(_player1Name);

    _player1Avatar = Sprite::create("image/2 Player Mode/cam.png");
    _player1Avatar->setAnchorPoint(Vec2(0.0f, 0.5f));
    _player1Avatar->setPosition(Vec2(nameBg1->getPositionX() + nameBg1->getContentSize().width / 2, nameBg1->getPositionY()));
    _player1Avatar->setScale(0.7f);
    this->addChild(_player1Avatar);

    this->addChild(UIManager::createLabelFigma("PLAYER 2", 26, 55, -115, 230, 70));
    auto nameBg2 = Sprite::create("image/2 Player Mode/namep2_border.png");
    FigmaLayoutHelper::apply(nameBg2, 360, 540, 613, 109);
    nameBg2->setScale(0.7f);
    this->addChild(nameBg2);

    _player2Name = TextField::create("Machine", "fonts/PoetsenOne-Regular.ttf", 30);
    _player2Name->setPosition(nameBg2->getPosition());
    _player2Name->setTextColor(Color4B::WHITE);
	_player2Name->setMaxLength(10);
    this->addChild(_player2Name);

    _player2Avatar = Sprite::create("image/2 Player Mode/xanh.png");
    _player2Avatar->setAnchorPoint(Vec2(0.0f, 0.5f));
    _player2Avatar->setPosition(Vec2(nameBg2->getPositionX() + nameBg2->getContentSize().width / 2, nameBg2->getPositionY()));
    _player2Avatar->setScale(0.7f);
    this->addChild(_player2Avatar);

    // --- COLOR SELECTION ---
    this->addChild(UIManager::createLabelFigma("COLOR", 26, 55, 85, 170, 66));

    auto swapBg = Sprite::create("image/2 Player Mode/color_border.png");
    swapBg->setName("colorSwitchBg");
    FigmaLayoutHelper::apply(swapBg, 470, 670, 613, 109);
    swapBg->setScale(0.7f);
    this->addChild(swapBg);

    auto orange = Button::create("image/2 Player Mode/cam.png");
    orange->setPosition(Vec2(65, 65));
    orange->addClickEventListener([=](Ref*) {
        _colorP1 = 1;
        updateColorUI();
        });
    swapBg->addChild(orange,1,"colorP1");

    auto green = Button::create("image/2 Player Mode/xanh.png");
    green->setPosition(Vec2(300, 65));
    green->addClickEventListener([=](Ref*) {
        _colorP1 = 2;
        updateColorUI();
        });
    swapBg->addChild(green,1,"colorP2");

    auto swapBtn = Button::create("image/2 Player Mode/arrow.png");
    swapBtn->setPosition(Vec2(180, 65));
    swapBtn->addClickEventListener([=](Ref*) {
        _colorP1 = (_colorP1 == 1) ? 2 : 1;
        updateColorUI();
        });
    swapBg->addChild(swapBtn);

    // --- FIRST MOVE ---
    this->addChild(UIManager::createLabelFigma("FIRST MOVE", 26, 55,230,298,66));

    auto moveBg = Sprite::create("image/2 Player Mode/color_border.png");
    moveBg->setName("firstMoveBg");
    FigmaLayoutHelper::apply(moveBg, 470, 800, 613, 109);
    moveBg->setScale(0.7f);
    this->addChild(moveBg);

    auto p1 = Sprite::create("image/2 Player Mode/cam.png");
    p1->setPosition(Vec2(65, 65));
    moveBg->addChild(p1, 1, "firstP1");

    auto p2 = Sprite::create("image/2 Player Mode/xanh.png");
    p2->setPosition(Vec2(300, 65));
    moveBg->addChild(p2, 1, "firstP2");

    auto swapMoveBtn = Button::create("image/2 Player Mode/arrow.png");
    swapMoveBtn->setPosition(Vec2(180, 65));
    swapMoveBtn->addClickEventListener([=](Ref*) {
		CCLOG("Swapping first move");
        _firstMove = (_firstMove == 1) ? 2 : 1;
		updateFirstMoveUI();
        });
    moveBg->addChild(swapMoveBtn);

    auto btnP1 = Button::create("image/2 Player Mode/border.png");
    btnP1->setPosition(Vec2(65,65));
    btnP1->addClickEventListener([=](Ref*) {
        _firstMove = 1;
        updateFirstMoveUI();
        });
    moveBg->addChild(btnP1);

    auto btnP2 = Button::create("image/2 Player Mode/border.png");
    btnP2->setPosition(Vec2(300, 65));
    btnP2->addClickEventListener([=](Ref*) {
        _firstMove = 2;
        updateFirstMoveUI();
        });
    moveBg->addChild(btnP2);

    // --- BACK BUTTON ---
    auto back = UIManager::getInstance()->createButton("image/2 Player Mode/back button.png",
        Vec2(center.x - 150, 270),
        [](Ref*) { UIManager::getInstance()->changeScene(MainMenuScene::createScene()); },
        0.6f);
    this->addChild(back);

    // --- START BUTTON ---
    auto start = UIManager::getInstance()->createButton("image/2 Player Mode/start button.png",
        Vec2(center.x + 150, 270),
        [=](Ref*) {
            UIManager::getInstance()->changeScene(GameSceneTwoPlayer::createScene());
        },
        0.6f);
    this->addChild(start);

    updateColorUI();
    updateFirstMoveUI();

    return true;
}

void TwoPlayerConfigScene::updateColorUI() {
    auto colorBg = this->getChildByName("colorSwitchBg");
    if (!colorBg) {
        return;
    }

    auto sprite1 = dynamic_cast<Button*>(colorBg->getChildByName("colorP1"));
    auto sprite2 = dynamic_cast<Button*>(colorBg->getChildByName("colorP2"));    

    if (_colorP1 == 1) {
        sprite1->loadTextureNormal("image/2 Player Mode/camSelect.png");
        sprite2->loadTextureNormal("image/2 Player Mode/xanh.png");
        _player1Avatar->setTexture("image/2 Player Mode/cam.png");
        _player2Avatar->setTexture("image/2 Player Mode/xanh.png");
    }
    else {
        sprite1->loadTextureNormal("image/2 Player Mode/xanhSelect.png");
        sprite2->loadTextureNormal("image/2 Player Mode/cam.png");
        _player1Avatar->setTexture("image/2 Player Mode/xanh.png");
        _player2Avatar->setTexture("image/2 Player Mode/cam.png");
    }
}

void TwoPlayerConfigScene::updateFirstMoveUI() {
    auto firstMoveBg = this->getChildByName("firstMoveBg");
    if (!firstMoveBg) return;

    auto sprite1 = dynamic_cast<Sprite*>(firstMoveBg->getChildByName("firstP1"));
    auto sprite2 = dynamic_cast<Sprite*>(firstMoveBg->getChildByName("firstP2"));

    if (!sprite1 || !sprite2) return;

    if (_firstMove == 1) {
        sprite1->setTexture("image/2 Player Mode/camSelect.png");
        sprite2->setTexture("image/2 Player Mode/xanh.png");
    }
    else {
        sprite1->setTexture("image/2 Player Mode/cam.png");
        sprite2->setTexture("image/2 Player Mode/xanhSelect.png");
    }
}
