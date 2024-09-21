#ifndef TILE_PROPERTY_H
#define TILE_PROPERTY_H

#include <string>

struct TileProperty {
    std::string name;
    std::string texture;
    bool isBrick = false;
    bool isVulnerable = false;
    int health = 1;
};

#endif // TILE_PROPERTY_H