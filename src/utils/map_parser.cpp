#include "map_parser.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

MapParser::MapParser(const std::string& filename)
    : m_filename(filename), m_width(0), m_height(0), m_tileSize(0), m_playerTankPosition(-1, -1) {}

bool MapParser::parse() {
    std::ifstream file(m_filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open map file: " << m_filename << std::endl;
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

void MapParser::parseJson(const json& j) {
    m_width = j["width"];
    m_height = j["height"];
    m_tileSize = j["tileSize"];
    m_playerTankPosition = {j["playerTank"]["x"], j["playerTank"]["y"]};

    m_backgroundTexture = j["background"];

    for (const auto& [key, value] : j["tiles"].items()) {
        TileProperty tileProperty;
        tileProperty.name = value["name"];
        tileProperty.texture = value["texture"];

        if (value.contains("isBrick")) {
            tileProperty.isBrick = value["isBrick"];
        }
        if (value.contains("isVulnerable")) {
            tileProperty.isVulnerable = value["isVulnerable"];
        }
        if (value.contains("health")) {
            tileProperty.health = value["health"];
        }

        m_tileProperties[key[0]] = tileProperty;
    }

    m_mapLayout = j["layout"].get<std::vector<std::string>>();

    if (m_mapLayout.size() != m_height || m_mapLayout[0].size() != m_width) {
        throw std::runtime_error("Map dimensions do not match the layout");
    }

    std::cout << "Parsed map dimensions: " << m_width << "x" << m_height << std::endl;
    std::cout << "Tile size: " << m_tileSize << std::endl;
    std::cout << "Parsed tile properties: " << m_tileProperties.size() << std::endl;
    std::cout << "Parsed map layout lines: " << m_mapLayout.size() << std::endl;
    std::cout << "Player tank position: (" << m_playerTankPosition.first << ", " << m_playerTankPosition.second << ")" << std::endl;
}