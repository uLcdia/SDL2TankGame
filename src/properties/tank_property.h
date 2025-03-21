#ifndef TANK_PROPERTY_H
#define TANK_PROPERTY_H

#include "chassis_property.h"
#include "turret_property.h"
#include "cartridge_property.h"
#include <string>
#include <vector>

struct TankProperty {
    std::string name;
    double health;
    std::pair<int, int> position;
    double angle;
    double scale;
    ChassisProperty chassis;
    TurretProperty turret;
    std::vector<CartridgeProperty> cartridges;
};

#endif // TANK_PROPERTY_H