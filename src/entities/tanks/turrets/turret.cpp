#include "turret.h"
#include <cmath>
#include <algorithm>

Turret::Turret(const TankProperty& tankProperty, double x, double y, std::shared_ptr<TextureInfo> textureInfo)
    : DynamicEntity(x, y, tankProperty.angle, std::move(textureInfo), tankProperty.scale),
      m_currentCartridgeIndex(0)
{}

void Turret::update(double deltaTime) {
    DynamicEntity::update(deltaTime);
    for (auto& cartridge : m_cartridges) {
        cartridge.update(deltaTime);
    }
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

void Turret::rotate(TankMovements::Rotation rotation, double rotationSpeed) {
    switch (rotation) {
        case TankMovements::Rotation::CLOCKWISE:
            setRotationSpeed(rotationSpeed);
            break;
        case TankMovements::Rotation::COUNTERCLOCKWISE:
            setRotationSpeed(-rotationSpeed);
            break;
        case TankMovements::Rotation::NONE:
            break;
    }

    m_angle = fmod(m_angle + 360.0, 360.0);
}

void Turret::fire(const Cartridge::FireCallback& fireCallback, std::string shooter) {
    if (!m_cartridges.empty()) {
        double spawnDistance = PROJECTILE_SPAWN_DISTANCE * m_scale;
        double shellX = getX() + std::sin(m_angle * M_PI / 180.0) * spawnDistance;
        double shellY = getY() - std::cos(m_angle * M_PI / 180.0) * spawnDistance;
        m_cartridges[m_currentCartridgeIndex].fire(shellX, shellY, m_angle, fireCallback, shooter);
    }
}

void Turret::addCartridge(const Cartridge& cartridge) {
    m_cartridges.emplace_back(cartridge);
}

void Turret::cycleCartridge() {
    if (!m_cartridges.empty()) {
        m_currentCartridgeIndex = (m_currentCartridgeIndex + 1) % m_cartridges.size();
    }
}

const Cartridge* Turret::getCurrentCartridge() const {
    return m_cartridges.empty() ? nullptr : &m_cartridges[m_currentCartridgeIndex];
}