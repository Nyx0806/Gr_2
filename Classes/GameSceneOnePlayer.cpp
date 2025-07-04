#include "GameSceneOnePlayer.h"
#include "GameSceneBase.h"
#include "UIManager.h"

USING_NS_CC;

Scene* GameSceneOnePlayer::createScene() {
    auto scene = Scene::create();
    auto layer = GameSceneOnePlayer::create();
    scene->addChild(layer);
    return scene;
}

bool GameSceneOnePlayer::init() {
    if (!initBase()) return false;

    _aiPlayer = new AIPlayer(GameSceneBase::getAIDifficulty());
    _currentPlayer = 1; // người chơi đi trước

    // Tạo các vùng click như chế độ 2 người
    for (int col = 0; col < MAX_COL; ++col) {
        auto tapArea = ui::Layout::create();
        tapArea->setContentSize(Size(CELL_SIZE_Width, CELL_SIZE_Heigth * MAX_ROW));
        tapArea->setPosition(Vec2(
            _board->getPositionX() + col * CELL_SIZE_Width + CELL_SIZE_Width / 2,
            _board->getPositionY() + (CELL_SIZE_Heigth * MAX_ROW / 2)
        ));
        tapArea->setTouchEnabled(true);

        tapArea->addClickEventListener([=](Ref*) {
            this->onColumnTap(col);
            });

        this->addChild(tapArea);
    }


    return true;
}

void GameSceneOnePlayer::onColumnTap(int col) {
    if (_currentPlayer != 1) return;

    int row = _board->dropPiece(col, _currentPlayer); //xử lý logic
    if (row >= 0) {
        _board->addPieceSprite(row, col, _currentPlayer); //thêm sprite nếu thành công

        checkWin(row, col);
        switchTurn();

        // Gọi AI sau delay
        this->runAction(Sequence::createWithTwoActions(
            DelayTime::create(0.5f),
            CallFunc::create([=]() { performAIMove(); })
        ));
    }
}

void GameSceneOnePlayer::performAIMove() {
    int aiCol = _aiPlayer->chooseMove(_board);
    int placedRow = _board->dropPiece(aiCol, 2);
    if (aiCol >= 0 && placedRow != -1) {
        _board->addPieceSprite(placedRow, aiCol, 2); //thêm animation

        checkWin(placedRow, aiCol);
        switchTurn();
    }
}
