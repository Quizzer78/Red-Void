#include <iostream>
#include <string>

#include "Fleet.h"
#include "game.h"
#include "random.h"
#include "Ship.h"
#include "shipvariant.h"
#include "State.h"

int main() {
    shipvariant::initializeMaps();
    weaponvariant::initializeMaps();

    State gameState {
        Scene::MAIN, // currentScene
        0, // currentCredits
        100000,
        { "Player Fleet", "Player Fleets", "This is the player's fleet." },
        { "Enemy Fleet", "Enemy Fleets", "This is the enemy's fleet." }
    };

    std::cout << "Welcome to Red Void version 0.1.\n";
    gameState.currentCredits = gameState.defaultCredits;

    while (true) {


        // MAIN
        while (gameState.currentScene == Scene::MAIN) {
            game::runMain(gameState);
        }


        // SETUP
        while (gameState.currentScene == Scene::SETUP) {
            game::runSetup(gameState);
        }


        // BATTLE
        while (gameState.currentScene == Scene::BATTLE) {
            game::runBattle(gameState);
        }


        // EXIT
        if (gameState.currentScene == Scene::EXIT) {
            return 0;
        }



    }
}
