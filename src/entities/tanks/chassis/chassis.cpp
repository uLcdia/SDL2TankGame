#include "chassis.h"
#include <cmath>
#include <algorithm>

Chassis::Chassis(double x, double y, const TextureInfo& chassisTextureInfo)
    : DynamicEntity(x, y, chassisTextureInfo),
      m_angle(0.0)
{}

void Chassis::update(double deltaTime) {
    DynamicEntity::update(deltaTime);
}

void Chassis::move(TankMovements::Movement movement, double deltaTime) {
    switch (movement) {
        case TankMovements::Movement::FORWARD:
            setVelocity(std::sin(m_angle * M_PI / 180.0) * MOVE_SPEED, -std::cos(m_angle * M_PI / 180.0) * MOVE_SPEED);
            m_isMoving = true;
            break;
        case TankMovements::Movement::BACKWARD:
            setVelocity(-std::sin(m_angle * M_PI / 180.0) * MOVE_SPEED, std::cos(m_angle * M_PI / 180.0) * MOVE_SPEED);
            m_isMoving = true;
            break;
        case TankMovements::Movement::NONE:
            setVelocity(0, 0);
            m_isMoving = false;
            break;
    }
}

void Chassis::rotate(TankMovements::Rotation rotation, double deltaTime) {
    double rotationSpeed = m_isMoving ? ROTATE_SPEED * TankMovements::ROTATE_SPEED_MULTIPLIER : ROTATE_SPEED;

    switch (rotation) {
        case TankMovements::Rotation::CLOCKWISE:
            m_angle += rotationSpeed * deltaTime;
            break;
        case TankMovements::Rotation::COUNTERCLOCKWISE:
            m_angle -= rotationSpeed * deltaTime;
            break;
        case TankMovements::Rotation::NONE:
            break;
    }

    m_angle = fmod(m_angle + 360.0, 360.0);
}

void Chassis::render(SDL_Renderer* renderer) const {
    // Render the chassis
    SDL_Rect chassisRect = getRect();
    SDL_RenderCopyEx(renderer, m_textureInfo->texture, nullptr, &chassisRect, m_angle, nullptr, SDL_FLIP_NONE);
}

SDL_Rect Chassis::getRect() const {
    SDL_Rect rect = DynamicEntity::getRect();
    rect.x -= rect.w / 2;
    rect.y -= rect.h / 2;
    return rect;
}