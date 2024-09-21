#include "cartridge.h"

Cartridge::Cartridge(const std::string& name, const std::string& projectileType, double scale, int capacity, double fireInterval, double reloadInterval)
    : m_name(name), m_projectileType(projectileType), m_scale(scale), m_capacity(capacity), m_remainingShots(capacity),
      m_fireInterval(fireInterval), m_reloadInterval(reloadInterval),
      m_fireTimer(0), m_reloadTimer(0)
{}

bool Cartridge::fire(double x, double y, double angle, const FireCallback& fireCallback) {
    if (m_remainingShots > 0 && m_fireTimer <= 0) {
        fireCallback(m_projectileType, x, y, angle, m_scale);
        m_remainingShots--;
        m_fireTimer = m_fireInterval;
        if (m_remainingShots == 0) {
            m_reloadTimer = m_reloadInterval;
        }
        return true;
    }
    return false;
}

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
