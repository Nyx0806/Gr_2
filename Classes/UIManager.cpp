#include "UIManager.h"
using namespace cocos2d;
using namespace ui;

Button* UIManager::createButton(const std::string& title, 
    const std::string& normalImage,
    const std::string& pressedImage, 
    const Vec2& position, 
    const std::function<void(Ref*)>& callback) {

    auto button = Button::create(normalImage);
    button->setTitleText(title);
    button->setTitleFontSize(28);
    button->setPosition(position);
    button->addClickEventListener(callback);
    return button;
}

Label* UIManager::createLabel(const std::string& text, float fontSize, const Vec2& position) {
    auto label = Label::createWithTTF(text, "fonts/Marker Felt.ttf", fontSize);
    label->setPosition(position);
    label->setColor(Color3B::WHITE);
    return label;
}

void UIManager::showPopup(Node* parent, const std::string& message) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto bg = LayerColor::create(Color4B(0, 0, 0, 180));
    bg->setContentSize(visibleSize);
    bg->setPosition(Vec2::ZERO);
    parent->addChild(bg, 100);

    auto label = Label::createWithTTF(message, "fonts/Marker Felt.ttf", 36);
    label->setPosition(visibleSize / 2);
    label->setColor(Color3B::YELLOW);
    bg->addChild(label);

    bg->runAction(Sequence::create(DelayTime::create(2.0f), RemoveSelf::create(), nullptr));
}