#include "AbstractIdentifier.h"
#include "AbstractName.h"
#include "Weapon.h"

Weapon::Weapon(std::string name, std::string pluralName,
               std::string description, double accuracy,
               double damage, bool guided, double hullEffectiveness,
               double armorEffectiveness, double shieldEffectiveness)
    : AbstractIdentifier(), AbstractName(name, pluralName, description),
      accuracy_ { accuracy }, damage_ { damage }, guided_ { guided },
      hullEffectiveness_ { hullEffectiveness },
      armorEffectiveness_ { armorEffectiveness },
      shieldEffectiveness_ { shieldEffectiveness }
    {
    }

double Weapon::getAccuracy() const {
    return accuracy_;
}
double Weapon::getDamage()   const {
    return damage_;
}
bool   Weapon::isGuided()    const {
    return guided_;
}
double Weapon::getHullEffectiveness()   const {
    return hullEffectiveness_;
}
double Weapon::getArmorEffectiveness()  const {
    return armorEffectiveness_;
}
double Weapon::getShieldEffectiveness() const {
    return shieldEffectiveness_;
}
