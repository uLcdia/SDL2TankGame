#ifndef MAP_PARSER_H
#define MAP_PARSER_H

#include "tile_property.h"
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
#include <unordered_map>

class MapParser {
public:
    MapParser(const std::string& filename);
    bool parse();

    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
    int getTileSize() const { return m_tileSize; }
    std::pair<int, int> getPlayerTankPosition() const { return m_playerTankPosition; }
    const std::string& getBackgroundTexture() const { return m_backgroundTexture; }
    const std::unordered_map<char, TileProperty>& getTileProperties() const { return m_tileProperties; }
    const std::vector<std::string>& getMapLayout() const { return m_mapLayout; }

private:
    std::string m_filename;
    int m_width;
    int m_height;
    int m_tileSize;
    std::pair<int, int> m_playerTankPosition;
    std::string m_backgroundTexture;
    std::unordered_map<char, TileProperty> m_tileProperties;
    std::vector<std::string> m_mapLayout;

    void parseJson(const nlohmann::json& j);
};

#endif // MAP_PARSER_H