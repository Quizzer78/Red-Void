#include <map>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

#include "shipvariant.h"
#include "weaponvariant.h"

std::map<ShipVariant, int> shipvariant::numberMadeMap;
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
std::map<ShipVariant, std::vector<std::tuple<WeaponVariant, int>>> shipvariant::weaponsMap;

Ship shipvariant::createShip(ShipVariant variant) {
    const std::vector<std::tuple<WeaponVariant, int>>& mapWeapons
        = shipvariant::weaponsMap.at(variant);
    std::vector<std::tuple<Weapon, int>> shipWeapons {};
    for (const auto& pair : mapWeapons) {
        shipWeapons.push_back(std::make_tuple(weaponvariant::createWeapon(std::get<0>(pair)), std::get<1>(pair)));
    }
    Ship returnShip {
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
        shipWeapons
        };
    if (shipvariant::numberMadeMap.at(variant) != 0) {
        returnShip.setName(returnShip.getName() + " " + std::to_string(shipvariant::numberMadeMap.at(variant)));
    }
    shipvariant::numberMadeMap.at(variant) += 1;

    return returnShip;
}

void shipvariant::initializeMaps() {
    typedef std::vector<std::tuple<WeaponVariant, int>> weaponvec;
    ShipVariant variant { ShipVariant::MAX_SHIP_VARIANT };

    variant = ShipVariant::DRONE;
    shipvariant::  numberMadeMap.emplace( variant, 0 );
    shipvariant::        nameMap.emplace( variant, "Drone" );
    shipvariant::  pluralNameMap.emplace( variant, "Drones" );
    shipvariant:: descriptionMap.emplace( variant,
        "A drone." );
    shipvariant::        costMap.emplace( variant, 500 );
    shipvariant::        sizeMap.emplace( variant, 1 );
    shipvariant::  hullPointsMap.emplace( variant, 1.0 );
    shipvariant:: armorPointsMap.emplace( variant, 0.0 );
    shipvariant::shieldPointsMap.emplace( variant, 0.0 );
    shipvariant::pointDefenseMap.emplace( variant, 0.0 );
    shipvariant::    mobilityMap.emplace( variant, 7 );
    shipvariant::     weaponsMap.emplace( variant,
        weaponvec{ { WeaponVariant::MINI_LASER, 1 } }
    );

    variant = ShipVariant::PIRATE_RAIDER;
    shipvariant::  numberMadeMap.emplace( variant, 0 );
    shipvariant::        nameMap.emplace( variant, "Pirate Raider" );
    shipvariant::  pluralNameMap.emplace( variant, "Pirate Raiders" );
    shipvariant:: descriptionMap.emplace( variant,
        "A pirate raider." );
    shipvariant::        costMap.emplace( variant, 800 );
    shipvariant::        sizeMap.emplace( variant, 1 );
    shipvariant::  hullPointsMap.emplace( variant, 5.0 );
    shipvariant:: armorPointsMap.emplace( variant, 3.0 );
    shipvariant::shieldPointsMap.emplace( variant, 0.0 );
    shipvariant::pointDefenseMap.emplace( variant, 0.0 );
    shipvariant::    mobilityMap.emplace( variant, 8 );
    shipvariant::     weaponsMap.emplace( variant,
        weaponvec{ { WeaponVariant::AUTOCANNON, 1 },
                   { WeaponVariant::INTERCEPTOR_MISSILE, 1 } }
    );

    variant = ShipVariant::PIRATE_BOMBER;
    shipvariant::  numberMadeMap.emplace( variant, 0 );
    shipvariant::        nameMap.emplace( variant, "Pirate Bomber" );
    shipvariant::  pluralNameMap.emplace( variant, "Pirate Bombers" );
    shipvariant:: descriptionMap.emplace( variant,
        "A pirate bomber." );
    shipvariant::        costMap.emplace( variant, 1400 );
    shipvariant::        sizeMap.emplace( variant, 2 );
    shipvariant::  hullPointsMap.emplace( variant, 7.0 );
    shipvariant:: armorPointsMap.emplace( variant, 4.0 );
    shipvariant::shieldPointsMap.emplace( variant, 0.0 );
    shipvariant::pointDefenseMap.emplace( variant, 0.0 );
    shipvariant::    mobilityMap.emplace( variant, 6 );
    shipvariant::     weaponsMap.emplace( variant,
        weaponvec{ { WeaponVariant::TORPEDO, 1 } }
    );

    variant = ShipVariant::PIRATE_SLOOP;
    shipvariant::  numberMadeMap.emplace( variant, 0 );
    shipvariant::        nameMap.emplace( variant, "Pirate Sloop" );
    shipvariant::  pluralNameMap.emplace( variant, "Pirate Sloops" );
    shipvariant:: descriptionMap.emplace( variant,
        "A pirate sloop." );
    shipvariant::        costMap.emplace( variant, 8000 );
    shipvariant::        sizeMap.emplace( variant, 3 );
    shipvariant::  hullPointsMap.emplace( variant, 15.0 );
    shipvariant:: armorPointsMap.emplace( variant, 10.0 );
    shipvariant::shieldPointsMap.emplace( variant, 0.0 );
    shipvariant::pointDefenseMap.emplace( variant, 0.2 );
    shipvariant::    mobilityMap.emplace( variant, 6 );
    shipvariant::     weaponsMap.emplace( variant,
        weaponvec{ { WeaponVariant::SMALL_RAILGUN, 1 },
                   { WeaponVariant::LIGHT_MISSILE, 2 } }
    );

    variant = ShipVariant::PIRATE_GALLEON;
    shipvariant::  numberMadeMap.emplace( variant, 0 );
    shipvariant::        nameMap.emplace( variant, "Pirate Galleon" );
    shipvariant::  pluralNameMap.emplace( variant, "Pirate Galleons" );
    shipvariant:: descriptionMap.emplace( variant,
        "A pirate galleon." );
    shipvariant::        costMap.emplace( variant, 80000 );
    shipvariant::        sizeMap.emplace( variant, 4 );
    shipvariant::  hullPointsMap.emplace( variant, 30.0 );
    shipvariant:: armorPointsMap.emplace( variant, 40.0 );
    shipvariant::shieldPointsMap.emplace( variant, 5.0 );
    shipvariant::pointDefenseMap.emplace( variant, 1.0 );
    shipvariant::    mobilityMap.emplace( variant, 4 );
    shipvariant::     weaponsMap.emplace( variant,
        weaponvec{ { WeaponVariant::AUTOCANNON, 3 },
                   { WeaponVariant::AUTOCANNON, 3 },
                   { WeaponVariant::EVISCERATOR_FLAK, 1 } }
    );

    variant = ShipVariant::IMPERIAL_FIGHTER;
    shipvariant::  numberMadeMap.emplace( variant, 0 );
    shipvariant::        nameMap.emplace( variant, "Imperial Fighter" );
    shipvariant::  pluralNameMap.emplace( variant, "Imperial Fighters" );
    shipvariant:: descriptionMap.emplace( variant,
        "An Imperial fighter." );
    shipvariant::        costMap.emplace( variant, 1600 );
    shipvariant::        sizeMap.emplace( variant, 1 );
    shipvariant::  hullPointsMap.emplace( variant, 7.0 );
    shipvariant:: armorPointsMap.emplace( variant, 4.0 );
    shipvariant::shieldPointsMap.emplace( variant, 4.0 );
    shipvariant::pointDefenseMap.emplace( variant, 0.0 );
    shipvariant::    mobilityMap.emplace( variant, 7 );
    shipvariant::     weaponsMap.emplace( variant,
        weaponvec{ { WeaponVariant::PULSE_LASER, 2 },
                   { WeaponVariant::INTERCEPTOR_MISSILE, 1 },
                   { WeaponVariant::INTERCEPTOR_MISSILE, 1 } }
    );

    variant = ShipVariant::IMPERIAL_FRIGATE;
    shipvariant::  numberMadeMap.emplace( variant, 0 );
    shipvariant::        nameMap.emplace( variant, "Imperial Frigate" );
    shipvariant::  pluralNameMap.emplace( variant, "Imperial Frigates" );
    shipvariant:: descriptionMap.emplace( variant,
        "An Imperial frigate." );
    shipvariant::        costMap.emplace( variant, 11000 );
    shipvariant::        sizeMap.emplace( variant, 3 );
    shipvariant::  hullPointsMap.emplace( variant, 20.0 );
    shipvariant:: armorPointsMap.emplace( variant, 10.0 );
    shipvariant::shieldPointsMap.emplace( variant, 10.0 );
    shipvariant::pointDefenseMap.emplace( variant, 1.5 );
    shipvariant::    mobilityMap.emplace( variant, 4 );
    shipvariant::     weaponsMap.emplace( variant,
        weaponvec{ { WeaponVariant::SMALL_RAILGUN, 2 },
                   { WeaponVariant::LIGHT_MISSILE, 1 },
                   { WeaponVariant::LIGHT_MISSILE, 1 } }
    );

    variant = ShipVariant::IMPERIAL_CRUISER;
    shipvariant::  numberMadeMap.emplace( variant, 0 );
    shipvariant::        nameMap.emplace( variant, "Imperial Cruiser" );
    shipvariant::  pluralNameMap.emplace( variant, "Imperial Cruisers" );
    shipvariant:: descriptionMap.emplace( variant,
        "An Imperial cruiser." );
    shipvariant::        costMap.emplace( variant, 100000 );
    shipvariant::        sizeMap.emplace( variant, 4 );
    shipvariant::  hullPointsMap.emplace( variant, 30.0 );
    shipvariant:: armorPointsMap.emplace( variant, 30.0 );
    shipvariant::shieldPointsMap.emplace( variant, 25.0 );
    shipvariant::pointDefenseMap.emplace( variant, 0.5 );
    shipvariant::    mobilityMap.emplace( variant, 3 );
    shipvariant::     weaponsMap.emplace( variant,
        weaponvec{ { WeaponVariant::PULSE_LASER, 2 },
                   { WeaponVariant::PULSE_LASER, 2 },
                   { WeaponVariant::LIGHT_MISSILE, 1 },
                   { WeaponVariant::HEAVY_MISSILE, 1 } }
    );

    variant = ShipVariant::IMPERIAL_DREADNOUGHT;
    shipvariant::  numberMadeMap.emplace( variant, 0 );
    shipvariant::        nameMap.emplace( variant, "Imperial Dreadnought" );
    shipvariant::  pluralNameMap.emplace( variant, "Imperial Dreadnoughts" );
    shipvariant:: descriptionMap.emplace( variant,
        "An Imperial dreadnought." );
    shipvariant::        costMap.emplace( variant, 1000000 );
    shipvariant::        sizeMap.emplace( variant, 5 );
    shipvariant::  hullPointsMap.emplace( variant, 50.0 );
    shipvariant:: armorPointsMap.emplace( variant, 45.0 );
    shipvariant::shieldPointsMap.emplace( variant, 40.0 );
    shipvariant::pointDefenseMap.emplace( variant, 0.3 );
    shipvariant::    mobilityMap.emplace( variant, 2 );
    shipvariant::     weaponsMap.emplace( variant,
        weaponvec{ { WeaponVariant::RAILGUN, 3 },
                   { WeaponVariant::RAILGUN, 3 },
                   { WeaponVariant::RAILGUN, 3 },
                   { WeaponVariant::PARTICLE_BEAM, 1 } }
    );
}
