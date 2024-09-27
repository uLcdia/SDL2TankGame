#ifndef DYNAMIC_ENTITY_H
#define DYNAMIC_ENTITY_H

#include "entity.h"

/**
 * @class DynamicEntity
 * @brief Represents an entity with dynamic properties such as velocity and rotation.
 *
 * This class extends the base Entity class to include functionality for moving and rotating entities.
 */
class DynamicEntity : public Entity {
public:
    DynamicEntity(double x, double y, double angle, std::shared_ptr<TextureInfo> textureInfo, double scale);
    virtual ~DynamicEntity() = default;

    virtual void update(double deltaTime) override;
    virtual void render(SDL_Renderer* renderer) const override;

    void setVelocity(double vx, double vy);
    double getVelocityX() const { return m_vx; }
    double getVelocityY() const { return m_vy; }
    void setRotationSpeed(double rotationSpeed) { m_rotationSpeed = rotationSpeed; }
    double getRotationSpeed() const { return m_rotationSpeed; }

    int getScaledWidth() const { return static_cast<int>(m_textureInfo->width * m_scale); }
    int getScaledHeight() const { return static_cast<int>(m_textureInfo->height * m_scale); }
    
    void setAngle(double angle) { m_angle = angle; }
    double getAngle() const { return m_angle; }

    virtual SDL_Rect getRect() const override;

    virtual std::array<SDL_Point, 4> getVertices() const override;

    bool collidesWith(const Entity& other) const;
    bool collidesWith(const DynamicEntity& other) const;

protected:
    double m_vx, m_vy;
    double m_rotationSpeed;
    double m_angle;
    double m_scale;

    bool checkSATCollision(const Entity& other) const;
};

#endif // DYNAMIC_ENTITY_H