#include "StatsManager.h"
#include "platform/CCFileUtils.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

static StatsManager* instance = nullptr;

StatsManager* StatsManager::getInstance() {
    if (!instance) instance = new StatsManager();
    return instance;
}

StatsManager::StatsManager() {
    _wins[0] = _wins[1] = 0;
    _draws = 0;
    _abandons[0] = _abandons[1] = 0;

    // Tự động load stats khi khởi tạo
    loadStats();
}

void StatsManager::loadStats() {
    std::string filePath = cocos2d::FileUtils::getInstance()->getWritablePath() + "player_stats.json";

    CCLOG("Loading stats from: %s", filePath.c_str());

    if (!cocos2d::FileUtils::getInstance()->isFileExist(filePath)) {
        CCLOG("Stats file does not exist, using default values");
        return;
    }

    std::string content = cocos2d::FileUtils::getInstance()->getStringFromFile(filePath);
    if (content.empty()) {
        CCLOG("Stats file is empty");
        return;
    }

    CCLOG("Stats file content: %s", content.c_str());

    rapidjson::Document doc;
    doc.Parse(content.c_str());

    if (doc.HasParseError()) {
        CCLOG("Parse error in stats file: %d", doc.GetParseError());
        return;
    }

    if (!doc.IsObject()) {
        CCLOG("Stats file is not a valid JSON object");
        return;
    }

    // Load với kiểm tra an toàn
    if (doc.HasMember("wins1") && doc["wins1"].IsInt()) {
        _wins[0] = doc["wins1"].GetInt();
        CCLOG("Loaded wins1: %d", _wins[0]);
    }

    if (doc.HasMember("wins2") && doc["wins2"].IsInt()) {
        _wins[1] = doc["wins2"].GetInt();
        CCLOG("Loaded wins2: %d", _wins[1]);
    }

    if (doc.HasMember("draws") && doc["draws"].IsInt()) {
        _draws = doc["draws"].GetInt();
        CCLOG("Loaded draws: %d", _draws);
    }

    if (doc.HasMember("abandons1") && doc["abandons1"].IsInt()) {
        _abandons[0] = doc["abandons1"].GetInt();
        CCLOG("Loaded abandons1: %d", _abandons[0]);
    }

    if (doc.HasMember("abandons2") && doc["abandons2"].IsInt()) {
        _abandons[1] = doc["abandons2"].GetInt();
        CCLOG("Loaded abandons2: %d", _abandons[1]);
    }

    CCLOG("Stats loaded successfully - W1:%d, W2:%d, D:%d, A1:%d, A2:%d",
        _wins[0], _wins[1], _draws, _abandons[0], _abandons[1]);
}

void StatsManager::saveStats() {
    rapidjson::Document doc;
    doc.SetObject();
    auto& alloc = doc.GetAllocator();

    doc.AddMember("wins1", _wins[0], alloc);
    doc.AddMember("wins2", _wins[1], alloc);
    doc.AddMember("draws", _draws, alloc);
    doc.AddMember("abandons1", _abandons[0], alloc);
    doc.AddMember("abandons2", _abandons[1], alloc);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    std::string filePath = cocos2d::FileUtils::getInstance()->getWritablePath() + "player_stats.json";
    FILE* file = fopen(filePath.c_str(), "w");
    if (file) {
        fputs(buffer.GetString(), file);
        fclose(file);
        CCLOG("Stats saved to: %s", filePath.c_str());
        CCLOG("Stats content: %s", buffer.GetString());
    }
    else {
        CCLOG("Failed to save stats to: %s", filePath.c_str());
    }
}

void StatsManager::resetStats() {
    _wins[0] = _wins[1] = 0;
    _draws = 0;
    _abandons[0] = _abandons[1] = 0;
    CCLOG("Stats reset");
}

void StatsManager::recordWin(int playerId) {
    if (playerId >= 1 && playerId <= 2) {
        _wins[playerId - 1]++;
        CCLOG("Recorded win for player %d. Total wins: %d", playerId, _wins[playerId - 1]);
    }
}

void StatsManager::recordDraw() {
    _draws++;
    CCLOG("Recorded draw. Total draws: %d", _draws);
}

void StatsManager::recordAbandon(int playerId) {
    if (playerId >= 1 && playerId <= 2) {
        _abandons[playerId - 1]++;
        CCLOG("Recorded abandon for player %d. Total abandons: %d", playerId, _abandons[playerId - 1]);
    }
}

int StatsManager::getWins(int playerId) {
    if (playerId >= 1 && playerId <= 2) {
        return _wins[playerId - 1];
    }
    return 0;
}

int StatsManager::getDraws() {
    return _draws;
}

int StatsManager::getAbandons(int playerId) {
    if (playerId >= 1 && playerId <= 2) {
        return _abandons[playerId - 1];
    }
    return 0;
}

void StatsManager::debugPrintStats() {
    CCLOG("=== STATS MANAGER DEBUG ===");
    CCLOG("_wins[0] (Player1): %d", _wins[0]);
    CCLOG("_wins[1] (Player2): %d", _wins[1]);
    CCLOG("_draws: %d", _draws);
    CCLOG("_abandons[0] (Player1): %d", _abandons[0]);
    CCLOG("_abandons[1] (Player2): %d", _abandons[1]);
    CCLOG("getWins(1): %d", getWins(1));
    CCLOG("getAbandons(1): %d", getAbandons(1));
    CCLOG("getDraws(): %d", getDraws());
    CCLOG("========================");
}

void StatsManager::forceReloadStats() {
    CCLOG("Force reloading stats...");
    // Reset về 0 trước khi load
    _wins[0] = _wins[1] = 0;
    _draws = 0;
    _abandons[0] = _abandons[1] = 0;

    // Load lại từ file
    loadStats();

    // Debug sau khi load
    debugPrintStats();
}