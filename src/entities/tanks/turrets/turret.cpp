#include "turret.h"
#include <cmath>
#include <algorithm>

Turret::Turret(double x, double y, double angle, const TextureInfo& turretTextureInfo, double scale)
    : DynamicEntity(x, y, angle, turretTextureInfo, scale),
      m_currentCartridgeIndex(0)
{}

void Turret::update(double deltaTime) {
    DynamicEntity::update(deltaTime);
    for (auto& cartridge : m_cartridges) {
        cartridge.update(deltaTime);
    }
}

void Turret::addCartridge(const std::string& name, const std::string& projectileType, int capacity, double fireInterval, double reloadInterval) {
    m_cartridges.emplace_back(name, projectileType, m_scale, capacity, fireInterval, reloadInterval);
}

void Turret::cycleCartridge() {
    if (!m_cartridges.empty()) {
        m_currentCartridgeIndex = (m_currentCartridgeIndex + 1) % m_cartridges.size();
    }
}

void Turret::fire(const Cartridge::FireCallback& fireCallback) {
    if (!m_cartridges.empty()) {
        double spawnDistance = PROJECTILE_SPAWN_DISTANCE * m_scale;
        double shellX = getX() + std::sin(m_angle * M_PI / 180.0) * spawnDistance;
        double shellY = getY() - std::cos(m_angle * M_PI / 180.0) * spawnDistance;
        m_cartridges[m_currentCartridgeIndex].fire(shellX, shellY, m_angle, fireCallback);
    }
}

const Cartridge* Turret::getCurrentCartridge() const {
    return m_cartridges.empty() ? nullptr : &m_cartridges[m_currentCartridgeIndex];
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
    SDL_RenderCopyEx(renderer, m_textureInfo->texture, nullptr, &turretRect, m_angle, &turretPivot, SDL_FLIP_NONE);
}