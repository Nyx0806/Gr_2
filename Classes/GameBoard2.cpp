#include "GameBoard2.h"
#include "MainMenuScene.h"
#include "GameSceneBase.h"
#include "StatsScene.h"
#include "FigmaLayoutHelper.h"
#include "SoundManager.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

const float paddingX = 15.0f;
const float paddingY = 10;

Scene* GameBoard2::createScene() {
    return GameBoard2::create();
}

bool GameBoard2::init() {
    if (!Scene::init()) return false;
    currentPlayer = GameSceneBase::getFirstMove();

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    float screenWidth = Director::getInstance()->getVisibleSize().width;

    auto avatar1 = Sprite::create(GameSceneBase::getPlayer1Avatar());
    avatar1->setPosition(Vec2(100, 1000));
    avatar1->setScale(0.7);
    this->addChild(avatar1, 1);

    auto avatar2 = Sprite::create(GameSceneBase::getPlayer2Avatar());
    avatar2->setPosition(Vec2(screenWidth - 100, 1000));
    avatar2->setScale(0.7);
    this->addChild(avatar2, 1);

    auto nameLabel1 = ui::Text::create(GameSceneBase::getPlayer1Name(), "fonts/PoetsenOne-Regular.ttf", 32);
    nameLabel1->setAnchorPoint(Vec2(0, 0.5));
    nameLabel1->setPosition(Vec2(150, 1000));
    nameLabel1->setTextColor(Color4B::WHITE);
    nameLabel1->enableOutline(Color4B::BLACK, 2);
    this->addChild(nameLabel1, 1);

    auto nameLabel2 = ui::Text::create(GameSceneBase::getPlayer2Name(), "fonts/PoetsenOne-Regular.ttf", 32);
    nameLabel2->setAnchorPoint(Vec2(1, 0.5));
    nameLabel2->setPosition(Vec2(screenWidth - 150, 1000));
    nameLabel2->setTextColor(Color4B::WHITE);
    nameLabel2->enableOutline(Color4B::BLACK, 2);
    this->addChild(nameLabel2, 1);

    float barHeight = 150;
    auto bar = LayerColor::create(Color4B(30, 0, 40, 255), visibleSize.width, barHeight);
    bar->setPosition(Vec2(origin.x, origin.y));
    this->addChild(bar, 0);

    auto optionButton = Sprite::create("image/Gameplay UI/pause button.png");
    optionButton->setAnchorPoint(Vec2(0.5, 0.5));
    optionButton->setPosition(Vec2(visibleSize.width / 2, origin.y + barHeight / 2));
    addChild(optionButton, 1);

    auto listenner = EventListenerTouchOneByOne::create();
    listenner->setSwallowTouches(true);
    listenner->onTouchBegan = [=](Touch* touch, Event* event) {
        if (optionButton->getBoundingBox().containsPoint(touch->getLocation())) {
            canPlay = false;
            this->showPauseMenu();
            return true;
        }
        return false;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenner, optionButton);

    auto title = Sprite::create("image/Main UI/title.png");
    title->setAnchorPoint(Vec2(0.5, 0.5));
    title->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 50));
    title->setScale(720.0f / 970.0f);
    addChild(title, 0);

    auto bg = Sprite::create("image/Main UI/BG.png");
    bg->setAnchorPoint(Vec2(0.5f, 0.5f));
    bg->setPosition(visibleSize / 2);
    addChild(bg, -1);

    gameplayLayer = Layer::create();
    this->addChild(gameplayLayer, 1);

    auto boardSprite = Sprite::create("image/Gameplay UI/board.png");
    boardSprite->setAnchorPoint(Vec2(0.5f, 0.5f));
    boardSprite->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 30);
    boardSprite->setScaleX(1.3);
    boardSprite->setScaleY(1.3);
    addChild(boardSprite, 2);

    boardOrigin = boardSprite->getPosition() - boardSprite->getContentSize() / 2;
    cellWidth = boardSprite->getContentSize().width / COL;
    cellHeight = boardSprite->getContentSize().height / ROW;

    float totalBoardWidth = COL * cellWidth + (COL - 1) * paddingX;
    boardOrigin.x = (visibleSize.width - totalBoardWidth) / 2;
    float totalBoardHeight = ROW * cellHeight + (ROW - 1) * paddingY;
    boardOrigin.y = (visibleSize.height - totalBoardHeight) / 2;


    // Touch listener
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GameBoard2::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

bool GameBoard2::onTouchBegan(Touch* touch, Event* event) {
    if (!canPlay || gameOver) return false;
    canPlay = false;
    Vec2 touchLocation = touch->getLocation();

    float totalBoardWidth = COL * cellWidth + (COL - 1) * paddingX;
    float totalBoardHeight = ROW * cellHeight + (ROW - 1) * paddingY;

    Rect boardRect(
        boardOrigin.x,
        boardOrigin.y,
        totalBoardWidth,
        totalBoardHeight
    );

    if (boardRect.containsPoint(touchLocation)) {
        int col = (touchLocation.x - boardOrigin.x) / (cellWidth + paddingX);
        if (col >= 0 && col < COL) {
            dropDisc(col, currentPlayer);
            this->scheduleOnce([this](float dt) {
                canPlay = true;
            }, 1.0f, "enable_input_delay");
        }
    }

    return true;
}

Vec2 GameBoard2::getCellPosition(int row, int col) {
    return Vec2(
        boardOrigin.x + col * (cellWidth + paddingX) + cellWidth / 2,
        boardOrigin.y + (ROW - 1 - row) * (cellHeight + paddingY) + cellHeight / 2
    );
}

void GameBoard2::dropDisc(int col, int player) {
    int row = -1;
    for (int r = ROW - 1; r >= 0; --r) {
        if (board[r][col] == 0) {
            row = r;
            break;
        }
    }
    if (row == -1) return;
    board[row][col] = player;

    int colorId = GameSceneBase::getColorForTurn(player);
    std::string discImage = (colorId == 1) ? "image/2 Player Mode/cam.png" : "image/2 Player Mode/xanh.png";
    auto disc = Sprite::create(discImage);
    disc->setScale(0.7);
    disc->setPosition(Vec2(
        boardOrigin.x + col * cellWidth + cellWidth / 2,
        boardOrigin.y + ROW * cellHeight + 100));

    gameplayLayer->addChild(disc, 1);
    SoundManager::getInstance().playClickSound();

    auto moveTo = MoveTo::create(0.3f, getCellPosition(row, col));
    disc->runAction(Sequence::create(
        moveTo,
        CallFunc::create([=]() {
        if (checkWin(player)) {
            CCLOG("Player %d wins!", player);
            gameOver = true;
            std::string resultMessage = StringUtils::format("Player %d Wins!", player);
            showEndGamePanel(resultMessage);
        } else if (isBoardFull()) {
            gameOver = true;
            showEndGamePanel("Draw!");
        } else {
            currentPlayer = 3 - player;
        }
        
    }),
        nullptr
    ));
}

bool GameBoard2::checkWin(int player) {
    for (int row = 0; row < ROW; ++row) {
        for (int col = 0; col <= COL - 4; ++col) {
            if (board[row][col] == player &&
                board[row][col + 1] == player &&
                board[row][col + 2] == player &&
                board[row][col + 3] == player)
                return true;
        }
    }

    for (int col = 0; col < COL; ++col) {
        for (int row = 0; row <= ROW - 4; ++row) {
            if (board[row][col] == player &&
                board[row + 1][col] == player &&
                board[row + 2][col] == player &&
                board[row + 3][col] == player)
                return true;
        }
    }

    for (int row = 0; row <= ROW - 4; ++row) {
        for (int col = 0; col <= COL - 4; ++col) {
            if (board[row][col] == player &&
                board[row + 1][col + 1] == player &&
                board[row + 2][col + 2] == player &&
                board[row + 3][col + 3] == player)
                return true;
        }
    }

    for (int row = 3; row < ROW; ++row) {
        for (int col = 0; col <= COL - 4; ++col) {
            if (board[row][col] == player &&
                board[row - 1][col + 1] == player &&
                board[row - 2][col + 2] == player &&
                board[row - 3][col + 3] == player)
                return true;
        }
    }

    return false;
}

void GameBoard2::showPauseMenu() {
    if (blockOptionButton) return;
    blockOptionButton = true;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 center = visibleSize / 2;

    auto darkLayer = LayerColor::create(Color4B(0, 0, 0, 180));
    addChild(darkLayer, 2);

    auto pauseBG = Sprite::create("image/Pause UI/pauseground.png");
    pauseBG->setPosition(Vec2(center.x, 0));
    pauseBG->setScale(0.3f);
    auto moveToCenter = MoveTo::create(0.5f, center);
    auto easeMove = EaseBounceOut::create(moveToCenter);
    auto scaleUp = ScaleTo::create(0.25, 1.1);
    auto scaleDown = ScaleTo::create(0.25, 0.7);
    auto scaleSequence = Sequence::create(scaleUp, scaleDown, nullptr);
    auto animation = Spawn::createWithTwoActions(easeMove, scaleSequence);
    addChild(pauseBG, 3);

    auto showButtons = CallFunc::create([=]() {
        auto newgameButton = Button::create("image/Pause UI/new game button.png");
        newgameButton->setScale(0.7);
        newgameButton->setPosition(center + Vec2(0, 50));
        newgameButton->addClickEventListener([](Ref*) {
            Director::getInstance()->replaceScene(GameBoard2::createScene());
        });
        addChild(newgameButton, 4);

        auto statsButton = Button::create("image/Pause UI/stats button.png");
        statsButton->setScale(0.7);
        statsButton->setPosition(center + Vec2(0, -50));
        statsButton->addClickEventListener([](Ref*) {
            Director::getInstance()->replaceScene(StatsScene::createScene());
        });
        addChild(statsButton, 4);

        auto btmmButton = Button::create("image/Pause UI/back to main menu button.png");
        btmmButton->setScale(0.7);
        btmmButton->setPosition(center + Vec2(0, -150));
        btmmButton->addClickEventListener([](Ref*) {
            Director::getInstance()->replaceScene(MainMenuScene::createScene());
        });
        addChild(btmmButton, 4);

        auto resumeButton = Button::create("image/Pause UI/resume button.png");
        resumeButton->setScale(0.7);
        resumeButton->setPosition(center + Vec2(0, 150));
        resumeButton->addClickEventListener([=](Ref* sender) {
            this->removeChild(darkLayer);
            this->removeChild(pauseBG);
            this->removeChild(resumeButton);
            this->removeChild(newgameButton);
            this->removeChild(statsButton);
            this->removeChild(btmmButton);
            blockOptionButton = false;
            canPlay = true;
        });
        addChild(resumeButton, 4);
    });
    pauseBG->runAction(Sequence::create(animation, showButtons, nullptr));
}

bool GameBoard2::isBoardFull() {
    for (int col = 0; col < COL; ++col) {
        if (board[0][col] == 0) return false;
    }
    return true;
}

void GameBoard2::showEndGamePanel(const std::string& message) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // Mờ nền
    auto overlay = LayerColor::create(Color4B(0, 0, 0, 180));
    overlay->setPosition(origin);
    this->addChild(overlay, 10);

    // Bảng kết thúc
    auto panel = Sprite::create("image/Pause UI/pauseground.png");
    panel->setScale(0.8f);
    panel->setPosition(visibleSize / 2);
    this->addChild(panel, 11);

    // Label kết quả
    auto label = Label::createWithTTF(message, "fonts/PoetsenOne-Regular.ttf", 50);
    label->setColor(Color3B::YELLOW);
    label->setPosition(panel->getContentSize() / 2 + Size(0, 100));
    label->setAnchorPoint(Vec2(0.5, 0.5));
    panel->addChild(label);

    // Nút chơi lại
    auto againBtn = ui::Button::create("image/Pause UI/new game button.png");
    againBtn->setPosition(panel->getContentSize() / 2 + Size(0, -30));
    againBtn->addClickEventListener([](Ref*) {
        Director::getInstance()->replaceScene(GameBoard2::createScene());
    });
    againBtn->setScale(0.7);
    panel->addChild(againBtn);

    // Nút về menu
    auto menuBtn = ui::Button::create("image/Pause UI/back to main menu button.png");
    menuBtn->setPosition(panel->getContentSize() / 2 + Size(0, -130));
    menuBtn->addClickEventListener([](Ref*) {
        Director::getInstance()->replaceScene(MainMenuScene::createScene());
    });
    menuBtn->setScale(0.7);
    panel->addChild(menuBtn);
}