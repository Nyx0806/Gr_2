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

    auto soundIcon = Sprite::create("image/Options UI/nut am thanh.png");
    soundIcon->setPosition(Vec2(center.x, 900));
    this->addChild(soundIcon);

    auto sound = Sprite::create("image/Options UI/SOUND.png");
    FigmaLayoutHelper::apply(sound, 100, 385, 200, 83);
    sound->setScale(0.8f);
    this->addChild(sound);

    auto material = Sprite::create("image/Options UI/MATERIAL.png");
    FigmaLayoutHelper::apply(material, 125, 490, 200, 83);
    material->setScale(0.8f);
    this->addChild(material);

    auto volumeSlider = Slider::create();
    volumeSlider->loadBarTexture("image/1 Player Mode/diff.png");
    volumeSlider->loadSlidBallTextures("image/1 Player Mode/slide.png", "image/1 Player Mode/slide.png"); //dung tam thanh cua dificulty
    volumeSlider->setScale(0.4f);
    volumeSlider->setPosition(Vec2(560, 900));
    this->addChild(volumeSlider);

    // Gán âm lượng đã lưu (nếu có)
    float savedVolume = UserDefault::getInstance()->getFloatForKey("bgmVolume", 1.0f); // mặc định 1.0
    volumeSlider->setPercent(savedVolume * 100);
    SoundManager::getInstance().setVolume(savedVolume);

    // Gắn sự kiện khi kéo slider để cập nhật âm lượng & lưu lại
    volumeSlider->addEventListener([=](Ref* sender, Slider::EventType type) {
        if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
            int percent = volumeSlider->getPercent();
            float volume = percent / 100.0f;
            SoundManager::getInstance().setVolume(volume);
            UserDefault::getInstance()->setFloatForKey("bgmVolume", volume);
        }
        });

    //    auto slider = Slider::create();
    //slider->loadBarTexture("image/1 Player Mode/diff.png");
  //  slider->loadSlidBallTextures("image/1 Player Mode/slide.png", "image/1 Player Mode/slide.png");
   // slider->setPercent(0);
  //  slider->setPosition(Vec2(center.x + 120, 347));
  //  slider->setScale(0.6f);
  //  this->addChild(slider);




    return true;
}

void OptionsScene::onSoundToggle() {
    _soundEnabled = !_soundEnabled;
}

void OptionsScene::onMaterialChange() {
    _materialType = (_materialType + 1) % 2;
}