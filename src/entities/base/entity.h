#ifndef ENTITY_H
#define ENTITY_H

#include "../../utils/texture_info.h"
#include <SDL.h>

class Entity {
public:
    Entity(double x, double y, const TextureInfo& textureInfo);
    virtual ~Entity() = default;

    virtual void update(double deltaTime) = 0;
    virtual void render(SDL_Renderer* renderer) const;

    double getX() const { return m_x; }
    double getY() const { return m_y; }
    void setX(double x) { m_x = x; }
    void setY(double y) { m_y = y; }

    int getWidth() const { return m_textureInfo->width; }
    int getHeight() const { return m_textureInfo->height; }

    virtual bool collidesWith(const Entity& other) const;

    virtual SDL_Rect getRect() const;

protected:
    double m_x, m_y;
    const TextureInfo* m_textureInfo;
};

#endif // ENTITY_H