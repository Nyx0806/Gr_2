#include "SoundManager.h"

using namespace cocos2d;

SoundManager& SoundManager::getInstance() {
    static SoundManager instance;
    return instance;
}

void SoundManager::playBackgroundMusic(const std::string& filePath) {
    if (!isPlaying) {
        bgmId = AudioEngine::play2d(filePath, true); // true = loop
        isPlaying = true;
    }
}

void SoundManager::stopBackgroundMusic() {
    if (isPlaying && bgmId != AudioEngine::INVALID_AUDIO_ID) {
        AudioEngine::stop(bgmId);
        isPlaying = false;
    }
}

void SoundManager::setVolume(float volume) {
    if (bgmId != AudioEngine::INVALID_AUDIO_ID) {
        AudioEngine::setVolume(bgmId, volume);
    }
}

