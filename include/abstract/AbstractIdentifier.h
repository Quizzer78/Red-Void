#include <string>

#ifndef ABSTRACTIDENTIFIER_H
#define ABSTRACTIDENTIFIER_H

class AbstractIdentifier {
    public:
        const std::string& getID() const;

    protected:
        std::string id_;

        AbstractIdentifier();

    private:
        void generateID();
};

#endif
