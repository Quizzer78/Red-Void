#include <string>
#include <tuple>
#include <vector>

#include "AbstractIdentifier.h"
#include "AbstractName.h"
#include "Faction.h"
#include "weaponvariant.h"

#ifndef SHIP_H
#define SHIP_H

class Ship : public AbstractIdentifier, public AbstractName {
    public:
        Ship(std::string name, std::string pluralName, std::string description,
             Faction faction_, long cost, int size, double hullPoints,
             double armorPoints, double shieldPoints, double pointDefense,
             int mobility, std::vector<std::tuple<Weapon, int>> weapons);

        void addWeapon(WeaponVariant variant, int number=1);
        bool removeWeapon(const std::string& id, int number=-1);
        int rollInitiative();
        void takeDamage(const Weapon& weapon, double pointDefense);

        Faction getFaction()      const;
        long    getCost()         const;
        int     getSize()         const;
        double  getHullPoints()   const;
        double  getArmorPoints()  const;
        double  getShieldPoints() const;
        int     getMobility()     const;
        int     getInitiative()   const;
        double  getPointDefense() const;
        const   std::vector<std::tuple<Weapon, int>>& getWeapons() const;

        void setCost        (long cost);
        void setHullPoints  (double hullPoints);
        void setArmorPoints (double armorPoints);
        void setShieldPoints(double shieldPoints);
        void setInitiative  (int initiative);

    private:
        Faction faction_;
        long   cost_;
        int    size_;
        double hullPoints_;
        double armorPoints_;
        double shieldPoints_;
        int    mobility_;
        int    initiative_;
        double pointDefense_;
        std::vector<std::tuple<Weapon, int>> weapons_;
};

#endif
