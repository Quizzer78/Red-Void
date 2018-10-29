#include <string>
#include <unordered_map>
#include <utility>

#include "AbstractIdentifier.h"
#include "AbstractName.h"
#include "Fleet.h"
#include "Ship.h"
#include "shipvariant.h"

Fleet::Fleet(std::string name, std::string pluralName, std::string description)
    : AbstractIdentifier(), AbstractName(name, pluralName, description),
      ships_ { {} }, totalCost_ { 0 }
    {
    }

void Fleet::addShip(ShipVariant variant, int number) {
    for (int i = 0; i < number; ++i) {
        Ship ship = shipvariant::createShip(variant);
        ships_.insert({ ship.getID(), std::move(ship) });
    }
    return;
}
bool Fleet::removeShip(const std::string& id, int number) {
    return false; //TODO
}
