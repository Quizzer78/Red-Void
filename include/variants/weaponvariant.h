#include <map>
#include <string>

#include "Weapon.h"

#ifndef WEAPONVARIANT_H
#define WEAPONVARIANT_H

enum class WeaponVariant {
    MINI_LASER,
    AUTOCANNON,
    LIGHT_MISSILE,
    MAX_WEAPON_VARIANT,
};

namespace weaponvariant {
    Weapon createWeapon(WeaponVariant variant);
    void initializeMaps(); // all weapon parameters defined here

    extern std::map<WeaponVariant, std::string> nameMap;
    extern std::map<WeaponVariant, std::string> pluralNameMap;
    extern std::map<WeaponVariant, std::string> descriptionMap;
    extern std::map<WeaponVariant, double> accuracyMap;
    extern std::map<WeaponVariant, double> damageMap;
    extern std::map<WeaponVariant, bool> guidedMap;
    extern std::map<WeaponVariant, double> hullEffectivenessMap;
    extern std::map<WeaponVariant, double> armorEffectivenessMap;
    extern std::map<WeaponVariant, double> shieldEffectivenessMap;
};

#endif
