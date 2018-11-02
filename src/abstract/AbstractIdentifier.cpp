#include <string>
#include <vector>

#include "AbstractIdentifier.h"
#include "random.h"

std::vector<std::string> AbstractIdentifier::pastIds_;

AbstractIdentifier::AbstractIdentifier() {
    this->generateID();
}

const std::string& AbstractIdentifier::getID() const {
    return id_;
}

void AbstractIdentifier::generateID() {
    std::uniform_int_distribution<int> distribution { 0, 9 };
    std::string id { "" };
    bool doLoop { true };
    while (doLoop) {
        id = "";
        doLoop = false;
        for (int i = 0; i < 10; ++i) {
            id += std::to_string(distribution(random::engine));
        }
        for (const std::string& past : pastIds_) {
            if (past == id) {
                doLoop = true;
            }
        }
    }
    pastIds_.push_back(id);
    id_ = id;
}
