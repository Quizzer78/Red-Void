#include <iostream>
#include <stdexcept>
#include <string>

#include "Fleet.h"
#include "game.h"
#include "input.h"
#include "random.h"
#include "Ship.h"
#include "shipvariant.h"
#include "State.h"





void game::runMain(State& state) {
    std::cout << "Menu:\n"
              << "1: Play\n"
              << "2: Exit\n"
              << "?: ";
    int choice { input::intInput() };

    if (choice == 1) {
        state.currentScene = Scene::SETUP;
    }
    else if (choice == 2) {
        state.currentScene = Scene::EXIT;
    }
}





void game::runSetup(State& state) {
    if (state.enemyFleet.getShips().empty()) {
        long enemyCredits { state.defaultCredits };
        std::uniform_int_distribution<int> distribution
            { 0, static_cast<int>(ShipVariant::MAX_SHIP_VARIANT) - 1 };
        while (enemyCredits >= 500) {
            ShipVariant variant = static_cast<ShipVariant>(distribution(random::engine));
            long cost = shipvariant::costMap.at(variant);
            if (cost <= enemyCredits) {
                state.enemyFleet.addShip(variant);
                enemyCredits -= cost;
            }
        }
    }

    std::cout << "You have: " << state.currentCredits << " credits.\n"
              << "Menu:\n"
              << "1: Add ship\n"
              << "2: Remove ship\n"
              << "3: View fleet\n"
              << "4: Clear fleet\n"
              << "5: Battle\n"
              << "6: Exit\n"
              << "?: ";
    int choice { input::intInput() };

    if (choice == 1) {
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

        std::cout << "You have: " << state.currentCredits << " credits.\n"
                  << "Choose a ship: ";

        ShipVariant shipChoice { input::shipVariantInput() };
        while (true) {

            std::cout << "You chose: " << shipvariant::nameMap.at(shipChoice) << '\n'
                      << "Options:\n"
                      << "1: View description\n"
                      << "2: Add to fleet\n"
                      << "3: Cancel\n"
                      << "?: ";

            int choice { input::intInput() };
            if (choice == 1) {
                std::cout << shipvariant::descriptionMap.at(shipChoice) << '\n';
            }
            else if (choice == 2) {
                long cost { shipvariant::costMap.at(shipChoice) };

                std::cout << "Number?: ";
                int num { input::intInput() };
                if (num * cost <= state.currentCredits) {
                    state.currentCredits -= num * cost;
                    state.playerFleet.addShip(shipChoice, num);
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

    else if (choice == 2) {
        std::cout << "ID?: ";
        std::string id { input::strInput() };
        try {
            long shipCost { state.playerFleet.getShips().at(id).getCost() };
            state.playerFleet.removeShip(id);
            state.currentCredits += shipCost;
        }
        catch (std::out_of_range& e) {
            std::cout << "Invalid ID.\n";
        }
    }

    else if (choice == 3) {
        auto ships = state.playerFleet.getShips();
        for (const auto& pair : ships) {
            const Ship& ship = pair.second;
            std::cout <<  ship.getName() << '\n'
                << "    ID: " << ship.getID() << '\n'
                << "    Cost: " << ship.getCost() << '\n'
                << "    Hull: " << ship.getHullPoints() << '\n'
                << "    Armor: " << ship.getArmorPoints() << '\n'
                << "    Shield: " << ship.getShieldPoints() << '\n'
                << "    Point Defense: " << ship.getPointDefense() << '\n'
                << "    Mobility: " << ship.getMobility() << '\n';
        }
    }

    else if (choice == 4) {
        state.playerFleet.clear();
        state.currentCredits = state.defaultCredits;
    }

    else if (choice == 5) {
        state.currentScene = Scene::BATTLE;
    }

    else if (choice == 6) {
        state.currentScene = Scene::EXIT;
    }
}





void game::runBattle(State& state) {
    auto playerShips = state.playerFleet.getShips();
    auto enemyShips = state.enemyFleet.getShips();

    std::cout << "Initiative Rolls:\n"
              << "Player's:\n";
    for (auto& pair : playerShips) {
        Ship& ship = pair.second;
        std::cout << ship.getName() << ": " << ship.rollInitiative() << '\n';
    }
    std::cout << "\nEnemy's:\n";
    for (auto& pair : enemyShips) {
        Ship& ship = pair.second;
        std::cout << ship.getName() << ": " << ship.rollInitiative() << '\n';
    }

    while (!playerShips.empty() && !enemyShips.empty()) {

    }


    return;
}
