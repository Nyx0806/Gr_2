#include "GameSceneBase.h"
#include "ui/CocosGUI.h"
#include "GameBoard.h"

USING_NS_CC;
using namespace ui;

int GameSceneBase::_colorP1 = 1;
bool GameSceneBase::_vsAI = true;
int GameSceneBase::_aiDifficulty = 1;
std::string GameSceneBase::_player1Name = "Player 1";
std::string GameSceneBase::_player2Name = "Player 2";
int GameSceneBase::_player1Color = 1;
int GameSceneBase::_firstMovePlayer = 1;
std::string GameSceneBase::_player1Avatar = "";
std::string GameSceneBase::_player2Avatar = "";

bool GameSceneBase::initBase() {
    if (!Scene::init()) return false;

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    _board = GameBoard::create();
    _board->setPosition(Vec2(visibleSize.width / 2 - _board->getContentSize().width / 2,
        visibleSize.height / 2 - _board->getContentSize().height / 2));
    this->addChild(_board);

    updatePieceUI();

    return true;
}

void GameSceneBase::setAIDifficulty(int diff) {
    _aiDifficulty = diff;
}

int GameSceneBase::getAIDifficulty() {
    return _aiDifficulty;
}

void GameSceneBase::setGameSettings(const std::string& name1, const std::string& name2, int color, int firstMove) {
    _player1Name = name1;
    _player2Name = name2;
    _player1Color = color;
    _firstMovePlayer = firstMove;
}

int GameSceneBase::getPlayer1Color() {
    return _player1Color;
}

int GameSceneBase::getPlayer2Color() {
    return 3 - _player1Color;
}

int GameSceneBase::getColorForTurn(int player) {
    if (player == 1)
        return _colorP1;
    else
        return (_colorP1 == 1) ? 2 : 1;
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

void GameSceneBase::setPlayerAvatars(const std::string& avatar1, const std::string& avatar2) {
    _player1Avatar = avatar1;
    _player2Avatar = avatar2;
}

std::string GameSceneBase::getPlayer1Avatar() {
    return _player1Avatar;
}

std::string GameSceneBase::getPlayer2Avatar() {
    return _player2Avatar;
}

void GameSceneBase::updatePieceUI() {
    Size visibleSize = Director::getInstance()->getVisibleSize();

    _avatarP1 = Sprite::create(_player1Avatar);
    if (_avatarP1) {
        _avatarP1->setScale(0.3f);
        _avatarP1->setPosition(Vec2(visibleSize.width * 0.15f, visibleSize.height * 0.9f));
        this->addChild(_avatarP1);
    }

    _avatarP2 = Sprite::create(_player2Avatar);
    if (_avatarP2) {
        _avatarP2->setScale(0.3f);
        _avatarP2->setPosition(Vec2(visibleSize.width * 0.85f, visibleSize.height * 0.9f));
        this->addChild(_avatarP2);
    }

    _nameP1 = Text::create(_player1Name, "fonts/Marker Felt.ttf", 24);
    this->addChild(_nameP1);

    _nameP2 = Text::create(_player2Name, "fonts/Marker Felt.ttf", 24);
    this->addChild(_nameP2);
}

void GameSceneBase::switchTurn() {
    _currentPlayer = 3 - _currentPlayer;
}

void GameSceneBase::showWinPopup(int winnerId) {
    std::string winnerName = (winnerId == 1) ? _player1Name : _player2Name;

    auto label = Label::createWithSystemFont(winnerName + " wins!", "Arial", 36);
    label->setPosition(Director::getInstance()->getVisibleSize() / 2);
    this->addChild(label, 100);
}
