#ifndef CARTRIDGE_PROPERTY_H
#define CARTRIDGE_PROPERTY_H

#include <string>

struct CartridgeProperty {
    std::string name;
    std::string projectileType;
    double fireInterval;    
    double reloadInterval;
    int capacity;
};

#endif // CARTRIDGE_PROPERTY_H