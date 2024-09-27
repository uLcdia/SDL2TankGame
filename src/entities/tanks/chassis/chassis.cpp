#include "chassis.h"
#include <cmath>
#include <algorithm>

Chassis::Chassis(const TankProperty& tankProperty, double x, double y, std::shared_ptr<TextureInfo> textureInfo)
    : DynamicEntity(x, y, tankProperty.angle, std::move(textureInfo), tankProperty.scale),
      m_speed(tankProperty.chassis.speed),
      m_rotationSpeed(tankProperty.chassis.rotationSpeed)
{}

void Chassis::move(TankMovements::Movement movement, double tileSpeedMultiplier) {
    double speed = m_speed * tileSpeedMultiplier;
    switch (movement) {
        case TankMovements::Movement::FORWARD:
            setVelocity(std::sin(m_angle * M_PI / 180.0) * speed, -std::cos(m_angle * M_PI / 180.0) * speed);
            break;
        case TankMovements::Movement::BACKWARD:
            setVelocity(-std::sin(m_angle * M_PI / 180.0) * speed, std::cos(m_angle * M_PI / 180.0) * speed);
            break;
        case TankMovements::Movement::NONE:
            setVelocity(0, 0);
            break;
    }
}

void Chassis::rotate(TankMovements::Rotation rotation, double rotationSpeed) {
    switch (rotation) {
        case TankMovements::Rotation::CLOCKWISE:
            setRotationSpeed(rotationSpeed);
            break;
        case TankMovements::Rotation::COUNTERCLOCKWISE:
            setRotationSpeed(-rotationSpeed);
            break;
        case TankMovements::Rotation::NONE:
            setRotationSpeed(0);
            break;
    }
}