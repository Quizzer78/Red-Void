#include <iostream>
#include <string>

#include "shipvariant.h"

#ifndef INPUT_H
#define INPUT_H

namespace input {
    int intInput();
    ShipVariant shipVariantInput();
    std::string strInput();
};

#endif
