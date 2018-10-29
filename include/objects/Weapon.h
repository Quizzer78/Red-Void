#include "AbstractIdentifier.h"
#include "AbstractName.h"

#ifndef WEAPON_H
#define WEAPON_H

class Weapon : public AbstractIdentifier, public AbstractName {
    public:
        Weapon(std::string name, std::string pluralName,
               std::string description, double accuracy,
               double damage, bool guided, double hullEffectiveness,
               double armorEffectiveness, double shieldEffectiveness);

        double getAccuracy() const;
        double getDamage()   const;
        bool   isGuided()    const;
        double getHullEffectiveness()   const;
        double getArmorEffectiveness()  const;
        double getShieldEffectiveness() const;

    private:
        double accuracy_;
        double damage_;
        bool   guided_;
        double hullEffectiveness_;
        double armorEffectiveness_;
        double shieldEffectiveness_;
};

#endif
