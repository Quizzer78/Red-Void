#include <map>
#include <stdexcept>
#include <string>

#include "weaponvariant.h"

std::map<WeaponVariant, std::string> weaponvariant::nameMap;
std::map<WeaponVariant, std::string> weaponvariant::pluralNameMap;
std::map<WeaponVariant, std::string> weaponvariant::descriptionMap;
std::map<WeaponVariant, double> weaponvariant::accuracyMap;
std::map<WeaponVariant, double> weaponvariant::damageMap;
std::map<WeaponVariant, bool> weaponvariant::guidedMap;
std::map<WeaponVariant, double> weaponvariant::hullEffectivenessMap;
std::map<WeaponVariant, double> weaponvariant::armorEffectivenessMap;
std::map<WeaponVariant, double> weaponvariant::shieldEffectivenessMap;

Weapon weaponvariant::createWeapon(WeaponVariant variant) {
    return
        {
        weaponvariant::nameMap.at(variant),
        weaponvariant::pluralNameMap.at(variant),
        weaponvariant::descriptionMap.at(variant),
        weaponvariant::accuracyMap.at(variant),
        weaponvariant::damageMap.at(variant),
        weaponvariant::guidedMap.at(variant),
        weaponvariant::hullEffectivenessMap.at(variant),
        weaponvariant::armorEffectivenessMap.at(variant),
        weaponvariant::shieldEffectivenessMap.at(variant)
        };
}

void weaponvariant::initializeMaps() {
    WeaponVariant variant { WeaponVariant::MAX_WEAPON_VARIANT };

    variant = WeaponVariant::MINI_LASER;
    weaponvariant::               nameMap.emplace( variant, "Mini Laser" );
    weaponvariant::         pluralNameMap.emplace( variant, "Mini Lasers" );
    weaponvariant::        descriptionMap.emplace( variant,
        "A mini laser." );
    weaponvariant::           accuracyMap.emplace( variant, 2.0 );
    weaponvariant::             damageMap.emplace( variant, 0.2 );
    weaponvariant::             guidedMap.emplace( variant, false );
    weaponvariant::  hullEffectivenessMap.emplace( variant, 1.0 );
    weaponvariant:: armorEffectivenessMap.emplace( variant, 1.0 );
    weaponvariant::shieldEffectivenessMap.emplace( variant, 1.0 );

    variant = WeaponVariant::AUTOCANNON;
    weaponvariant::               nameMap.emplace( variant, "Autocannon" );
    weaponvariant::         pluralNameMap.emplace( variant, "Autocannons" );
    weaponvariant::        descriptionMap.emplace( variant,
        "An autocannon." );
    weaponvariant::           accuracyMap.emplace( variant, 1.5 );
    weaponvariant::             damageMap.emplace( variant, 2.5 );
    weaponvariant::             guidedMap.emplace( variant, false );
    weaponvariant::  hullEffectivenessMap.emplace( variant, 1.0 );
    weaponvariant:: armorEffectivenessMap.emplace( variant, 0.5 );
    weaponvariant::shieldEffectivenessMap.emplace( variant, 1.1 );

    variant = WeaponVariant::LIGHT_MISSILE;
    weaponvariant::               nameMap.emplace( variant, "Light Missile" );
    weaponvariant::         pluralNameMap.emplace( variant, "Light Missiles" );
    weaponvariant::        descriptionMap.emplace( variant,
        "A light missile." );
    weaponvariant::           accuracyMap.emplace( variant, 5.0 );
    weaponvariant::             damageMap.emplace( variant, 5.0 );
    weaponvariant::             guidedMap.emplace( variant, true );
    weaponvariant::  hullEffectivenessMap.emplace( variant, 1.3 );
    weaponvariant:: armorEffectivenessMap.emplace( variant, 0.5 );
    weaponvariant::shieldEffectivenessMap.emplace( variant, 0.3 );
}
