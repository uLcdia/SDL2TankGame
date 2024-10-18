#include "tank.h"

Tank::Tank(const TankProperty& tankProperty, double x, double y, std::shared_ptr<TextureInfo> chassisTexture, std::shared_ptr<TextureInfo> turretTexture)
    : m_name(tankProperty.name),
      m_health(tankProperty.health),
      m_maxHealth(tankProperty.health),
      m_isMoving(false),
      m_chassis(std::make_unique<Chassis>(tankProperty, x, y, std::move(chassisTexture))),
      m_turret(std::make_unique<Turret>(tankProperty, x, y, std::move(turretTexture))),
      m_chassisRotationSpeed(tankProperty.chassis.rotationSpeed),
      m_turretRotationSpeed(tankProperty.turret.rotationSpeed)
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

void Tank::move(TankMovements::Movement movement, double tileSpeedMultiplier) {
    if (movement == TankMovements::Movement::NONE) {
        m_chassis->setVelocity(0, 0);
        m_isMoving = false;
    } else {
        m_chassis->move(movement, tileSpeedMultiplier);
        m_isMoving = true;
    }
}

void Tank::rotate(TankMovements::Rotation rotation, double tileSpeedMultiplier) {
    if (rotation == TankMovements::Rotation::NONE) {
        m_chassis->setRotationSpeed(0);
        m_turret->setRotationSpeed(0);
    } else {
        double rotationSpeed = m_isMoving ? m_chassisRotationSpeed * TankMovements::ROTATE_SPEED_MULTIPLIER * tileSpeedMultiplier 
                                          : m_chassisRotationSpeed * tileSpeedMultiplier;
        m_chassis->rotate(rotation, rotationSpeed);
        m_turret->rotate(rotation, rotationSpeed);
    }
}

void Tank::rotateTurret(TankMovements::Rotation rotation) {
    // Turrent rotation should be independent of chassis rotation
    m_turret->rotate(rotation, m_turretRotationSpeed);
}

void Tank::damage(double damage) {
    if (!isAlive()) {
        return;
    }
    m_health -= damage;
    if (m_health <= 0) {
        m_health = 0;
    }
}

void Tank::heal(double health) {
    if (!isAlive() || m_health == m_maxHealth) {
        return;
    }
    m_health += health;
    if (m_health > m_maxHealth) {
        m_health = m_maxHealth;
    }
}

bool Tank::collidesWith(const Entity& other) const {
    return m_chassis->collidesWith(other);
}

bool Tank::collidesWith(const DynamicEntity& other) const {
    return m_chassis->collidesWith(other);
}

bool Tank::collidesWith(const Tank& other) const {
    return m_chassis->collidesWith(*other.m_chassis);
}