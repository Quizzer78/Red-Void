#include <string>

#ifndef ABSTRACTNAME_H
#define ABSTRACTNAME_H

class AbstractName {
    public:
        const std::string& getName()        const;
        const std::string& getPluralName()  const;
        const std::string& getDescription() const;

        void setName       (std::string name);
        void setPluralName (std::string pluralName);
        void setDescription(std::string description);

    protected:
        std::string name_;
        std::string pluralName_;
        std::string description_;

        AbstractName(std::string name, std::string pluralName,
                     std::string description);
};

#endif
