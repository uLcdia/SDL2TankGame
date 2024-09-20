#ifndef DYNAMIC_ENTITY_H
#define DYNAMIC_ENTITY_H

#include "entity.h"

class DynamicEntity : public Entity {
public:
    DynamicEntity(double x, double y, double angle, const TextureInfo& textureInfo, double scale = 1.0);
    virtual ~DynamicEntity() = default;

    virtual void update(double deltaTime) override;
    virtual void render(SDL_Renderer* renderer) const override;

    void setVelocity(double vx, double vy);
    double getVelocityX() const { return m_vx; }
    double getVelocityY() const { return m_vy; }

    int getScaledWidth() const { return static_cast<int>(m_textureInfo->width * m_scale); }
    int getScaledHeight() const { return static_cast<int>(m_textureInfo->height * m_scale); }
    
    void setAngle(double angle) { m_angle = angle; }
    double getAngle() const { return m_angle; }

    virtual SDL_Rect getRect() const override;

protected:
    double m_vx, m_vy;
    double m_angle;
    double m_scale;
};

#endif // DYNAMIC_ENTITY_H