#ifndef CHASSIS_H
#define CHASSIS_H

#include "../tank_movements.h"
#include "../../base/dynamic_entity.h"
#include "../../../properties/tank_property.h"
#include <SDL.h>
#include <vector>

class Chassis : public DynamicEntity {
public:
    Chassis(const TankProperty& tankProperty, double x, double y, std::shared_ptr<TextureInfo> textureInfo);

    void move(TankMovements::Movement movement, double tileSpeedMultiplier);
    void rotate(TankMovements::Rotation rotation, double deltaTime, double rotationSpeed);

private:
    double m_speed;
    double m_rotationSpeed;
};

#endif // CHASSIS_H