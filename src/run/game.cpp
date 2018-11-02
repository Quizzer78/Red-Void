#include <ios>
#include <iomanip>
#include <iostream>
#include <queue>
#include <stdexcept>
#include <string>
#include <vector>
#include <Windows.h>

#include "Faction.h"
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

        // CREATE ENEMY FLEET
        if (state.enemyFleet.getShips().empty()) {
            long enemyCredits { state.defaultCredits };
            std::uniform_int_distribution<int> distributionFaction
                { 1, static_cast<int>(Faction::MAX_FACTION) - 1 };

            Faction faction = static_cast<Faction>(distributionFaction(random::engine));

            std::uniform_int_distribution<int> distributionShip
                { 0, static_cast<int>(ShipVariant::MAX_SHIP_VARIANT) - 1 };

            while (enemyCredits >= shipvariant::costMap.at(ShipVariant::DRONE)) {
                ShipVariant variant = static_cast<ShipVariant>(distributionShip(random::engine));
                long cost = shipvariant::costMap.at(variant);
                if (cost <= enemyCredits && (shipvariant::factionMap.at(variant) == faction
                    || shipvariant::factionMap.at(variant) == Faction::NONE)) {

                    state.enemyFleet.addShip(variant);
                    enemyCredits -= cost;
                }
            }
        }

        state.currentScene = Scene::BATTLE;
    }

    // EXIT
    else if (choice == 6) {
        state.currentScene = Scene::EXIT;
    }
}





void game::runBattle(State& state) {
    const auto comp =
        [](const Ship* s1, const Ship* s2)
        { return s1->getInitiative() < s2->getInitiative(); };
    std::priority_queue<Ship*, std::vector<Ship*>, decltype(comp)> orderQueue { comp };

    std::cout << "Initiative Rolls:\n"
              << "Player's:\n";
    for (auto& pair : state.playerFleet.getShips()) {
        Ship& ship = pair.second;
        std::cout << ship.getName() << ": " << ship.rollInitiative() << '\n';
        orderQueue.push(&ship);
    }
    std::cout << "\nEnemy's:\n";
    for (auto& pair : state.enemyFleet.getShips()) {
        Ship& ship = pair.second;
        std::cout << ship.getName() << ": " << ship.rollInitiative() << '\n';
        orderQueue.push(&ship);
    }
    Sleep(5000);
    std::deque<Ship*> initiativeDeque;
    while (!orderQueue.empty()) {
        initiativeDeque.push_back(orderQueue.top());
        orderQueue.pop();
    }



    Ship* activeShip = nullptr;

    auto* targetShips = &(state.playerFleet.getShips());
    auto* targetFleet = &(state.playerFleet);

    while (!state.playerFleet.getShips().empty() && !state.enemyFleet.getShips().empty()) {
        activeShip = initiativeDeque.front();
        initiativeDeque.pop_front();

        std::cout << activeShip->getName() << "'s turn!\n";
        std::cout
            << "    Hull: " << activeShip->getHullPoints() << '\n'
            << "    Armor: " << activeShip->getArmorPoints() << '\n'
            << "    Shield: " << activeShip->getShieldPoints() << '\n'
            << "    Point Defense: " << activeShip->getPointDefense() << '\n'
            << "    Mobility: " << activeShip->getMobility() << '\n';
        Sleep(500);

        // Check if activeShip is in playerFleet
        if (state.playerFleet.getShips().find(activeShip->getID()) != state.playerFleet.getShips().end()) {
            targetShips = &(state.enemyFleet.getShips());
            targetFleet = &(state.enemyFleet);
        }
        else {
            targetShips = &(state.playerFleet.getShips());
            targetFleet = &(state.playerFleet);
        }

        // Shoot with each weapon bank
        for (const auto& weaponPair : activeShip->getWeapons()) {
            const Weapon& weapon = std::get<0>(weaponPair);
            int num = std::get<1>(weaponPair);
            for (int i = 0; i < num; ++i) {
                if (targetShips->empty()) {
                    break;
                }
                // Find target
                Ship& target = targetFleet->findBestTarget(weapon);


                std::cout << activeShip->getName() << " fires its "
                          << weapon.getName() << " at " << target.getName() << "!\n";

                Sleep(500);


                // Attempt attack
                std::uniform_real_distribution<double> distribution { 0.0, 1.0 };
                if (distribution(random::engine) <
                    weapon.getAccuracy() * (10.0 / (target.getMobility() + 10.0))) {

                    double initialHealth[]
                        { target.getHullPoints(), target.getArmorPoints(),
                        target.getShieldPoints() };

                    // Deal damage
                    target.takeDamage(weapon, targetFleet->getTotalPointDefense());

                    double finalHealth[]
                        { target.getHullPoints(), target.getArmorPoints(),
                        target.getShieldPoints() };

                    std::cout << "Hit! (" << initialHealth[0] << ", "
                        << initialHealth[1] << ", " << initialHealth[2] << ") -> ("
                        << finalHealth[0] << ", " << finalHealth[1] << ", "
                        << finalHealth[2] << ")\n";

                    if (target.getHullPoints() <= 0.0) {
                        std::cout << target.getName() << " is destroyed!\n";

                        if(!targetFleet->removeShip(target.getID())) {
                            std::cerr << "Error, ship not removed\n";
                        }
                        for (auto it = initiativeDeque.begin(); it != initiativeDeque.end(); ) {
                            if ((*it)->getID() == target.getID()) {
                                it = initiativeDeque.erase(it);
                            }
                            else {
                                ++it;
                            }
                        }
                    }
                }
                else {
                    std::cout << "Miss!\n";
                }
                Sleep(500);
            }
        }
        initiativeDeque.push_back(activeShip);
    }
    if (state.playerFleet.getShips().empty()) {
        std::cout << "Enemy win!\n";
    }
    else if (state.enemyFleet.getShips().empty()) {
        std::cout << "Player win!\n";
    }
    state.currentCredits = state.defaultCredits;
    state.currentScene = Scene::MAIN;
}
