#ifndef PLAYER_PARSER_H
#define PLAYER_PARSER_H

#include "projectile_property.h"
#include "cartridge_property.h"
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
#include <unordered_map>

class PlayerParser {
public:
    PlayerParser(const std::string& filename);
    bool parse();

    int getHealth() const { return m_health; }
    int getSpeed() const { return m_speed; }
    int getRotationSpeed() const { return m_rotationSpeed; }
    const std::pair<int, int>& getPosition() const { return m_position; }
    double getAngle() const { return m_angle; }
    double getScale() const { return m_scale; }
    const std::vector<ProjectileProperty>& getProjectileTypes() const { return m_projectileTypes; }
    const std::vector<CartridgeProperty>& getCartridges() const { return m_cartridges; }

private:
    std::string m_filename;
    int m_health;
    int m_speed;
    int m_rotationSpeed;
    std::pair<int, int> m_position;
    double m_angle;
    double m_scale;
    std::vector<ProjectileProperty> m_projectileTypes;
    std::vector<CartridgeProperty> m_cartridges;

    void parseJson(const nlohmann::json& j);
};

#endif // PLAYER_PARSER_H