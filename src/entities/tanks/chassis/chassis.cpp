#include "chassis.h"
#include <cmath>
#include <algorithm>

Chassis::Chassis(const TankProperty& tankProperty, double x, double y, std::shared_ptr<TextureInfo> textureInfo)
    : DynamicEntity(x, y, tankProperty.angle, std::move(textureInfo), tankProperty.scale),
      m_speed(tankProperty.chassis.speed),
      m_rotationSpeed(tankProperty.chassis.rotationSpeed)
{}

void Chassis::move(TankMovements::Movement movement, double deltaTime) {
    switch (movement) {
        case TankMovements::Movement::FORWARD:
            setVelocity(std::sin(m_angle * M_PI / 180.0) * m_speed, -std::cos(m_angle * M_PI / 180.0) * m_speed);
            break;
        case TankMovements::Movement::BACKWARD:
            setVelocity(-std::sin(m_angle * M_PI / 180.0) * m_speed, std::cos(m_angle * M_PI / 180.0) * m_speed);
            break;
    }
}

void Chassis::rotate(TankMovements::Rotation rotation, double deltaTime, double rotationSpeed) {
    switch (rotation) {
        case TankMovements::Rotation::CLOCKWISE:
            m_angle += rotationSpeed * deltaTime;
            break;
        case TankMovements::Rotation::COUNTERCLOCKWISE:
            m_angle -= rotationSpeed * deltaTime;
            break;
    }

    m_angle = fmod(m_angle + 360.0, 360.0);
}