#include <iostream>
#include <string>

#include "Fleet.h"
#include "random.h"
#include "Ship.h"
#include "shipvariant.h"

enum class Scene {
    MAIN,
    SETUP,
    BATTLE,
    EXIT,
};

struct State {
    Scene currentScene;
    long currentCredits;
    Fleet playerFleet;
    Fleet enemyFleet;
};

int intInput() {
    int i;

    while (true) {
        if (std::cin >> i) {
            return i;
        }
        else {
            std::cout << "Please enter a valid integer\n";
            std::cin.clear();
            std::cin.ignore(255, '\n');
        }
    }
}

ShipVariant shipVariantInput() {
    int i;

    while (true) {
        if (std::cin >> i) {
            if (i < static_cast<int>(ShipVariant::MAX_SHIP_VARIANT)) {
                return static_cast<ShipVariant>(i);
            }
            else {
                std::cout << "Input out of bounds.\n";
            }
        }
        else {
            std::cout << "Please enter a valid integer.\n";
            std::cin.clear();
            std::cin.ignore(255, '\n');
        }
    }
}

int main() {
    shipvariant::initializeMaps();

    State gameState {
        Scene::MAIN, // currentScene
        500000, // currentCredits
        { "Player Fleet", "Player Fleets", "This is the player's fleet." },
        { "Enemy Fleet", "Enemy Fleets", "This is the enemy's fleet." }
    };

    std::cout << "Welcome to Red Void version 0.1.\n";

    while (true) {


        // MAIN
        while (gameState.currentScene == Scene::MAIN) {
            std::cout << "Menu:\n"
                      << "1: Play\n"
                      << "2: Exit\n"
                      << "?: ";

            int choice { intInput() };
            if (choice == 1) {
                gameState.currentScene = Scene::SETUP;
            }
            else if (choice == 2) {
                gameState.currentScene = Scene::EXIT;
            }
        }


        // SETUP
        while (gameState.currentScene == Scene::SETUP) {
            ShipVariant variant;
            for (int i = 0; i < static_cast<int>(ShipVariant::MAX_SHIP_VARIANT); ++i) {
                variant = static_cast<ShipVariant>(i);
                std::cout << i << ". "
                    << shipvariant::nameMap.at(variant) << '\n'
                    << "    Cost: " << shipvariant::costMap.at(variant) << '\n'
                    << "    Hull: " << shipvariant::hullPointsMap.at(variant) << '\n'
                    << "    Armor: " << shipvariant::armorPointsMap.at(variant) << '\n'
                    << "    Shield: " << shipvariant::shieldPointsMap.at(variant) << '\n'
                    << "    Point Defense: " << shipvariant::pointDefenseMap.at(variant) << '\n'
                    << "    Mobility: " << shipvariant::mobilityMap.at(variant) << '\n';
            }

            std::cout << "You have: " << gameState.currentCredits << " credits.\n"
                      << "Choose a ship: ";

            ShipVariant shipChoice { shipVariantInput() };
            while (true) {

                std::cout << "You chose: " << shipvariant::nameMap.at(shipChoice) << '\n'
                          << "Options:\n"
                          << "1: View description\n"
                          << "2: Add to fleet\n"
                          << "3: Cancel\n"
                          << "?: ";

                int choice { intInput() };
                if (choice == 1) {
                    std::cout << shipvariant::descriptionMap.at(shipChoice) << '\n';
                }
                else if (choice == 2) {
                    long cost { shipvariant::costMap.at(shipChoice) };

                    std::cout << "Number?: ";
                    int num { intInput() };
                    if (num * cost <= gameState.currentCredits) {
                        gameState.currentCredits -= num * cost;
                        gameState.playerFleet.addShip(shipChoice, num);
                        std::cout << "Ship(s) added.\n";
                    }
                    else {
                        std::cout << "Not enough credits.\n";
                    }

                    break;
                }
                else if (choice == 3) {
                    break;
                }
            }
        }


        // BATTLE
        while (gameState.currentScene == Scene::BATTLE) {
            return 0;
        }


        // EXIT
        if (gameState.currentScene == Scene::EXIT) {
            return 0;
        }



    }
}
