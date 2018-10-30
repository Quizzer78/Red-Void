#include "Fleet.h"

#ifndef STATE_H
#define STATE_H

enum class Scene {
    MAIN,
    SETUP,
    BATTLE,
    EXIT,
};

struct State {
    Scene currentScene;
    long currentCredits;
    long defaultCredits;
    Fleet playerFleet;
    Fleet enemyFleet;
};

#endif
