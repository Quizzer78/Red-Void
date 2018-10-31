#include <cmath>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>

#include "AbstractIdentifier.h"
#include "AbstractName.h"
#include "Fleet.h"
#include "Ship.h"
#include "shipvariant.h"

Fleet::Fleet(std::string name, std::string pluralName, std::string description)
    : AbstractIdentifier(), AbstractName(name, pluralName, description),
      ships_ { {} }, totalCost_ { 0 }, totalPointDefense_ { 0.0 }
    {
    }

void Fleet::addShip(ShipVariant variant, int number) {
    for (int i = 0; i < number; ++i) {
        Ship ship = shipvariant::createShip(variant);
        totalPointDefense_ += ship.getPointDefense();
        ships_.insert({ ship.getID(), std::move(ship) });
    }
    return;
}
bool Fleet::removeShip(const std::string& id, int number) {
    try {
        Ship& ship = ships_.at(id);
        totalPointDefense_ -= ship.getPointDefense();
        ships_.erase(id);
        return true;
    }
    catch (std::out_of_range& e) {
        return false;
    }
}
void Fleet::clear() {
    ships_.clear();
    totalPointDefense_ = 0.0;
}

Ship& Fleet::findBestTarget(const Weapon& weapon, int number) {
    double totalDamage { weapon.getDamage() * (number * 1.0) };
    double targetHull, targetArmor, targetShield;
    Ship* bestTarget { nullptr };
    double bestDamageDifference { 1000.0 };
    double remainingDamage { totalDamage };

    for (auto& pair : this->ships_) {
        targetHull = pair.second.getHullPoints();
        targetArmor = pair.second.getArmorPoints();
        targetShield = pair.second.getShieldPoints();
        remainingDamage = totalDamage;

        remainingDamage *= weapon.getShieldEffectiveness();
        remainingDamage -= targetShield;
        remainingDamage *= 1.0 / weapon.getShieldEffectiveness();

        remainingDamage *= weapon.getArmorEffectiveness();
        remainingDamage -= targetArmor;
        remainingDamage *= 1.0 / weapon.getArmorEffectiveness();

        remainingDamage *= weapon.getHullEffectiveness();
        remainingDamage -= targetHull;
        remainingDamage *= 1.0 / weapon.getHullEffectiveness();

        double absoluteDamage { std::abs(remainingDamage) };
        if (absoluteDamage < bestDamageDifference) {
            bestTarget = &(pair.second);
            bestDamageDifference = absoluteDamage;
        }
    }
    return *bestTarget;
}

Ship& Fleet::getShip(const std::string& id) {
    return ships_.at(id);
}
std::unordered_map<std::string, Ship>& Fleet::getShips() {
    return ships_;
}
double Fleet::getTotalPointDefense() const {
    return totalPointDefense_;
}
