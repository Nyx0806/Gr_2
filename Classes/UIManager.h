// MODULE 9: UIManager – Tạo và quản lý các UI đơn giản
#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
class UIManager {
public:
    // Tạo button cơ bản với ảnh sẵn có và callback
    static cocos2d::ui::Button* createButton(
        const std::string& normalImage,
        const cocos2d::Vec2& position,
        const std::function<void(cocos2d::Ref*)>& callback,
        float scale);
};