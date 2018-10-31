#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "Ship.h"
#include "weaponvariant.h"

#ifndef SHIPVARIANT_H
#define SHIPVARIANT_H

enum class ShipVariant {
    DRONE,

    PIRATE_RAIDER,
    PIRATE_BOMBER,
    PIRATE_SLOOP,
    PIRATE_GALLEON,

    IMPERIAL_FIGHTER,
    IMPERIAL_FRIGATE,
    IMPERIAL_CRUISER,
    IMPERIAL_DREADNOUGHT,

    MAX_SHIP_VARIANT,
};

namespace shipvariant {
    Ship createShip(ShipVariant variant);
    void initializeMaps(); // all ship parameters defined here

    extern std::map<ShipVariant, int> numberMadeMap;
    extern std::map<ShipVariant, std::string> nameMap;
    extern std::map<ShipVariant, std::string> pluralNameMap;
    extern std::map<ShipVariant, std::string> descriptionMap;
    extern std::map<ShipVariant, long> costMap;
    extern std::map<ShipVariant, int> sizeMap;
    extern std::map<ShipVariant, double> hullPointsMap;
    extern std::map<ShipVariant, double> armorPointsMap;
    extern std::map<ShipVariant, double> shieldPointsMap;
    extern std::map<ShipVariant, double> pointDefenseMap;
    extern std::map<ShipVariant, int> mobilityMap;
    extern std::map<ShipVariant, std::vector<std::tuple<WeaponVariant, int>>> weaponsMap;
};

#endif
