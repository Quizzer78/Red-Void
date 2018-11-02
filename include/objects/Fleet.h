#include <string>
#include <unordered_map>

#include "AbstractIdentifier.h"
#include "AbstractName.h"
#include "Ship.h"
#include "shipvariant.h"

#ifndef FLEET_H
#define FLEET_H

class Fleet : public AbstractIdentifier, public AbstractName {
    public:
        Fleet(std::string name, std::string pluralName,
              std::string description);

        void addShip(ShipVariant variant, int number=1);
        bool removeShip(const std::string& id, int number=-1);
        void clear();

        // Minimizes distance between damage and remaining health, accounting
        // for effectiveness
        Ship& findBestTarget(const Weapon& weapon);

        Ship& getShip(const std::string& id);
        std::unordered_map<std::string, Ship>& getShips();
        double getTotalPointDefense() const;

    private:
        std::unordered_map<std::string, Ship> ships_;
        long totalCost_;
        double totalPointDefense_;
};

#endif
