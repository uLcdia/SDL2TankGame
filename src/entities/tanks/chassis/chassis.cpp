#include "chassis.h"
#include <cmath>
#include <algorithm>

Chassis::Chassis(double x, double y, double angle, const TextureInfo& chassisTextureInfo, double scale)
    : DynamicEntity(x, y, angle, chassisTextureInfo, scale)
{}

void Chassis::move(TankMovements::Movement movement, double deltaTime) {
    switch (movement) {
        case TankMovements::Movement::FORWARD:
            setVelocity(std::sin(m_angle * M_PI / 180.0) * MOVE_SPEED, -std::cos(m_angle * M_PI / 180.0) * MOVE_SPEED);
            break;
        case TankMovements::Movement::BACKWARD:
            setVelocity(-std::sin(m_angle * M_PI / 180.0) * MOVE_SPEED, std::cos(m_angle * M_PI / 180.0) * MOVE_SPEED);
            break;
    }
}

void Chassis::rotate(TankMovements::Rotation rotation, double deltaTime, bool isMoving) {
    double rotationSpeed = isMoving ? ROTATE_SPEED * TankMovements::ROTATE_SPEED_MULTIPLIER : ROTATE_SPEED;

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