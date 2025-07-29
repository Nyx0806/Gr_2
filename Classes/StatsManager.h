// MODULE 5: StatsManager – Th?ng kê k?t qu? ch?i
#pragma once
class StatsManager {
public:
    static StatsManager* getInstance();

    void loadStats();     // T?i th?ng kê t? b? nh?
    void saveStats();     // L?u th?ng kê
    void resetStats();    // Xoá th?ng kê

    void recordWin(int playerId);        // Ghi l?i tr?n th?ng
    void recordDraw();                   // Ghi l?i tr?n hoà
    void recordAbandon(int playerId);    // Ghi l?i b? cu?c

    int getWins(int playerId);
    int getDraws();
    int getAbandons(int playerId);

    void debugPrintStats();              // In ra stats hiện tại
    void forceReloadStats();            // Force reload từ file

    

private:
    StatsManager();
    int _wins[2];
    int _draws;
    int _abandons[2];
};