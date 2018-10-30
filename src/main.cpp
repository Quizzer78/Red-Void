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

    State gameState {
        Scene::MAIN, // currentScene
        500000, // currentCredits
        500000,
        { "Player Fleet", "Player Fleets", "This is the player's fleet." },
        { "Enemy Fleet", "Enemy Fleets", "This is the enemy's fleet." }
    };

    std::cout << "Welcome to Red Void version 0.1.\n";

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
