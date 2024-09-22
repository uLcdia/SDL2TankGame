#include "tank_parser.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

TankParser::TankParser(const std::string& filename)
    : m_filename(filename) {}

bool TankParser::parse() {
    std::ifstream file(m_filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open tank config file: " << m_filename << std::endl;
        return false;
    }

    try {
        json j;
        file >> j;
        parseJson(j);
        return true;
    } catch (json::parse_error& e) {
        std::cerr << "JSON parse error: " << e.what() << std::endl;
        return false;
    }
}

void TankParser::parseJson(const json& j) {
    m_playerTank = parseTank(j["player"]);
    for (const auto& enemy : j["enemies"]) {
        m_enemyTanks.emplace_back(parseTank(enemy));
    }
    std::cout << "Player tank: " << m_playerTank.name << std::endl;
    for (const auto& enemy : m_enemyTanks) {
        std::cout << "Enemy tank: " << enemy.name << std::endl;
    }
}

TankProperty TankParser::parseTank(const json& j) {
    TankProperty tank; 
    tank.name = j["name"];
    tank.health = j["health"];
    tank.position.first = j["position"]["x"];
    tank.position.second = j["position"]["y"];
    tank.angle = j["angle"];
    tank.scale = j["scale"];
    tank.chassis.name = j["chassis"]["name"];
    tank.chassis.texturePath = j["chassis"]["texturePath"];
    tank.chassis.speed = j["chassis"]["speed"];
    tank.chassis.rotationSpeed = j["chassis"]["rotationSpeed"];
    tank.turret.name = j["turret"]["name"];
    tank.turret.texturePath = j["turret"]["texturePath"];
    tank.turret.rotationSpeed = j["turret"]["rotationSpeed"];
    for (const auto& cartridge : j["cartridges"]) {
        tank.cartridges.emplace_back(
            cartridge["name"],
            cartridge["projectileType"],
            cartridge["fireInterval"],
            cartridge["reloadInterval"],
            cartridge["capacity"]
        );
    }
    return tank;
}