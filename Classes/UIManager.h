#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <functional>

class UIManager {
public:
    static UIManager* getInstance();

    // Tạo button đơn giản
    cocos2d::ui::Button* createButton(
        const std::string& normalImage,
        const cocos2d::Vec2& position,
        const std::function<void(cocos2d::Ref*)>& callback,
        float scale = 1.0f);

    // Chuyển scene có animation và callback tùy chọn
    void changeScene(cocos2d::Scene* scene,
        float duration = 0.2f,
        const std::function<void()>& onTransitionEnd = nullptr);

private:
    UIManager() = default;
    static UIManager* instance;
};
