#ifndef CARTRIDGE_PROPERTY_H
#define CARTRIDGE_PROPERTY_H

#include <string>

struct CartridgeProperty {
    std::string name;
    std::string projectileType;
    double fireInterval;    
    double reloadInterval;
    int capacity;

    CartridgeProperty(const std::string& name, const std::string& projectileType, double fireInterval, double reloadInterval, int capacity)
        : name(name), projectileType(projectileType), fireInterval(fireInterval), reloadInterval(reloadInterval), capacity(capacity) {}
};

#endif // CARTRIDGE_PROPERTY_H