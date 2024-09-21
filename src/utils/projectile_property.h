#ifndef PROJECTILE_PROPERTY_H
#define PROJECTILE_PROPERTY_H

#include <string>

struct ProjectileProperty {
    std::string name;
    std::string texturePath;
    int speed;
    int damage;
};

#endif // PROJECTILE_PROPERTY_H