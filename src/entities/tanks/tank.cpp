#include "tank.h"

Tank::Tank(double x, double y, const TextureInfo& chassisTextureInfo, const TextureInfo& turretTextureInfo, const TextureInfo& shellTextureInfo)
    : m_chassis(std::make_unique<Chassis>(x, y, chassisTextureInfo)),
      m_turret(std::make_unique<Turret>(x, y, turretTextureInfo, shellTextureInfo))
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
    m_chassis->move(movement, deltaTime);
}

void Tank::rotateTank(TankMovements::Rotation rotation, double deltaTime) {
    m_chassis->rotate(rotation, deltaTime);
    m_turret->rotate(rotation, deltaTime, m_chassis->isMoving());
}

void Tank::rotateTurret(TankMovements::Rotation rotation, double deltaTime) {
    m_turret->rotate(rotation, deltaTime, false);
}

void Tank::fire() {
    m_turret->fire();
}