// MODULE 8: SoundManager – Quản lý âm thanh
#pragma once
class SoundManager {
public:
    static SoundManager* getInstance();
    void playMoveSound();   // Âm thanh khi đánh cờ
    void playWinSound();    // Âm thanh khi chiến thắng
    void setMuted(bool m);  // Bật/tắt tiếng
    bool isMuted();

private:
    bool _muted;
    SoundManager();
};