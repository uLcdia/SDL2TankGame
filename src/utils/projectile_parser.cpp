#include "projectile_parser.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

ProjectileParser::ProjectileParser(const std::string& filename)
    : m_filename(filename) {}

bool ProjectileParser::parse() {
    std::ifstream file(m_filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open projectile config file: " << m_filename << std::endl;
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

void ProjectileParser::parseJson(const json& j) {
    for (const auto& projectile : j["projectiles"]) {
        m_projectiles.emplace_back(parseProjectile(projectile));
    }
    for (const auto& projectile : m_projectiles) {
        std::cout << "Projectile: " << projectile.name << std::endl;
    }
}

ProjectileProperty ProjectileParser::parseProjectile(const json& j) {
    ProjectileProperty projectile(j["name"], 
                                  j["texturePath"], 
                                  j["speed"], 
                                  j["damage"], 
                                  j["scale"]); 
    return projectile;
}