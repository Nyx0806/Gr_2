#include "GameBoard.h"
#include "MainMenuScene.h"
#include "GameSceneBase.h"
#include "StatsScene.h"
#include "StatsManager.h"
#include "SoundManager.h"
#include "FigmaLayoutHelper.h"
#include "ui/CocosGUI.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "platform/CCFileUtils.h"


USING_NS_CC;
using namespace ui;

const float paddingX = 15.0f;
const float paddingY = 10;

Scene* GameBoard::createScene() {
    return GameBoard::create();
}

bool GameBoard::init() {
    if (!Scene::init()) return false;

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    float screenWidth = Director::getInstance()->getVisibleSize().width;

    //Khởi tạo board với giá trị 0
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                board[i][j] = 0;
            }
        }

    // Load stats khi khởi tạo scene
    StatsManager::getInstance()->loadStats();

    std::string avatar1Path = GameSceneBase::getPlayer1Avatar();
    auto avatar1 = Sprite::create(GameSceneBase::getPlayer1Avatar());
    if (!avatar1) {
        CCLOG("⚠ Avatar1 failed to load: %s", avatar1Path.c_str());
        return false;
    }
    avatar1->setPosition(Vec2(100, 1000));
	avatar1->setScale(0.7);
    this->addChild(avatar1, 1);

    std::string avatar2Path = GameSceneBase::getPlayer2Avatar();
    auto avatar2 = Sprite::create(GameSceneBase::getPlayer2Avatar());
    if (!avatar2) {
        CCLOG("⚠ Avatar2 failed to load: %s", avatar2Path.c_str());
        return false;
    }
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
    FigmaLayoutHelper::apply(title, 65, 150, 970, 127);
    title->setAnchorPoint(Vec2(0.0f, 1.0f));
    title->setScale(720.0f / 970.0f);
    this->addChild(title);

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
    cellWidth = boardSprite->getContentSize().width / COLS;
    cellHeight = boardSprite->getContentSize().height / ROWS;

    float totalBoardWidth = COLS * cellWidth + (COLS - 1) * paddingX;
    boardOrigin.x = (visibleSize.width - totalBoardWidth) / 2;
    float totalBoardHeight = ROWS * cellHeight + (ROWS - 1) * paddingY;
    boardOrigin.y = (visibleSize.height - totalBoardHeight) / 2;

	currentPlayer = GameSceneBase::getFirstMove();
    if (GameSceneBase::isVsAI() && GameSceneBase::getFirstMove() == 2) {
        this->scheduleOnce([this](float dt) {
            runAI();
        }, 0.2f, "ai_starts");
    }

    // Touch listener
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GameBoard::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

bool GameBoard::onTouchBegan(Touch* touch, Event* event) {
    if (!canPlay || gameOver) return false;
    canPlay = false;
    Vec2 touchLocation = touch->getLocation();

    float totalBoardWidth = COLS * cellWidth + (COLS - 1) * paddingX;
    float totalBoardHeight = ROWS * cellHeight + (ROWS - 1) * paddingY;

    Rect boardRect(
        boardOrigin.x,
        boardOrigin.y,
        totalBoardWidth,
        totalBoardHeight
    );

    if (boardRect.containsPoint(touchLocation)) {
        int col = (touchLocation.x - boardOrigin.x) / (cellWidth + paddingX);
        if (col >= 0 && col < COLS) {
            dropDisc(col, currentPlayer);
            this->scheduleOnce([this](float dt) {
                canPlay = true;
            }, 1.0f, "enable_input_delay");
        }
    }

    return true;
}

Vec2 GameBoard::getCellPosition(int row, int col) {
    return Vec2(
        boardOrigin.x + col * (cellWidth + paddingX) + cellWidth / 2,
        boardOrigin.y + (ROWS - 1 - row) * (cellHeight + paddingY) + cellHeight / 2
    );
}

void GameBoard::dropDisc(int col, int player) {
    int row = -1;
    for (int r = ROWS - 1; r >= 0; --r) {
        if (board[r][col] == 0) {
            row = r;
            break;
        }
    }
    if (row == -1) return;
    board[row][col] = player;

    int colorId = (player == 1) ? GameSceneBase::getPlayer1Color()
                                : GameSceneBase::getPlayer2Color();
    std::string discImage = (colorId == 1) ? "image/1 Player Mode/cam.png" : "image/1 Player Mode/xanh.png";
    auto disc = Sprite::create(discImage);
    disc->setScale(0.7);
    disc->setPosition(Vec2(
        boardOrigin.x + col * cellWidth + cellWidth / 2,
        boardOrigin.y + ROWS * cellHeight + 100));

    gameplayLayer->addChild(disc, 1);

    SoundManager::getInstance().playClickSound();

    auto moveTo = MoveTo::create(0.3f, getCellPosition(row, col));
    disc->runAction(Sequence::create(
        moveTo,
        CallFunc::create([=]() {
        if (checkWin(player)) {
            CCLOG("Player %d wins!", player);
            gameOver = true;
            StatsManager::getInstance()->recordWin(player);
            StatsManager::getInstance()->saveStats();
            
            // xóa file save sau khi over
            std::string filePath = FileUtils::getInstance()->getWritablePath() + "saved_game.json";
            if (FileUtils::getInstance()->isFileExist(filePath)) {
                FileUtils::getInstance()->removeFile(filePath);
            }

            std::string resultMessage;
            if (vsAI) {
                resultMessage = (player == 1) ? "You Win!" : "You Lose!";
            }
            else {
                resultMessage = StringUtils::format("Player %d Wins!", player);
            }

            showEndGamePanel(resultMessage);
        }
        else if (isBoardFull()) {
            CCLOG("Game is a draw!");
            gameOver = true;
            StatsManager::getInstance()->recordDraw();
            StatsManager::getInstance()->saveStats();
            showEndGamePanel("Draw!");

            std::string filePath = FileUtils::getInstance()->getWritablePath() + "saved_game.json";
            if (FileUtils::getInstance()->isFileExist(filePath)) {
                FileUtils::getInstance()->removeFile(filePath);
            }
        }
        else if (vsAI && player == 1 && !gameOver) {
            this->runAI();
        }
        currentPlayer = 3 - player;
    }),
        nullptr
    ));
}

void GameBoard::showEndGamePanel(const std::string& message) {
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
    auto label = Label::createWithSystemFont(message, "fonts/PoetsenOne-Regular.ttf", 50);
    label->setColor(Color3B::YELLOW);
    label->setPosition(panel->getContentSize() / 2 + Size(0, 100));
    label->setAnchorPoint(Vec2(0.5, 0.5));
    panel->addChild(label);

    // Nút chơi lại
    auto againBtn = ui::Button::create("image/Pause UI/new game button.png");
    againBtn->setPosition(panel->getContentSize() / 2 + Size(0, -30));
    againBtn->addClickEventListener([](Ref*) {
        Director::getInstance()->replaceScene(GameBoard::createScene());
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


void GameBoard::runAI() {
    std::vector<int> validCols;
    for (int col = 0; col < COLS; ++col) {
        if (board[0][col] == 0) {
            validCols.push_back(col);
        }
    }

    if (!validCols.empty()) {
        int chosenCol = validCols[rand() % validCols.size()];
        dropDisc(chosenCol, 2);
    }
}

bool GameBoard::checkWin(int player) {
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col <= COLS - 4; ++col) {
            if (board[row][col] == player &&
                board[row][col + 1] == player &&
                board[row][col + 2] == player &&
                board[row][col + 3] == player)
                return true;
        }
    }

    for (int col = 0; col < COLS; ++col) {
        for (int row = 0; row <= ROWS - 4; ++row) {
            if (board[row][col] == player &&
                board[row + 1][col] == player &&
                board[row + 2][col] == player &&
                board[row + 3][col] == player)
                return true;
        }
    }

    for (int row = 0; row <= ROWS - 4; ++row) {
        for (int col = 0; col <= COLS - 4; ++col) {
            if (board[row][col] == player &&
                board[row + 1][col + 1] == player &&
                board[row + 2][col + 2] == player &&
                board[row + 3][col + 3] == player)
                return true;
        }
    }

    for (int row = 3; row < ROWS; ++row) {
        for (int col = 0; col <= COLS - 4; ++col) {
            if (board[row][col] == player &&
                board[row - 1][col + 1] == player &&
                board[row - 2][col + 2] == player &&
                board[row - 3][col + 3] == player)
                return true;
        }
    }

    return false;
}

bool GameBoard::isBoardFull() {
    for (int col = 0; col < COLS; ++col) {
        if (board[0][col] == 0)
            return false;
    }
    return true;
}

int GameBoard::simulateDrop(int col, int pid) {
    for (int r = ROWS - 1; r >= 0; --r) {
        if (board[r][col] == 0) {
            board[r][col] = pid;
            return r;
        }
    }
    return -1;
}

void GameBoard::undoDrop(int col) {
    for (int r = 0; r < ROWS; ++r) {
        if (board[r][col] != 0) {
            board[r][col] = 0;
            break;
        }
    }
}

int GameBoard::getCell(int row, int col) const {
    return board[row][col];
}

bool GameBoard::checkWin(int row, int col, int player) const {
    GameBoard* temp = const_cast<GameBoard*>(this);
    temp->board[row][col] = player;
    return temp->checkWin(player);
}



void GameBoard::showPauseMenu() {
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
        Director::getInstance()->replaceScene(GameBoard::createScene());
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
    btmmButton->addClickEventListener([this](Ref*) {
        this->saveGameState();
        Director::getInstance()->replaceScene(MainMenuScene::createScene());
    });
    btmmButton->setPosition(center + Vec2(0, -150));
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

// Lưu thông tin ván cờ
void GameBoard::saveGameState() {
    rapidjson::Document doc;
    doc.SetObject();
    auto& alloc = doc.GetAllocator();

    // Lưu trạng thái board
    rapidjson::Value boardArr(rapidjson::kArrayType);
    for (int i = 0; i < ROWS; ++i) {
        rapidjson::Value rowArr(rapidjson::kArrayType);
        for (int j = 0; j < COLS; ++j) {
            rowArr.PushBack(board[i][j], alloc);
        }
        boardArr.PushBack(rowArr, alloc);
    }

    doc.AddMember("board", boardArr, alloc);
    doc.AddMember("currentPlayer", currentPlayer, alloc);
    doc.AddMember("gameOver", gameOver, alloc);
    doc.AddMember("vsAI", vsAI, alloc);

    // Lưu thông tin player
    doc.AddMember("player1Name", rapidjson::Value(GameSceneBase::getPlayer1Name().c_str(), alloc), alloc);
    doc.AddMember("player2Name", rapidjson::Value(GameSceneBase::getPlayer2Name().c_str(), alloc), alloc);
    doc.AddMember("player1Avatar", rapidjson::Value(GameSceneBase::getPlayer1Avatar().c_str(), alloc), alloc);
    doc.AddMember("player2Avatar", rapidjson::Value(GameSceneBase::getPlayer2Avatar().c_str(), alloc), alloc);
    doc.AddMember("player1Color", GameSceneBase::getPlayer1Color(), alloc);
    doc.AddMember("player2Color", GameSceneBase::getPlayer2Color(), alloc);
    doc.AddMember("firstMove", GameSceneBase::getFirstMove(), alloc);
    doc.AddMember("difficulty", GameSceneBase::getAIDifficulty(), alloc);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    std::string filePath = FileUtils::getInstance()->getWritablePath() + "saved_game.json";
    FILE* file = fopen(filePath.c_str(), "w");
    if (file) {
        fputs(buffer.GetString(), file);
        fclose(file);
        CCLOG("Game saved to %s", filePath.c_str());
    }
    else {
        CCLOG("Failed to save game to %s", filePath.c_str());
    }
}
// Load ván cờ
bool GameBoard::loadGameState() {
    std::string filePath = FileUtils::getInstance()->getWritablePath() + "saved_game.json";
    if (!FileUtils::getInstance()->isFileExist(filePath)) {
        CCLOG("No saved game file found");
        return false;
    }

    std::string content = FileUtils::getInstance()->getStringFromFile(filePath);
    if (content.empty()) {
        CCLOG("Saved game file is empty");
        return false;
    }

    rapidjson::Document doc;
    doc.Parse(content.c_str());

    if (doc.HasParseError() || !doc.IsObject()) {
        CCLOG("Error parsing saved game JSON");
        return false;
    }

    // Load board state
    if (doc.HasMember("board") && doc["board"].IsArray()) {
        auto boardArr = doc["board"].GetArray();
        for (int i = 0; i < ROWS && i < (int)boardArr.Size(); ++i) {
            if (boardArr[i].IsArray()) {
                auto row = boardArr[i].GetArray();
                for (int j = 0; j < COLS && j < (int)row.Size(); ++j) {
                    if (row[j].IsInt()) {
                        board[i][j] = row[j].GetInt();
                    }
                }
            }
        }
    }

    // Load game state
    if (doc.HasMember("currentPlayer") && doc["currentPlayer"].IsInt()) {
        currentPlayer = doc["currentPlayer"].GetInt();
    }

    if (doc.HasMember("gameOver") && doc["gameOver"].IsBool()) {
        gameOver = doc["gameOver"].GetBool();
    }

    if (doc.HasMember("vsAI") && doc["vsAI"].IsBool()) {
        vsAI = doc["vsAI"].GetBool();
    }

    // Load player settings
    if (doc.HasMember("player1Name") && doc["player1Name"].IsString() &&
        doc.HasMember("player2Name") && doc["player2Name"].IsString() &&
        doc.HasMember("player1Color") && doc["player1Color"].IsInt() &&
        doc.HasMember("firstMove") && doc["firstMove"].IsInt()) {

        GameSceneBase::setGameSettings(
            doc["player1Name"].GetString(),
            doc["player2Name"].GetString(),
            doc["player1Color"].GetInt(),
            doc["firstMove"].GetInt()
        );
    }

    if (doc.HasMember("difficulty") && doc["difficulty"].IsInt()) {
        GameSceneBase::setAIDifficulty(doc["difficulty"].GetInt());
    }

    // Recreate visual representation of loaded board
    this->scheduleOnce([this](float dt) {
        this->recreateBoard();
        }, 0.1f, "recreate_board");

    return true;
}

void GameBoard::recreateBoard() {
    // Clear existing discs
    gameplayLayer->removeAllChildren();

    // Recreate discs based on loaded board state
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            if (board[row][col] != 0) {
                int player = board[row][col];
                int colorId = (player == 1) ? GameSceneBase::getPlayer1Color()
                    : GameSceneBase::getPlayer2Color();
                std::string discImage = (colorId == 1) ? "image/1 Player Mode/cam.png"
                    : "image/1 Player Mode/xanh.png";

                auto disc = Sprite::create(discImage);
                disc->setScale(0.7);
                disc->setPosition(getCellPosition(row, col));
                gameplayLayer->addChild(disc, 1);
            }
        }
    }
}
