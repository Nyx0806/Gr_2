// MODULE 3: Player – Định nghĩa người chơi
#pragma once
#include "cocos2d.h"

class Player {
public:
    // Khởi tạo người chơi với ID và màu cờ
    Player(int id, cocos2d::Color3B color) : _id(id), _color(color) {}

    int getId() const { return _id; } // Lấy ID người chơi
    cocos2d::Color3B getColor() const { return _color; } // Lấy màu cờ

private:
    int _id;
    cocos2d::Color3B _color;
};
