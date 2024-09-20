#include "turret.h"
#include <cmath>
#include <algorithm>

Turret::Turret(double x, double y, double angle, const TextureInfo& turretTextureInfo, const TextureInfo& shellTextureInfo, double scale)
    : DynamicEntity(x, y, angle, turretTextureInfo, scale),
      m_turretTextureInfo(&turretTextureInfo),
      m_shellTextureInfo(&shellTextureInfo),
      m_fireTimer(0.0)
{}

void Turret::update(double deltaTime) {
    DynamicEntity::update(deltaTime);
    updateShells(deltaTime);
}

void Turret::rotate(TankMovements::Rotation rotation, double deltaTime, bool isMoving) {
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

void Turret::render(SDL_Renderer* renderer) const {
    // Calculate the position of the turret's pivot point
    double turretPivotX = getScaledWidth() * 0.5;
    double turretPivotY = getScaledHeight() * 0.65;

    // Set the pivot point for turret rotation
    SDL_Point turretPivot = {static_cast<int>(turretPivotX), static_cast<int>(turretPivotY)};

    // Set up destination rectangle for the turret
    SDL_Rect turretRect = {
        static_cast<int>(getX() - turretPivotX),
        static_cast<int>(getY() - turretPivotY),
        getScaledWidth(),
        getScaledHeight()
    };

    // Render the turret
    SDL_RenderCopyEx(renderer, m_turretTextureInfo->texture, nullptr, &turretRect, m_angle, &turretPivot, SDL_FLIP_NONE);

    // Render shells
    renderShells(renderer);
}

void Turret::fire() {
    double currentTime = SDL_GetTicks() / 1000.0;
    if (currentTime - m_fireTimer < FIRE_COOLDOWN) return;

    m_fireTimer = currentTime;

    m_shells.emplace_back(Shell::createShell(getX(), getY(), m_angle, *m_shellTextureInfo, m_scale));
}

void Turret::updateShells(double deltaTime) {
    for (auto& shell : m_shells) {
        shell.update(deltaTime);
    }

    // Remove inactive shells
    m_shells.erase(std::remove_if(m_shells.begin(), m_shells.end(),
        [](const Shell& shell) { return !shell.isActive(); }),
        m_shells.end());
}

void Turret::renderShells(SDL_Renderer* renderer) const {
    for (const auto& shell : m_shells) {
        shell.render(renderer);
    }
}