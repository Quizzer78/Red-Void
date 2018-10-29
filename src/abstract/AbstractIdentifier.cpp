#include <string>

#include "AbstractIdentifier.h"
#include "random.h"

AbstractIdentifier::AbstractIdentifier() {
    this->generateID();
}

const std::string& AbstractIdentifier::getID() const {
    return id_;
}

void AbstractIdentifier::generateID() {
    std::uniform_int_distribution<int> distribution { 0, 9 };
    std::string id { "" };
    for (int i = 0; i < 10; ++i) {
        id += std::to_string(distribution(random::engine));
    }
    id_ = id;
}
