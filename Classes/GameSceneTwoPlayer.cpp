#include "GameSceneTwoPlayer.h"
#include "GameBoard.h"
#include "GameSceneBase.h"

USING_NS_CC;

Scene* GameSceneTwoPlayer::createScene() {
    auto scene = Scene::create();
    auto layer = GameSceneTwoPlayer::create();
    scene->addChild(layer);
    return scene;
}

bool GameSceneTwoPlayer::init() {
    if (!Scene::init()) return false;
    
    // Tạo các vùng click như chế độ 2 người
    for (int col = 0; col < MAX_COL; ++col) {
        auto tapArea = ui::Layout::create();
        tapArea->setContentSize(Size(CELL_SIZE_Width, CELL_SIZE_Heigth * MAX_ROW));
        tapArea->setPosition(Vec2(
            GameSceneBase::_board->getPositionX() + col * CELL_SIZE_Width + CELL_SIZE_Width / 2,
            GameSceneBase::_board->getPositionY() + (CELL_SIZE_Heigth * MAX_ROW / 2)
        ));
        tapArea->setTouchEnabled(true);

        tapArea->addClickEventListener([=](Ref*) {
            this->onColumnTap(col);
            });

        this->addChild(tapArea);
    }


    return true;
}
void GameSceneTwoPlayer::onColumnTap(int col) {
    int row = _board->dropPiece(col, _currentPlayer); //xử lý logic
    if (row >= 0) {
        _board->addPieceSprite(row, col, _currentPlayer); //thêm sprite nếu thành công

        checkWin(row, col);
        switchTurn();

    }
}
