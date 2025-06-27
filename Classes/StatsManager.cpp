#include "StatsManager.h"
static StatsManager* instance = nullptr;

StatsManager* StatsManager::getInstance() {
    if (!instance) instance = new StatsManager();
    return instance;
}

StatsManager::StatsManager() {
    _wins[0] = _wins[1] = 0;
    _draws = 0;
    _abandons[0] = _abandons[1] = 0;
}

void StatsManager::loadStats() {
    // Chưa tích hợp lưu file, có thể thêm bằng UserDefault
}

void StatsManager::saveStats() {
    // Chưa tích hợp lưu file, có thể thêm bằng UserDefault
}

void StatsManager::resetStats() {
    _wins[0] = _wins[1] = 0;
    _draws = 0;
    _abandons[0] = _abandons[1] = 0;
}

void StatsManager::recordWin(int playerId) {
    if (playerId >= 1 && playerId <= 2) _wins[playerId - 1]++;
}

void StatsManager::recordDraw() {
    _draws++;
}

void StatsManager::recordAbandon(int playerId) {
    if (playerId >= 1 && playerId <= 2) _abandons[playerId - 1]++;
}

int StatsManager::getWins(int playerId) {
    return _wins[playerId - 1];
}

int StatsManager::getDraws() {
    return _draws;
}

int StatsManager::getAbandons(int playerId) {
    return _abandons[playerId - 1];
}