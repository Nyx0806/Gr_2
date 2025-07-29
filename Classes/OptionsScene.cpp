#include "OptionsScene.h"
#include "UIManager.h"
#include "MainMenuScene.h"
#include "FigmaLayoutHelper.h"
#include "ui/CocosGUI.h"
#include "audio/include/AudioEngine.h"
#include "SoundManager.h"

using namespace cocos2d;
using namespace cocos2d::ui;

Scene* OptionsScene::createScene() {
    auto scene = Scene::create();
    auto layer = OptionsScene::create();
    scene->addChild(layer);
    return scene;
}

bool OptionsScene::init() {
    if (!Scene::init()) return false;

	// Lấy kích thuoc man hinh
    auto size = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Vec2 center = Vec2(size.width / 2, size.height / 2);

	//Background
    auto background = Sprite::create("image/Main UI/BG.png");
    background->setPosition(size / 2);
    this->addChild(background);

    _soundEnabled = true;
    _materialType = 0;

    // Thiết kế giao diện Options

    // --- BACK BUTTON ---
    auto back = UIManager::getInstance()->createButton("image/Options UI/back to main menu full.png",
        Vec2(center.x , 270),
        [](Ref*) { UIManager::getInstance()->changeScene(MainMenuScene::createScene()); },
        0.6f);
    this->addChild(back);
	
    auto title = Sprite::create("image/Main UI/title.png");
    FigmaLayoutHelper::apply(title, 65, 150, 970, 127);
    title->setAnchorPoint(Vec2(0.0f, 1.0f));
    title->setScale(720.0f / 970.0f);
    this->addChild(title);

    auto subtitle = Sprite::create("image/Options UI/OPTIONS.png");
    FigmaLayoutHelper::apply(subtitle, 365, 265, 410, 83);
    subtitle->setScale(0.8f);
    this->addChild(subtitle);

    //auto soundIcon = Sprite::create("image/Options UI/nut am thanh.png");
    //soundIcon->setPosition(Vec2(center.x, 900));
    //this->addChild(soundIcon);

    auto bgSound = Sprite::create("image/Options UI/BACKGROUND VOLUME.png");
    FigmaLayoutHelper::apply(bgSound, 210, 385, 200, 83);
    bgSound->setScale(0.65f);
    this->addChild(bgSound);

    auto sfxSound = Sprite::create("image/Options UI/SFX VOLUME.png");
    FigmaLayoutHelper::apply(sfxSound, 150, 610, 200, 83);
    sfxSound->setScale(0.65f);
    this->addChild(sfxSound);

    auto MasterSound = Sprite::create("image/Options UI/MASTER VOLUME.png");
    FigmaLayoutHelper::apply(MasterSound, 180, 835, 200, 83);
    MasterSound->setScale(0.65f);
    this->addChild(MasterSound);

    // === Lấy âm lượng đã lưu hoặc mặc định ===
    float bgm = UserDefault::getInstance()->getFloatForKey("bgmVolume", 1.0f);
    float sfx = UserDefault::getInstance()->getFloatForKey("sfxVolume", 1.0f);
    float master = UserDefault::getInstance()->getFloatForKey("masterVolume", 1.0f);

    // --- BGM SLIDER ---
    auto bgmSlider = Slider::create();
    bgmSlider->loadBarTexture("image/1 Player Mode/diff.png");
    bgmSlider->loadSlidBallTextures("image/1 Player Mode/slide.png", "image/1 Player Mode/slide.png");
    bgmSlider->setPosition(Vec2(560, 900));
    bgmSlider->setScale(0.4f);
    float bgmVol = UserDefault::getInstance()->getFloatForKey("bgmVolume", 1.0f);
    bgmSlider->setPercent(bgmVol * 100);
    bgmSlider->addEventListener([=](Ref*, Slider::EventType type) {
        if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
            float vol = bgmSlider->getPercent() / 100.0f;
            SoundManager::getInstance().setBGMVolume(vol);
        }
        });
    this->addChild(bgmSlider);

    // --- SFX SLIDER ---
    auto sfxSlider = Slider::create();
    sfxSlider->loadBarTexture("image/1 Player Mode/diff.png");
    sfxSlider->loadSlidBallTextures("image/1 Player Mode/slide.png", "image/1 Player Mode/slide.png");
    sfxSlider->setPosition(Vec2(560, 675));
    sfxSlider->setScale(0.4f);
    float sfxVol = UserDefault::getInstance()->getFloatForKey("sfxVolume", 1.0f);
    sfxSlider->setPercent(sfxVol * 100);
    sfxSlider->addEventListener([=](Ref*, Slider::EventType type) {
        if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
            float vol = sfxSlider->getPercent() / 100.0f;
            SoundManager::getInstance().setSFXVolume(vol);
        }
        });
    this->addChild(sfxSlider);

    // --- MASTER VOLUME SLIDER ---
    auto masterSlider = Slider::create();
    masterSlider->loadBarTexture("image/1 Player Mode/diff.png");
    masterSlider->loadSlidBallTextures("image/1 Player Mode/slide.png", "image/1 Player Mode/slide.png");
    masterSlider->setPosition(Vec2(560, 450));
    masterSlider->setScale(0.4f);
    float masterVol = UserDefault::getInstance()->getFloatForKey("masterVolume", 1.0f);
    masterSlider->setPercent(masterVol * 100);
    masterSlider->addEventListener([=](Ref*, Slider::EventType type) {
        if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
            float vol = masterSlider->getPercent() / 100.0f;
            SoundManager::getInstance().setMasterVolume(vol);
        }
        });
    this->addChild(masterSlider);

    //test click sound
    auto listener = EventListenerMouse::create();
    listener->onMouseDown = [](EventMouse* event) {
        SoundManager::getInstance().playClickSound();  // <-- gọi được bình thường
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
  



    return true;
}

void OptionsScene::onSoundToggle() {
    _soundEnabled = !_soundEnabled;
}

void OptionsScene::onMaterialChange() {
    _materialType = (_materialType + 1) % 2;
}