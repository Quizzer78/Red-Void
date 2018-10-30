#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

#include "shipvariant.h"
#include "weaponvariant.h"

std::map<ShipVariant, std::string> shipvariant::nameMap;
std::map<ShipVariant, std::string> shipvariant::pluralNameMap;
std::map<ShipVariant, std::string> shipvariant::descriptionMap;
std::map<ShipVariant, long> shipvariant::costMap;
std::map<ShipVariant, int> shipvariant::sizeMap;
std::map<ShipVariant, double> shipvariant::hullPointsMap;
std::map<ShipVariant, double> shipvariant::armorPointsMap;
std::map<ShipVariant, double> shipvariant::shieldPointsMap;
std::map<ShipVariant, double> shipvariant::pointDefenseMap;
std::map<ShipVariant, int> shipvariant::mobilityMap;
std::map<ShipVariant, std::vector<std::tuple<Weapon, int>>> shipvariant::weaponsMap;

Ship shipvariant::createShip(ShipVariant variant) {
    return
        {
        shipvariant::nameMap.at(variant),
        shipvariant::pluralNameMap.at(variant),
        shipvariant::descriptionMap.at(variant),
        shipvariant::costMap.at(variant),
        shipvariant::sizeMap.at(variant),
        shipvariant::hullPointsMap.at(variant),
        shipvariant::armorPointsMap.at(variant),
        shipvariant::shieldPointsMap.at(variant),
        shipvariant::pointDefenseMap.at(variant),
        shipvariant::mobilityMap.at(variant),
        shipvariant::weaponsMap.at(variant)
        };
}

void shipvariant::initializeMaps() {
    typedef std::vector<std::tuple<Weapon, int>> weaponvec;
    ShipVariant variant { ShipVariant::MAX_SHIP_VARIANT };

    variant = ShipVariant::PIRATE_FIGHTER;
    shipvariant::        nameMap.emplace( variant, "Pirate Fighter" );
    shipvariant::  pluralNameMap.emplace( variant, "Pirate Fighters" );
    shipvariant:: descriptionMap.emplace( variant,
        "A pirate fighter." );
    shipvariant::        costMap.emplace( variant, 800 );
    shipvariant::        sizeMap.emplace( variant, 1 );
    shipvariant::  hullPointsMap.emplace( variant, 5.0 );
    shipvariant:: armorPointsMap.emplace( variant, 3.0 );
    shipvariant::shieldPointsMap.emplace( variant, 0.0 );
    shipvariant::pointDefenseMap.emplace( variant, 0.0 );
    shipvariant::    mobilityMap.emplace( variant, 8 );
    shipvariant::     weaponsMap.emplace( variant,
        weaponvec{ { weaponvariant::createWeapon(WeaponVariant::TEST), 1 } }
    );

    variant = ShipVariant::PIRATE_GALLEON;
    shipvariant::        nameMap.emplace( variant, "Pirate Galleon" );
    shipvariant::  pluralNameMap.emplace( variant, "Pirate Galleons" );
    shipvariant:: descriptionMap.emplace( variant,
        "A pirate galleon." );
    shipvariant::        costMap.emplace( variant, 80000 );
    shipvariant::        sizeMap.emplace( variant, 4 );
    shipvariant::  hullPointsMap.emplace( variant, 30.0 );
    shipvariant:: armorPointsMap.emplace( variant, 40.0 );
    shipvariant::shieldPointsMap.emplace( variant, 0.0 );
    shipvariant::pointDefenseMap.emplace( variant, 1.5 );
    shipvariant::    mobilityMap.emplace( variant, 4 );
    shipvariant::     weaponsMap.emplace( variant,
        weaponvec{ { weaponvariant::createWeapon(WeaponVariant::TEST), 1 } }
    );
}
