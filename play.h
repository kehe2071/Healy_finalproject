#ifndef PLAY_H
#define PLAY_H

#include "player.h"
#include "char.h"
#include "item.h"

using namespace std;

class Game {
private:
    Player player;
    int currentDay;
    int maxDays;
    int jojaInfluence;

    bool bundleChecks[5];
    string bundleNames[5];
    Character npcs[4];
    string locations[5];

public:
    Game();
    void startGame();
    void gameLoop();
    
    void displayDashboard();
    void displayMap();
    // void displayBundle();

    void moveLocation();
    void interactWithNPC();
    void visitCommunityCenter();
    void visitJojaMart();
    void forageOrWork();
    void endDay();

    bool checkWin();
    void displayEnding();
};

#endif