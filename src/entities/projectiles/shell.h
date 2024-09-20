#ifndef SHELL_H
#define SHELL_H

#include "../base/dynamic_entity.h"
#include <SDL.h>

class Shell : public DynamicEntity {
public:
    Shell(double x, double y, double angle, const TextureInfo& shellTextureInfo);
    
    void update(double deltaTime) override;
    void render(SDL_Renderer* renderer) const override;
    
    bool isActive() const { return m_active; }
    void setActive(bool active) { m_active = active; }

    double getAngle() const { return m_angle; }

    static Shell createShell(double x, double y, double angle, const TextureInfo& shellTextureInfo);

private:
    double m_angle;
    bool m_active;
    
    const TextureInfo* m_shellTextureInfo;
    
    static constexpr double SPEED = 300.0; // pixels per second
    static constexpr double SPAWN_DISTANCE = 65.0; // pixels from turret center to barrel tip
};

#endif // SHELL_H