#ifndef CHASSIS_PROPERTY_H
#define CHASSIS_PROPERTY_H

#include <string>

struct ChassisProperty {
    std::string name;
    std::string texturePath;
    double speed;
    double rotationSpeed;
};

#endif // CHASSIS_PROPERTY_H