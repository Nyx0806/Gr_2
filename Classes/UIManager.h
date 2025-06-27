// MODULE 9: UIManager – Tạo và quản lý các UI đơn giản
#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
class UIManager {
public:
    // Tạo button cơ bản với tiêu đề và callback
    static cocos2d::ui::Button* createButton(const std::string& title,
        const std::string& normalImage,
        const std::string& pressedImage,
        const cocos2d::Vec2& position,
        const std::function<void(cocos2d::Ref*)>& callback);

    // Tạo label
    static cocos2d::Label* createLabel(const std::string& text, float fontSize, const cocos2d::Vec2& position);

    // Hiện popup thông báo đơn giản
    static void showPopup(cocos2d::Node* parent, const std::string& message);
};