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
    weaponvariant::           accuracyMap.emplace( variant, 1.5 );
    weaponvariant::             damageMap.emplace( variant, 0.2 );
    weaponvariant::             guidedMap.emplace( variant, false );
    weaponvariant::  hullEffectivenessMap.emplace( variant, 1.0 );
    weaponvariant:: armorEffectivenessMap.emplace( variant, 1.0 );
    weaponvariant::shieldEffectivenessMap.emplace( variant, 1.0 );

    variant = WeaponVariant::PULSE_LASER;
    weaponvariant::               nameMap.emplace( variant, "Pulse Laser" );
    weaponvariant::         pluralNameMap.emplace( variant, "Pulse Lasers" );
    weaponvariant::        descriptionMap.emplace( variant,
        "A pulse laser." );
    weaponvariant::           accuracyMap.emplace( variant, 1.5 );
    weaponvariant::             damageMap.emplace( variant, 1.0 );
    weaponvariant::             guidedMap.emplace( variant, false );
    weaponvariant::  hullEffectivenessMap.emplace( variant, 1.0 );
    weaponvariant:: armorEffectivenessMap.emplace( variant, 1.2 );
    weaponvariant::shieldEffectivenessMap.emplace( variant, 0.8 );

    variant = WeaponVariant::PARTICLE_BEAM;
    weaponvariant::               nameMap.emplace( variant, "Particle Beam" );
    weaponvariant::         pluralNameMap.emplace( variant, "Particle Beams" );
    weaponvariant::        descriptionMap.emplace( variant,
        "A particle beam." );
    weaponvariant::           accuracyMap.emplace( variant, 1.2 );
    weaponvariant::             damageMap.emplace( variant, 5.0 );
    weaponvariant::             guidedMap.emplace( variant, false );
    weaponvariant::  hullEffectivenessMap.emplace( variant, 1.0 );
    weaponvariant:: armorEffectivenessMap.emplace( variant, 1.5 );
    weaponvariant::shieldEffectivenessMap.emplace( variant, 0.5 );

    variant = WeaponVariant::AUTOCANNON;
    weaponvariant::               nameMap.emplace( variant, "Autocannon" );
    weaponvariant::         pluralNameMap.emplace( variant, "Autocannons" );
    weaponvariant::        descriptionMap.emplace( variant,
        "An autocannon." );
    weaponvariant::           accuracyMap.emplace( variant, 1.0 );
    weaponvariant::             damageMap.emplace( variant, 2.5 );
    weaponvariant::             guidedMap.emplace( variant, false );
    weaponvariant::  hullEffectivenessMap.emplace( variant, 1.0 );
    weaponvariant:: armorEffectivenessMap.emplace( variant, 0.5 );
    weaponvariant::shieldEffectivenessMap.emplace( variant, 1.1 );

    variant = WeaponVariant::SMALL_RAILGUN;
    weaponvariant::               nameMap.emplace( variant, "Small Railgun" );
    weaponvariant::         pluralNameMap.emplace( variant, "Small Railguns" );
    weaponvariant::        descriptionMap.emplace( variant,
        "A small railgun." );
    weaponvariant::           accuracyMap.emplace( variant, 0.9 );
    weaponvariant::             damageMap.emplace( variant, 4.0 );
    weaponvariant::             guidedMap.emplace( variant, false );
    weaponvariant::  hullEffectivenessMap.emplace( variant, 1.0 );
    weaponvariant:: armorEffectivenessMap.emplace( variant, 0.7 );
    weaponvariant::shieldEffectivenessMap.emplace( variant, 1.2 );

    variant = WeaponVariant::RAILGUN;
    weaponvariant::               nameMap.emplace( variant, "Railgun" );
    weaponvariant::         pluralNameMap.emplace( variant, "Railguns" );
    weaponvariant::        descriptionMap.emplace( variant,
        "A railgun." );
    weaponvariant::           accuracyMap.emplace( variant, 0.8 );
    weaponvariant::             damageMap.emplace( variant, 8.0 );
    weaponvariant::             guidedMap.emplace( variant, false );
    weaponvariant::  hullEffectivenessMap.emplace( variant, 1.0 );
    weaponvariant:: armorEffectivenessMap.emplace( variant, 0.9 );
    weaponvariant::shieldEffectivenessMap.emplace( variant, 1.4 );

    variant = WeaponVariant::EVISCERATOR_FLAK;
    weaponvariant::               nameMap.emplace( variant, "Eviscerator Flak" );
    weaponvariant::         pluralNameMap.emplace( variant, "Eviscerator Flaks" );
    weaponvariant::        descriptionMap.emplace( variant,
        "An eviscerator flak." );
    weaponvariant::           accuracyMap.emplace( variant, 1.3 );
    weaponvariant::             damageMap.emplace( variant, 3.0 );
    weaponvariant::             guidedMap.emplace( variant, false );
    weaponvariant::  hullEffectivenessMap.emplace( variant, 2.0 );
    weaponvariant:: armorEffectivenessMap.emplace( variant, 0.2 );
    weaponvariant::shieldEffectivenessMap.emplace( variant, 0.3 );

    variant = WeaponVariant::INTERCEPTOR_MISSILE;
    weaponvariant::               nameMap.emplace( variant, "Interceptor Missile" );
    weaponvariant::         pluralNameMap.emplace( variant, "Interceptor Missiles" );
    weaponvariant::        descriptionMap.emplace( variant,
        "An interceptor missile." );
    weaponvariant::           accuracyMap.emplace( variant, 1.9 );
    weaponvariant::             damageMap.emplace( variant, 1.0 );
    weaponvariant::             guidedMap.emplace( variant, true );
    weaponvariant::  hullEffectivenessMap.emplace( variant, 1.5 );
    weaponvariant:: armorEffectivenessMap.emplace( variant, 0.5 );
    weaponvariant::shieldEffectivenessMap.emplace( variant, 0.3 );

    variant = WeaponVariant::LIGHT_MISSILE;
    weaponvariant::               nameMap.emplace( variant, "Light Missile" );
    weaponvariant::         pluralNameMap.emplace( variant, "Light Missiles" );
    weaponvariant::        descriptionMap.emplace( variant,
        "A light missile." );
    weaponvariant::           accuracyMap.emplace( variant, 1.7 );
    weaponvariant::             damageMap.emplace( variant, 5.0 );
    weaponvariant::             guidedMap.emplace( variant, true );
    weaponvariant::  hullEffectivenessMap.emplace( variant, 1.3 );
    weaponvariant:: armorEffectivenessMap.emplace( variant, 0.6 );
    weaponvariant::shieldEffectivenessMap.emplace( variant, 0.3 );

    variant = WeaponVariant::HEAVY_MISSILE;
    weaponvariant::               nameMap.emplace( variant, "Heavy Missile" );
    weaponvariant::         pluralNameMap.emplace( variant, "Heavy Missiles" );
    weaponvariant::        descriptionMap.emplace( variant,
        "A heavy missile." );
    weaponvariant::           accuracyMap.emplace( variant, 1.5 );
    weaponvariant::             damageMap.emplace( variant, 10.0 );
    weaponvariant::             guidedMap.emplace( variant, true );
    weaponvariant::  hullEffectivenessMap.emplace( variant, 1.5 );
    weaponvariant:: armorEffectivenessMap.emplace( variant, 0.7 );
    weaponvariant::shieldEffectivenessMap.emplace( variant, 0.4 );

    variant = WeaponVariant::TORPEDO;
    weaponvariant::               nameMap.emplace( variant, "Torpedo" );
    weaponvariant::         pluralNameMap.emplace( variant, "Torpedoes" );
    weaponvariant::        descriptionMap.emplace( variant,
        "A torpedo." );
    weaponvariant::           accuracyMap.emplace( variant, 0.7 );
    weaponvariant::             damageMap.emplace( variant, 30.0 );
    weaponvariant::             guidedMap.emplace( variant, true );
    weaponvariant::  hullEffectivenessMap.emplace( variant, 2.0 );
    weaponvariant:: armorEffectivenessMap.emplace( variant, 1.0 );
    weaponvariant::shieldEffectivenessMap.emplace( variant, 0.5 );
}
