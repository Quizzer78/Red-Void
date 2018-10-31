#include <iostream>
#include <queue>
#include <stdexcept>
#include <string>
#include <vector>
#include <Windows.h>

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

    // CREATE ENEMY FLEET
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

    // ADD SHIP
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

    // REMOVE SHIP
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

    // VIEW FLEET
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

    // CLEAR FLEET
    else if (choice == 4) {
        state.playerFleet.clear();
        state.currentCredits = state.defaultCredits;
    }

    // GO TO BATTLE
    else if (choice == 5) {
        state.currentScene = Scene::BATTLE;
    }

    // EXIT
    else if (choice == 6) {
        state.currentScene = Scene::EXIT;
    }
}





void game::runBattle(State& state) {
    auto& playerShips = state.playerFleet.getShips();
    auto& enemyShips = state.enemyFleet.getShips();

    const auto comp =
        [](const Ship* s1, const Ship* s2)
        { return s1->getInitiative() < s2->getInitiative(); };
    std::priority_queue<Ship*, std::vector<Ship*>, decltype(comp)> initiativeQueue { comp };

    std::cout << "Initiative Rolls:\n"
              << "Player's:\n";
    for (auto& pair : playerShips) {
        Ship& ship = pair.second;
        std::cout << ship.getName() << ": " << ship.rollInitiative() << '\n';
        initiativeQueue.push(&ship);
    }
    std::cout << "\nEnemy's:\n";
    for (auto& pair : enemyShips) {
        Ship& ship = pair.second;
        std::cout << ship.getName() << ": " << ship.rollInitiative() << '\n';
        initiativeQueue.push(&ship);
    }
    Sleep(500);

    std::vector<Ship*> usedShips;
    Ship* activeShip = nullptr;

    auto& targetShips = playerShips;
    auto& targetFleet = state.playerFleet;

    while (!playerShips.empty() && !enemyShips.empty()) {

        if (initiativeQueue.empty()) {
            for (Ship* ship : usedShips) {
                initiativeQueue.push(ship);
            }
            usedShips.clear();
        }

        do {
            activeShip = initiativeQueue.top();
            initiativeQueue.pop();
        } while (activeShip == nullptr || activeShip->getHullPoints() < 0.0);
        if (initiativeQueue.empty()) {
            continue;
        }

        std::cout << activeShip->getName() << "'s turn!\n";
        std::cout
            << "    Hull: " << activeShip->getHullPoints() << '\n'
            << "    Armor: " << activeShip->getArmorPoints() << '\n'
            << "    Shield: " << activeShip->getShieldPoints() << '\n'
            << "    Point Defense: " << activeShip->getPointDefense() << '\n'
            << "    Mobility: " << activeShip->getMobility() << '\n';
        Sleep(500);

        // Check if activeShip is in playerFleet
        if (playerShips.find(activeShip->getID()) != playerShips.end()) {
            targetShips = enemyShips;
            targetFleet = state.enemyFleet;
        }
        else {
            targetShips = playerShips;
            targetFleet = state.playerFleet;
        }

        // Shoot with each weapon bank
        for (const auto& weaponPair : activeShip->getWeapons()) {
            const Weapon& weapon = std::get<0>(weaponPair);
            int num = std::get<1>(weaponPair);
            if (targetShips.empty()) {
                break;
            }
            // Find target
            Ship& target = targetFleet.findBestTarget(weapon, num);

            if (num == 1) {
                std::cout << activeShip->getName() << " fires its "
                          << weapon.getName() << " at " << target.getName() << "!\n";
            }
            else {
                std::cout << activeShip->getName() << " fires its " << num << " "
                          << weapon.getPluralName() << " at " << target.getName() << "!\n";
            }
            Sleep(500);


            // Attempt attack
            std::uniform_real_distribution<double> distribution { 0.0, 1.0 };
            if (distribution(random::engine) <
                weapon.getAccuracy() * (10.0 / (target.getMobility() + 10.0))) {

                std::cout << activeShip->getName() << " hits!\n";

                // Deal damage
                target.takeDamage(weapon, num, targetFleet.getTotalPointDefense());

                if (target.getHullPoints() < 0.0) {
                    std::cout << target.getName() << " is destroyed!\n";

                    if(!targetFleet.removeShip(target.getID())) {
                        std::cerr << "Error, ship not removed\n";
                    }
                }
            }
            else {
                std::cout << activeShip->getName() << " misses!\n";
            }
            Sleep(500);
        }
        for (auto it = usedShips.begin(); it != usedShips.end();) {
            if (*it == nullptr) {
                it = usedShips.erase(it);
            }
            else {
                ++it;
            }
        }

        usedShips.push_back(activeShip);
    }
    if (playerShips.empty()) {
        std::cout << "Enemy win!\n";
    }
    else if (enemyShips.empty()) {
        std::cout << "Player win!\n";
    }
    state.currentScene = Scene::MAIN;
}
