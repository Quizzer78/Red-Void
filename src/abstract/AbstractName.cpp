#include <string>

#include "AbstractName.h"

const std::string& AbstractName::getName()        const {
    return name_;
}
const std::string& AbstractName::getPluralName()  const {
    return pluralName_;
}
const std::string& AbstractName::getDescription() const {
    return description_;
}

void AbstractName::setName       (std::string name) {
    name_ = name;
}
void AbstractName::setPluralName (std::string pluralName) {
    pluralName_ = pluralName;
}
void AbstractName::setDescription(std::string description) {
    description_ = description;
}

AbstractName::AbstractName(std::string name, std::string pluralName,
                           std::string description)
    : name_ { name }, pluralName_ { pluralName }, description_ { description }
    {
    }
