#include <stdexcept>
#include <string>

#include "weaponvariant.h"

Weapon weaponvariant::createWeapon(WeaponVariant variant) {
    switch(variant) {

    case WeaponVariant::TEST : return
        {
        "name",
        "names",
        "des",
        0.0, //accuracy
        0.0, //damage
        false, //guided
        0.0, //hullEffectiveness
        0.0,  //armorEffectiveness
        0.0  //shieldEffectiveness
        };
    default:
        throw std::invalid_argument("Weapon variant not found");
    }
}
