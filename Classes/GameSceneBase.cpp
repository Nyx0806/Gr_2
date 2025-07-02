#include "GameSceneBase.h"
#include "WinLoseScene.h"
#include "UIManager.h"
#include "FigmaLayoutHelper.h"
#include "ui/UIText.h"


USING_NS_CC;

bool GameSceneBase::initBase() {
    if (!Scene::init()) return false;

    _timeLeft = 10.0f; // gán giá trị mặc định ở đây


    // --- 1. Background ---
    auto size = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto background = Sprite::create("image/Main UI/BG.png");
    background->setPosition(size / 2);
    this->addChild(background);

    // --- 2. Title ---
    auto title = Sprite::create("image/Main UI/title.png");
    FigmaLayoutHelper::apply(title, 65, 150, 970, 127);
    title->setAnchorPoint(Vec2(0.0f, 1.0f));
    title->setScale(720.0f / 970.0f);
    this->addChild(title);

    // --- 3. Avatars & Names ---
    _avatarP1 = Sprite::create("image/1 Player Mode/cam.png"); // default
    _avatarP1->setPosition(Vec2(70, 975));
	_avatarP1->setScale(0.8f); // Giảm kích thước cho vừa
    this->addChild(_avatarP1);

    _nameP1 = ui::Text::create("Player", "fonts/PoetsenOne-Regular.ttf", 36);
    _nameP1->setPosition(Vec2(250, 975));
    _nameP1->setTextColor(Color4B::WHITE);
    this->addChild(_nameP1);


    _avatarP2 = Sprite::create("image/1 Player Mode/xanh.png"); // default
    _avatarP2->setPosition(Vec2(size.width - 70, 975));
	_avatarP2->setScale(0.8f); // Giảm kích thước cho vừa
    this->addChild(_avatarP2);

    _nameP2 = ui::Text::create("Machine", "fonts/PoetsenOne-Regular.ttf", 36);
    _nameP2->setPosition(Vec2(size.width - 250, 975));
    _nameP2->setTextColor(Color4B::WHITE);
    this->addChild(_nameP2);

    // --- 4. Gán dữ liệu từ config ---
    _nameP1->setString(GameSceneBase::getPlayer1Name());
    _nameP2->setString(GameSceneBase::getPlayer2Name());

    if (GameSceneBase::getColorForPlayer(1) == 1) {
        _avatarP1->setTexture("image/1 Player Mode/cam.png");
        _avatarP2->setTexture("image/1 Player Mode/xanh.png");
    }
    else {
        _avatarP1->setTexture("image/1 Player Mode/xanh.png");
        _avatarP2->setTexture("image/1 Player Mode/cam.png");
    }

    // --- 5. Board background ---
    _board = GameBoard::create();
	_board->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2 -300, 300));
    _board->setScale(0.8f); // vì đã dùng CELL_SIZE nên không cần scale nữa
    this->addChild(_board, 1);

    // --- 6. Grid sprite over the board ---
    auto boardFrame = Sprite::create("image/Gameplay UI/board.png");
    boardFrame->setAnchorPoint(Vec2::ZERO);
    boardFrame->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2 - 310, 260));
	boardFrame->setScale(1.35f); // Giữ nguyên kích thước gốc
    this->addChild(boardFrame, 10); // Trên các quân cờ

    // --- 7. Timer (tuỳ chọn) ---
    _timerLabel = ui::Text::create("10", "fonts/PoetsenOne-Regular.ttf", 36);
    _timerLabel->setPosition(Vec2(size.width / 2, 850));
    _timerLabel->setTextColor(Color4B::YELLOW);
    this->addChild(_timerLabel);

    // --- 8. Pause button ---
    auto pauseBtn = ui::Button::create("image/Gameplay UI/pause button.png");
    pauseBtn->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, 200));
    pauseBtn->addClickEventListener([](Ref*) {
        Director::getInstance()->popScene();
        });
    this->addChild(pauseBtn);

    updatePieceUI();
    return true;
}

std::string GameSceneBase::_player1Name = "Player 1";
std::string GameSceneBase::_player2Name = "Player 2";  // mặc định cho chế độ 2 người
int GameSceneBase::_player1Color = 1;
int GameSceneBase::_firstMovePlayer = 1;

void GameSceneBase::setGameSettings(const std::string& name1, const std::string& name2, int color, int firstMove) {
    _player1Name = name1;
    _player2Name = name2;
    _player1Color = color;
    _firstMovePlayer = firstMove;
}

int GameSceneBase::getColorForPlayer(int playerId) {
    if (playerId == 1) return _player1Color;
    return (_player1Color == 1) ? 2 : 1;
}


std::string GameSceneBase::getPlayer1Name() {
    return _player1Name;
}

std::string GameSceneBase::getPlayer2Name() {
    return _player2Name;
}

int GameSceneBase::getFirstMove() {
    return _firstMovePlayer;
}

void GameSceneBase::checkWin(int row, int col) {
   /* if (_board->checkWin(row, col, _currentPlayer)) {
        this->scheduleOnce([=](float) {
            showWinPopup(_currentPlayer);
            }, 0.3f, "delayWinPopup");
    }*/
}

void GameSceneBase::switchTurn() {
    _currentPlayer = (_currentPlayer == 1) ? 2 : 1;
    updatePieceUI();
}

void GameSceneBase::showWinPopup(int winnerId) {
    Director::getInstance()->replaceScene(WinLoseScene::createScene(true, winnerId));
}

void GameSceneBase::updatePieceUI() {
    // Cập nhật giao diện vòng sáng, tên người chơi v.v nếu cần
}

int GameSceneBase::_aiDifficulty = 1;

void GameSceneBase::setAIDifficulty(int diff) {
    _aiDifficulty = diff;
}

int GameSceneBase::getAIDifficulty() {
    return _aiDifficulty;
}
