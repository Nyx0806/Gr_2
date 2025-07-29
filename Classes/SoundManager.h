#ifndef __SOUND_MANAGER_H__
#define __SOUND_MANAGER_H__

#include "cocos2d.h"
#include "audio/include/AudioEngine.h"

class SoundManager {
public:
    static SoundManager& getInstance();

    void playBackgroundMusic(const std::string& filePath);
    void stopBackgroundMusic();
    void setVolume(float volume);
    void playClickSound();
    void setBGMVolume(float volume);     // âm lượng nhạc nền
    void setSFXVolume(float volume);     // âm lượng hiệu ứng click
    void setMasterVolume(float volume);  // âm lượng tổng
    void updateAllVolumes();             // cập nhật lại âm lượng theo master




private:
    int bgmId = -1;
    bool isPlaying = false;

    SoundManager() {}
    SoundManager(const SoundManager&) = delete;
    void operator=(const SoundManager&) = delete;
};

#endif
