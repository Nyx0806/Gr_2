#include "SoundManager.h"
#include "audio/include/AudioEngine.h"
#include "base/CCUserDefault.h"

using namespace cocos2d;

SoundManager& SoundManager::getInstance() {
    static SoundManager instance;
    return instance;
}

void SoundManager::playBackgroundMusic(const std::string& filePath) {
    float bgm = UserDefault::getInstance()->getFloatForKey("bgmVolume", 1.0f);
    float master = UserDefault::getInstance()->getFloatForKey("masterVolume", 1.0f);
    float finalVolume = bgm * master;

    if (finalVolume <= 0.01f) return; // Không phát nếu âm lượng đã tắt

    if (!isPlaying) {
        bgmId = AudioEngine::play2d(filePath, true, finalVolume);  // phát đúng volume luôn
        isPlaying = true;
    }
}

void SoundManager::stopBackgroundMusic() {
    if (isPlaying && bgmId != AudioEngine::INVALID_AUDIO_ID) {
        AudioEngine::stop(bgmId);
        isPlaying = false;
    }
}

void SoundManager::playClickSound() {
    float sfx = UserDefault::getInstance()->getFloatForKey("sfxVolume", 1.0f);
    float master = UserDefault::getInstance()->getFloatForKey("masterVolume", 1.0f);
    float finalVolume = sfx * master;

    AudioEngine::play2d("sound/click.mp3", false, finalVolume);
}

void SoundManager::setSFXVolume(float volume) {
    UserDefault::getInstance()->setFloatForKey("sfxVolume", volume);
    UserDefault::getInstance()->flush();
}

void SoundManager::setBGMVolume(float volume) {
    UserDefault::getInstance()->setFloatForKey("bgmVolume", volume);
    UserDefault::getInstance()->flush();
    updateAllVolumes();
}

void SoundManager::setMasterVolume(float volume) {
    UserDefault::getInstance()->setFloatForKey("masterVolume", volume);
    UserDefault::getInstance()->flush();
    updateAllVolumes();
}

void SoundManager::updateAllVolumes() {
    float bgm = UserDefault::getInstance()->getFloatForKey("bgmVolume", 1.0f);
    float master = UserDefault::getInstance()->getFloatForKey("masterVolume", 1.0f);
    float finalVolume = bgm * master;

    if (bgmId != AudioEngine::INVALID_AUDIO_ID) {
        AudioEngine::setVolume(bgmId, finalVolume);
    }
}
