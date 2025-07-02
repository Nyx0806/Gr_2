#include "UIManager.h"
using namespace cocos2d;
using namespace ui;

UIManager* UIManager::instance = nullptr;

UIManager* UIManager::getInstance() {
    if (!instance) {
        instance = new UIManager();
    }
    return instance;
}

Button* UIManager::createButton(
    const std::string& normalImage,
    const Vec2& position,
    const std::function<void(Ref*)>& callback,
    float scale) {

    auto button = Button::create(normalImage);
    button->setAnchorPoint(Vec2(0.5f, 1.0f)); // căn giữa-trên
    button->setPosition(position);
    button->setScale(scale);
    button->addClickEventListener(callback);
    return button;  
}

void UIManager::changeScene(Scene* scene, float duration, const std::function<void()>& onTransitionEnd) {
    auto transition = TransitionFade::create(duration, scene);

    if (onTransitionEnd) {
        auto delay = DelayTime::create(duration);
        auto callback = CallFunc::create(onTransitionEnd);
        auto sequence = Sequence::create(delay, callback, nullptr);
        transition->runAction(sequence);
    }

    Director::getInstance()->replaceScene(transition);
}

Label* UIManager::createLabelFigma(const std::string& text, float fontSize, float left, float top, float width, float height) {
    auto label = Label::createWithTTF(text, "fonts/PoetsenOne-Regular.ttf", fontSize);
    label->setColor(Color3B::WHITE);
    label->setAlignment(TextHAlignment::LEFT);
    label->setAnchorPoint(Vec2(0.0f, 1.0f)); // neo trái trên
	label->setScale(1.3f);

    float posX = left;
    float posY = 720 - top; // dùng đúng chiều cao design
    label->setPosition(Vec2(posX, posY));

    return label;
}


