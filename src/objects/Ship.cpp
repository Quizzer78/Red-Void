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
           Faction faction, long cost, int size, double hullPoints,
           double armorPoints, double shieldPoints, double pointDefense,
           int mobility, std::vector<std::tuple<Weapon, int>> weapons)
    : AbstractIdentifier(), AbstractName(name, pluralName, description),
      faction_ { faction }, cost_ { cost }, size_ { size },
      hullPoints_ { hullPoints }, armorPoints_ { armorPoints },
      shieldPoints_ { shieldPoints }, mobility_ { mobility }, initiative_ { 1 },
      pointDefense_ { pointDefense }, weapons_ { weapons }
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
void Ship::takeDamage(const Weapon& weapon, double pointDefense) {
    double remainingDamage { weapon.getDamage() };
    if (weapon.isGuided()) {
        remainingDamage *= std::exp(-0.1 * pointDefense);
    }

    if (shieldPoints_ > 0.0 && remainingDamage > 0.0) {
        remainingDamage *= weapon.getShieldEffectiveness();
        double shield = shieldPoints_;
        shieldPoints_ -= remainingDamage;
        remainingDamage -= shield;
        remainingDamage *= 1.0 / weapon.getShieldEffectiveness();
    }

    if (armorPoints_ > 0.0 && remainingDamage > 0.0) {
        remainingDamage *= weapon.getArmorEffectiveness();
        double armor = armorPoints_;
        armorPoints_ -= remainingDamage;
        remainingDamage -= armor;
        remainingDamage *= 1.0 / weapon.getArmorEffectiveness();
    }

    if (hullPoints_ > 0.0 && remainingDamage > 0.0) {
        remainingDamage *= weapon.getHullEffectiveness();
        double hull = hullPoints_;
        hullPoints_ -= remainingDamage;
        remainingDamage -= hull;
        remainingDamage *= 1.0 / weapon.getHullEffectiveness();
    }
}

Faction Ship::getFaction()      const {
    return faction_;
}
long    Ship::getCost()         const {
    return cost_;
}
int     Ship::getSize()         const {
    return size_;
}
double  Ship::getHullPoints()   const {
    return hullPoints_;
}
double  Ship::getArmorPoints()  const {
    return armorPoints_;
}
double  Ship::getShieldPoints() const {
    return shieldPoints_;
}
int     Ship::getMobility()     const {
    return mobility_;
}
int     Ship::getInitiative()   const {
    return initiative_;
}
double  Ship::getPointDefense() const {
    return pointDefense_;
}
const   std::vector<std::tuple<Weapon, int>>& Ship::getWeapons() const {
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
