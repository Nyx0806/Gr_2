// MODULE 5: StatsManager � Th?ng k� k?t qu? ch?i
#pragma once
class StatsManager {
public:
    static StatsManager* getInstance();

    void loadStats();     // T?i th?ng k� t? b? nh?
    void saveStats();     // L?u th?ng k�
    void resetStats();    // Xo� th?ng k�

    void recordWin(int playerId);        // Ghi l?i tr?n th?ng
    void recordDraw();                   // Ghi l?i tr?n ho�
    void recordAbandon(int playerId);    // Ghi l?i b? cu?c

    int getWins(int playerId);
    int getDraws();
    int getAbandons(int playerId);

    

private:
    StatsManager();
    int _wins[2];
    int _draws;
    int _abandons[2];
};