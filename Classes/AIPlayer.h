// MODULE 4: AIPlayer � Ng??i ch?i m�y
#pragma once
#include "GameBoard.h"
#include <cstdlib>
#include <vector>

class AIPlayer : public Player {
public:
    // Kh?i t?o AI v?i ID = 2, m�u cam
    AIPlayer() : Player(2, cocos2d::Color3B::ORANGE) {}

    // L?a ch?n n??c ?i ??n gi?n (ng?u nhi�n t? c�c c?t c�n tr?ng)
    int chooseMove(GameBoard* board) {
        std::vector<int> availableCols;
        for (int c = 0; c < MAX_COL; ++c) {
            if (board->getCell(0, c) == 0) // ki?m tra h�ng ??u ch?a b? l?p
                availableCols.push_back(c);
        }
        if (availableCols.empty()) return -1; // kh�ng c�n ch? ?i

        int randomIndex = rand() % availableCols.size();
        return availableCols[randomIndex];
    }
};