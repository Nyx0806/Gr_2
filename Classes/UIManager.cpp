#include "UIManager.h"
using namespace cocos2d;
using namespace ui;

Button* UIManager::createButton(
    const std::string& normalImage,
    const Vec2& position,
    const std::function<void(Ref*)>& callback,
    float scale = 1.0f) {

    auto button = Button::create(normalImage);
    button->setAnchorPoint(Vec2(0.5f, 1.0f)); // căn giữa-trên
    button->setPosition(position);
    button->setScale(scale);
    button->addClickEventListener(callback);
    return button;
}

