#ifndef TILE_PROPERTY_H
#define TILE_PROPERTY_H

#include <string>

struct TileProperty {
    std::string name;
    std::string texturePath;
    bool isBrick = false;
    bool isVulnerable = false;
    int health = 1;
    double tileSpeedMultiplier = 1.0;
};

#endif // TILE_PROPERTY_H