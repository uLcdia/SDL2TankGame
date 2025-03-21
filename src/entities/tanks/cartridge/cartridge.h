#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include "../../../properties/cartridge_property.h"
#include <string>
#include <functional>

class Cartridge {
public:
    using FireCallback = std::function<void(const std::string&, double, double, double, std::string)>;

    Cartridge(const CartridgeProperty& cartridgeProperty);

    void update(double deltaTime);

    bool fire(double x, double y, double angle, const FireCallback& fireCallback, std::string shooter);
    bool isReady() const { return m_remainingShots > 0 && m_fireTimer <= 0; }
    int getRemainingShots() const { return m_remainingShots; }
    const std::string& getName() const { return m_name; }

private:
    std::string m_name;
    std::string m_projectileType;
    int m_capacity;
    double m_fireInterval;
    double m_reloadInterval;
    int m_remainingShots;
    double m_fireTimer;
    double m_reloadTimer;
};

#endif // CARTRIDGE_H