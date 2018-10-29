#include "Weapon.h"

#ifndef WEAPONVARIANT_H
#define WEAPONVARIANT_H

enum class WeaponVariant {
    TEST,
};

namespace weaponvariant {
    Weapon createWeapon(WeaponVariant variant);
};

#endif
