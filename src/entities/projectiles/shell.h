#ifndef SHELL_H
#define SHELL_H

#include "../base/dynamic_entity.h"
#include <SDL.h>

class Shell : public DynamicEntity {
public:
    Shell(double x, double y, double angle, const TextureInfo& shellTextureInfo, double scale = 1.0);
    
    void update(double deltaTime) override;
    void render(SDL_Renderer* renderer) const override;
    
    bool isActive() const { return m_active; }
    void setActive(bool active) { m_active = active; }

    static Shell createShell(double x, double y, double angle, const TextureInfo& shellTextureInfo, double scale = 1.0);

private:
    bool m_active;
    
    const TextureInfo* m_shellTextureInfo;
    
    static constexpr double SPEED = 300.0; // pixels per second
    static constexpr double SPAWN_DISTANCE = 65.0; // pixels from turret center to barrel tip
};

#endif // SHELL_H