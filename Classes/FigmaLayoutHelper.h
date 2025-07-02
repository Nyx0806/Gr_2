// FigmaLayoutHelper.h
#pragma once
#include "cocos2d.h"

class FigmaLayoutHelper {
public:
    static void apply(cocos2d::Node* node, float left, float top, float width, float height, cocos2d::Size designSize = cocos2d::Size(720, 1280)) {
        node->setPosition(cocos2d::Vec2(left, designSize.height - top));
    }
};