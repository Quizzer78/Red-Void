#include <cmath>
#include <string>
#include <tuple>
#include <vector>

#include "AbstractIdentifier.h"
#include "AbstractName.h"
#include "random.h"
#include "Ship.h"
#include "weaponvariant.h"

Ship::Ship(std::string name, std::string pluralName, std::string description,
           long cost, int size, double hullPoints, double armorPoints,
           double shieldPoints, double pointDefense, int mobility,
           std::vector<std::tuple<Weapon, int>> weapons)
    : AbstractIdentifier(), AbstractName(name, pluralName, description),
      cost_ { cost }, size_ { size }, hullPoints_ { hullPoints },
      armorPoints_ { armorPoints }, shieldPoints_ { shieldPoints },
      mobility_ { mobility }, initiative_ { 1 }, pointDefense_ { pointDefense },
      weapons_ { weapons }
    {
    }

void Ship::addWeapon(WeaponVariant variant, int number) {
    auto tuple = std::make_tuple(weaponvariant::createWeapon(variant), number);
    weapons_.push_back(tuple);
}
bool Ship::removeWeapon(const std::string& id, int number) {
    return false; //TODO
}
int Ship::rollInitiative() {
    std::uniform_int_distribution<int> distribution { 0, 10 };
    initiative_ = distribution(random::engine) + mobility_;
    return initiative_;
}
void Ship::takeDamage(const Weapon& weapon, int number, double pointDefense) {
    double remainingDamage { weapon.getDamage() * (number * 1.0) };
    if (weapon.isGuided()) {
        remainingDamage *= std::exp(-0.5 * pointDefense);
    }

    remainingDamage *= weapon.getShieldEffectiveness();
    if (remainingDamage > this->shieldPoints_) {
        remainingDamage -= this->shieldPoints_;
        this->shieldPoints_ = 0.0;
    }
    else {
        this->shieldPoints_ -= remainingDamage;
        return;
    }
    remainingDamage *= 1.0 / weapon.getShieldEffectiveness();


    remainingDamage *= weapon.getArmorEffectiveness();
    if (remainingDamage > this->armorPoints_) {
        remainingDamage -= this->armorPoints_;
        this->armorPoints_ = 0.0;
    }
    else {
        this->armorPoints_ -= remainingDamage;
        return;
    }
    remainingDamage *= 1.0 / weapon.getArmorEffectiveness();



    remainingDamage *= weapon.getHullEffectiveness();
    if (remainingDamage > this->hullPoints_) {
        remainingDamage -= this->hullPoints_;
        this->hullPoints_ = -1.0;
    }
    else {
        this->hullPoints_ -= remainingDamage;
        return;
    }
    remainingDamage *= 1.0 / weapon.getHullEffectiveness();
}

long   Ship::getCost()         const {
    return cost_;
}
int    Ship::getSize()         const {
    return size_;
}
double Ship::getHullPoints()   const {
    return hullPoints_;
}
double Ship::getArmorPoints()  const {
    return armorPoints_;
}
double Ship::getShieldPoints() const {
    return shieldPoints_;
}
int    Ship::getMobility()     const {
    return mobility_;
}
int    Ship::getInitiative()   const {
    return initiative_;
}
double Ship::getPointDefense() const {
    return pointDefense_;
}
const  std::vector<std::tuple<Weapon, int>>& Ship::getWeapons() const {
    return weapons_;
}

void Ship::setCost        (long cost) {
    cost_ = cost;
}
void Ship::setHullPoints  (double hullPoints) {
    hullPoints_ = hullPoints;
}
void Ship::setArmorPoints (double armorPoints) {
    armorPoints_ = armorPoints;
}
void Ship::setShieldPoints(double shieldPoints) {
    shieldPoints_ = shieldPoints;
}
void Ship::setInitiative  (int initiative) {
    initiative_ = initiative;
}
