#include "cartridge.h"

Cartridge::Cartridge(const CartridgeProperty& cartridgeProperty)
    : m_name(cartridgeProperty.name), m_projectileType(cartridgeProperty.projectileType), m_capacity(cartridgeProperty.capacity),
      m_fireInterval(cartridgeProperty.fireInterval), m_reloadInterval(cartridgeProperty.reloadInterval),
      m_remainingShots(cartridgeProperty.capacity), m_fireTimer(0), m_reloadTimer(0)
{}

void Cartridge::update(double deltaTime) {
    if (m_fireTimer > 0) {
        m_fireTimer -= deltaTime;
    }
    if (m_reloadTimer > 0) {
        m_reloadTimer -= deltaTime;
        if (m_reloadTimer <= 0) {
            m_remainingShots = std::min(m_remainingShots + 1, m_capacity);
            if (m_remainingShots < m_capacity) {
                m_reloadTimer = m_reloadInterval;
            }
        }
    }
}

bool Cartridge::fire(double x, double y, double angle, const FireCallback& fireCallback, std::string shooter) {
    if (m_remainingShots > 0 && m_fireTimer <= 0) {
        fireCallback(m_projectileType, x, y, angle, shooter);
        m_remainingShots--;
        m_fireTimer = m_fireInterval;
        if (m_remainingShots == 0) {
            m_reloadTimer = m_reloadInterval;
        }
        return true;
    }
    return false;
}