#include "tank.h"

Tank::Tank(double x, double y, double angle, const TextureInfo& chassisTextureInfo, const TextureInfo& turretTextureInfo, double scale)
    : m_chassis(std::make_unique<Chassis>(x, y, angle, chassisTextureInfo, scale)),
      m_turret(std::make_unique<Turret>(x, y, angle, turretTextureInfo, scale))
{}

void Tank::update(double deltaTime) {
    m_chassis->update(deltaTime);
    m_turret->update(deltaTime);
    // Update turret position to match chassis position
    m_turret->setX(m_chassis->getX());
    m_turret->setY(m_chassis->getY());
}

void Tank::render(SDL_Renderer* renderer) const {
    m_chassis->render(renderer);
    m_turret->render(renderer);
}

void Tank::move(TankMovements::Movement movement, double deltaTime) {
    if (movement == TankMovements::Movement::NONE) {
        m_chassis->setVelocity(0, 0);
        m_isMoving = false;
    } else {
        m_chassis->move(movement, deltaTime);
        m_isMoving = true;
    }
}

void Tank::rotate(TankMovements::Rotation rotation, double deltaTime) {
    m_chassis->rotate(rotation, deltaTime, m_isMoving);
    m_turret->rotate(rotation, deltaTime, m_isMoving);
}

void Tank::rotateTurret(TankMovements::Rotation rotation, double deltaTime) {
    // Turrent rotation should be independent of chassis rotation
    m_turret->rotate(rotation, deltaTime, false);
}

void Tank::fire(const Cartridge::FireCallback& fireCallback) {
    m_turret->fire(fireCallback);
}

void Tank::addCartridge(const std::string& name, const std::string& projectileType, int capacity, double fireInterval, double reloadInterval) {
    m_turret->addCartridge(name, projectileType, capacity, fireInterval, reloadInterval);
}