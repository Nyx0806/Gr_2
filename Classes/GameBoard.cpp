#include "GameBoard.h"
#include "GameSceneBase.h"

USING_NS_CC;

bool GameBoard::init() {
    if (!Node::init()) return false;

    resetBoard();
    // Reset trạng thái mảng logic và sprite
    for (int row = 0; row < MAX_ROW; ++row) {
        for (int col = 0; col < MAX_COL; ++col) {
            _board[row][col] = 0;
            _gridSprites[row][col] = nullptr;

            
            auto slot = cocos2d::Sprite::create("image/Gameplay UI/empty.png");
            slot->setPosition(Vec2(
                col * CELL_SIZE + CELL_SIZE / 2,
                row * CELL_SIZE + CELL_SIZE / 2
            ));
            this->addChild(slot, 0); // Z-order = 0 dưới quân cờ
        }
    }

    // Đặt kích thước logic cho node
    this->setContentSize(Size(MAX_COL * CELL_SIZE, MAX_ROW * CELL_SIZE));
    this->setAnchorPoint(Vec2::ZERO);
    this->setPosition(Vec2::ZERO);

    return true;

}

int GameBoard::dropPiece(int col, int playerId) {
    for (int row = 0; row < MAX_ROW; ++row) {
        if (_board[row][col] == 0) {
            _board[row][col] = playerId;
            return row;
        }
    }
    return -1;
}

void GameBoard::addPieceSprite(int row, int col, int playerId) {
    // Lấy màu quân cờ dựa theo player
    int color = GameSceneBase::getColorForPlayer(playerId);
    std::string pieceImg = (color == 1)
        ? "image/1 Player Mode/cam.png"
        : "image/1 Player Mode/xanh.png";

    // Tạo quân cờ và đặt ban đầu phía trên bàn cờ (rơi xuống)
    auto piece = cocos2d::Sprite::create(pieceImg);
    piece->setPosition(Vec2(
        col * CELL_SIZE + CELL_SIZE / 2,
        MAX_ROW * CELL_SIZE + 100 // Vị trí "trên cao" để rơi xuống
    ));
    this->addChild(piece, 1); // Layer cao hơn empty slot

    // Vị trí đích đến (trung tâm ô rỗng)
    Vec2 targetPos = Vec2(
        col * CELL_SIZE + CELL_SIZE / 2,
        row * CELL_SIZE + CELL_SIZE / 2
    );

    // Hiệu ứng rơi
    auto moveAction = cocos2d::MoveTo::create(0.25f, targetPos);
    piece->runAction(moveAction);

    // Lưu lại sprite để quản lý
    _gridSprites[row][col] = piece;
}

int GameBoard::getCell(int row, int col) const {
    if (row < 0 || row >= MAX_ROW || col < 0 || col >= MAX_COL)
        return -1;
    return _board[row][col];
}

void GameBoard::resetBoard() {
    for (int row = 0; row < MAX_ROW; ++row)
        for (int col = 0; col < MAX_COL; ++col) {
            _board[row][col] = 0;
            if (_gridSprites[row][col]) {
                _gridSprites[row][col]->removeFromParent();
                _gridSprites[row][col] = nullptr;
            }
        }
}

// (Tùy bạn) kiểm tra thắng hàng dọc/ngang/chéo — giữ nguyên nếu đã có
bool GameBoard::checkWin(int row, int col, int playerId) const {
    // ... (giữ lại phần này nếu bạn đã có sẵn)
    return false;
}
