#include "turret.h"
#include <cmath>
#include <algorithm>

Turret::Turret(double x, double y, const TextureInfo& turretTextureInfo, const TextureInfo& shellTextureInfo)
    : DynamicEntity(x, y, turretTextureInfo),
      m_angle(0.0),
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
    double turretPivotX = getX();
    double turretPivotY = getY();

    // Set the pivot point for turret rotation
    SDL_Point turretPivot = {m_turretTextureInfo->width / 2, static_cast<int>(m_turretTextureInfo->height * 0.65)};

    // Set up destination rectangle for the turret
    SDL_Rect turretRect = {
        static_cast<int>(turretPivotX - m_turretTextureInfo->width / 2),
        static_cast<int>(turretPivotY - m_turretTextureInfo->height * 0.65),
        m_turretTextureInfo->width,
        m_turretTextureInfo->height
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

    m_shells.emplace_back(Shell::createShell(getX(), getY(), m_angle, *m_shellTextureInfo));
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

SDL_Rect Turret::getRect() const {
    SDL_Rect rect = DynamicEntity::getRect();
    rect.x -= rect.w / 2;
    rect.y -= rect.h / 2;
    return rect;
}