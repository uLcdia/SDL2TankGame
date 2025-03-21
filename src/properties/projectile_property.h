#ifndef PROJECTILE_PROPERTY_H
#define PROJECTILE_PROPERTY_H

#include <string>

struct ProjectileProperty {
    std::string name;
    std::string texturePath;
    int speed;
    int damage;
    double scale;
    
    ProjectileProperty(const std::string& name, const std::string& texturePath, int speed, int damage, double scale)
        : name(name), texturePath(texturePath), speed(speed), damage(damage), scale(scale) {}
};

#endif // PROJECTILE_PROPERTY_H