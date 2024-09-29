#ifndef ENTITY_H
#define ENTITY_H

#include "../../utils/texture_info.h"
#include <SDL.h>
#include <memory>
#include <array>
#include <cmath>

/**
 * @class Entity
 * @brief Base class for all game entities.
 *
 * This class represents a basic entity in the game world, providing
 * common functionality such as position, dimensions, and rendering.
 */
class Entity {
public:
    Entity(double x, double y, std::shared_ptr<TextureInfo> textureInfo);
    virtual ~Entity() = default;

    virtual void render(SDL_Renderer* renderer) const;

    double getX() const { return m_x; }
    double getY() const { return m_y; }
    void setX(double x) { m_x = x; }
    void setY(double y) { m_y = y; }

    int getWidth() const { return m_textureInfo->width; }
    int getHeight() const { return m_textureInfo->height; }

    virtual SDL_Rect getRect() const;

    virtual std::array<SDL_Point, 4> getVertices() const;

    void renderEdges(SDL_Renderer* renderer) const;

protected:
    double m_x, m_y;
    std::shared_ptr<TextureInfo> m_textureInfo;
};

#endif // ENTITY_H