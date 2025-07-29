#include "StatsScene.h"
#include "StatsManager.h"
#include "UIManager.h"
#include "MainMenuScene.h"

using namespace cocos2d;

Scene* StatsScene::createScene() {
    auto scene = Scene::create();
    auto layer = StatsScene::create();
    scene->addChild(layer);
    return scene;
}

bool StatsScene::init() {
    if (!Scene::init()) return false;

    auto size = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Vec2 center = Vec2(size.width / 2, size.height / 2);

    auto background = Sprite::create("image/Main UI/BG.png");
    background->setPosition(size / 2);
    this->addChild(background);

    auto title = Sprite::create("image/Main UI/title.png");
    title->setAnchorPoint(Vec2(0.5f, 1.0f));
    title->setScale(0.6f);
    title->setPosition(Vec2(origin.x + size.width / 2, origin.y + size.height - 60));
    this->addChild(title);
    
    auto stats = StatsManager::getInstance();

    // Lấy giá trị để hiển thị
    int wins = stats->getWins(1);
    int losses = stats->getAbandons(1);
    int draws = stats->getDraws();
    int totalGames = wins + losses + draws;

    float tableStartY = origin.y + size.height * 0.62f;
    float rowHeight = 100.0f;
    float colNameX = size.width * 0.22f;
    float colGlobalX = size.width * 0.5f;
    float colPercentX = size.width * 0.78f;

    std::vector<std::string> statNames = {"Win", "Lose", "Draw", "Total"};
    std::vector<int> statValues = {wins, losses, draws, totalGames};
    std::vector<std::string> percentValues;
    for (int i = 0; i < 3; ++i) {
        if (totalGames > 0)
            percentValues.push_back(StringUtils::format("%.1f%%", 100.0f * statValues[i] / (float)totalGames));
        else
            percentValues.push_back("0%");
    }
    percentValues.push_back("100%"); // Tổng luôn là 100%

    std::string fontPath = "fonts/PoetsenOne-Regular.ttf";
    int fontSizeLabel = 44;
    int fontSizeValue = 52;

    // Tiêu đề cột
    auto titleName = Label::createWithTTF("STATS", fontPath, fontSizeLabel);
    titleName->setPosition(Vec2(colNameX, tableStartY + rowHeight));
    titleName->setColor(Color3B::RED);
    titleName->enableOutline(Color4B::BLACK, 2);
    this->addChild(titleName, 100);

    auto titleGlobal = Label::createWithTTF("Global", fontPath, fontSizeLabel);
    titleGlobal->setPosition(Vec2(colGlobalX, tableStartY + rowHeight));
    titleGlobal->setColor(Color3B::BLUE);
    titleGlobal->enableOutline(Color4B::BLACK, 2);
    this->addChild(titleGlobal, 100);

    auto titlePercent = Label::createWithTTF("%", fontPath, fontSizeLabel);
    titlePercent->setPosition(Vec2(colPercentX, tableStartY + rowHeight));
    titlePercent->setColor(Color3B::BLUE);
    titlePercent->enableOutline(Color4B::BLACK, 2);
    this->addChild(titlePercent, 100);

    // Các hàng dữ liệu
    for (int i = 0; i < statNames.size(); ++i) {
        float y = tableStartY - i * rowHeight;
        // Border cho từng ô
        for (float x : {colNameX, colGlobalX, colPercentX}) {
            auto border = Sprite::create("image/Stats/stat_border.png");
            border->setScale(0.8f);
            border->setPosition(Vec2(x, y));
            this->addChild(border, 1);
        }
        // Label tên chỉ số
        auto nameLabel = Label::createWithTTF(statNames[i], fontPath, fontSizeLabel);
        nameLabel->setPosition(Vec2(colNameX, y));
        nameLabel->setColor(Color3B::WHITE);
        nameLabel->enableOutline(Color4B::BLACK, 2);
        this->addChild(nameLabel, 100);
        // Label giá trị Global
        auto valueLabel = Label::createWithTTF(std::to_string(statValues[i]), fontPath, fontSizeValue);
        valueLabel->setPosition(Vec2(colGlobalX, y));
        valueLabel->setColor(Color3B::BLUE);
        valueLabel->enableOutline(Color4B::BLACK, 2);
        this->addChild(valueLabel, 100);
        // Label phần trăm
        auto percentLabel = Label::createWithTTF(percentValues[i], fontPath, fontSizeLabel);
        percentLabel->setPosition(Vec2(colPercentX, y));
        percentLabel->setColor(Color3B::BLUE);
        percentLabel->enableOutline(Color4B::BLACK, 2);
        this->addChild(percentLabel, 100);
    }

    // Nút quay lại menu
    auto back = UIManager::getInstance()->createButton("image/Options UI/back to main menu full.png",
        Vec2(center.x, origin.y + size.height * 0.15f),
        [](Ref*) { UIManager::getInstance()->changeScene(MainMenuScene::createScene()); },
        0.6f);
    this->addChild(back, 5);

    // Nút xóa toàn bộ stat
    auto eraseStat = UIManager::getInstance()->createButton("image/Stats/erase stats button.png",
        Vec2(center.x, origin.y + size.height * 0.25f),
        [this](Ref*) {
            // Reset stats và save
            StatsManager::getInstance()->resetStats();
            StatsManager::getInstance()->saveStats();
            // Refresh lại scene để hiển thị stats đã reset
            Director::getInstance()->replaceScene(StatsScene::createScene());
        },
        0.6f);
    this->addChild(eraseStat, 5); 
    return true;
}