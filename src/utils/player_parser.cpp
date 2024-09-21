#include "player_parser.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

PlayerParser::PlayerParser(const std::string& filename)
    : m_filename(filename), m_health(0), m_speed(0), m_rotationSpeed(0), m_position({0, 0}), m_projectileTypes({}) {}

bool PlayerParser::parse() {
    std::ifstream file(m_filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open player config file: " << m_filename << std::endl;
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

void PlayerParser::parseJson(const json& j) {
    m_health = j["health"];
    m_speed = j["speed"];
    m_rotationSpeed = j["rotationSpeed"];
    m_position = {j["position"]["x"], j["position"]["y"]};
    m_angle = j["angle"];
    m_scale = j["scale"];

    for (const auto& projectileType : j["projectileTypes"]) {
        m_projectileTypes.push_back({
            projectileType["name"],
            projectileType["texturePath"],
            projectileType["speed"],
            projectileType["damage"]
        });
    }

    for (const auto& cartridge : j["cartridges"]) {
        m_cartridges.push_back({
            cartridge["name"],
            cartridge["projectileType"],
            cartridge["fireInterval"],
            cartridge["reloadInterval"],
            cartridge["capacity"]
        });
    }

    std::cout << "Player health: " << m_health << std::endl;
    std::cout << "Player speed: " << m_speed << std::endl;
    std::cout << "Player rotation speed: " << m_rotationSpeed << std::endl;
    std::cout << "Player position: (" << m_position.first << ", " << m_position.second << ")" << std::endl;
    std::cout << "Player angle: " << m_angle << std::endl;
    std::cout << "Player scale: " << m_scale << std::endl;
    std::cout << "Player projectile types: ";
    for (const auto& projectileType : m_projectileTypes) {
        std::cout << projectileType.name << " ";
    }
    std::cout << std::endl;
    std::cout << "Player cartridges: ";
    for (const auto& cartridge : m_cartridges) {
        std::cout << cartridge.name << " ";
    }
    std::cout << std::endl;
}