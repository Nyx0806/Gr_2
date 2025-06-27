#include "GameScene.h"
#include "AIPlayer.h"
#include "StatsManager.h"

USING_NS_CC;

Scene* GameScene::createScene(GameMode mode) {
    auto scene = Scene::create();
    auto layer = GameScene::create();
    layer->_mode = mode;
    scene->addChild(layer);
    return scene;
}

bool GameScene::init() {
    if (!Scene::init()) return false;

    // Khởi tạo người chơi
    _player1 = new Player(1, Color3B::GREEN);
    _player2 = (_mode == GameMode::ONE_PLAYER) ? new AIPlayer() : new Player(2, Color3B::ORANGE);

    // Khởi tạo bàn cờ
    _board = GameBoard::create();
    this->addChild(_board);

    _currentTurn = 0;

    // Lắng nghe chạm vào các cột
    // ... sẽ được xử lý trong phần UI sau

    return true;
}

void GameScene::onColumnTapped(int col) {
    // Gọi tới GameBoard để đánh cờ tại cột
    bool success = _board->dropPiece(col, _currentTurn);

    if (success) {
        updateBoard();
        checkWinCondition();
        _currentTurn = (_currentTurn + 1) % 2;
    }
}

void GameScene::updateBoard() {
    // Gọi lại update UI của GameBoard nếu cần
}

void GameScene::checkWinCondition() {
    // Kiểm tra xem có người chơi nào thắng hoặc hòa không
    // Nếu có thì ghi lại vào StatsManager và reset game
}

void GameScene::resetGame() {
    _board->resetBoard();
    _currentTurn = 0;
}
