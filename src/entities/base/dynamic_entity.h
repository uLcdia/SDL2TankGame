#ifndef DYNAMIC_ENTITY_H
#define DYNAMIC_ENTITY_H

#include "entity.h"

class DynamicEntity : public Entity {
public:
    DynamicEntity(double x, double y, const TextureInfo& textureInfo);
    virtual ~DynamicEntity() = default;

    virtual void update(double deltaTime) override;

    void setVelocity(double vx, double vy);
    double getVelocityX() const { return m_vx; }
    double getVelocityY() const { return m_vy; }

protected:
    double m_vx, m_vy;  // Velocity components
};

#endif // DYNAMIC_ENTITY_H