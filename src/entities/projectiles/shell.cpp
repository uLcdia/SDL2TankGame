#include "shell.h"
#include <cmath>

Shell::Shell(double x, double y, double angle, const TextureInfo& shellTextureInfo)
    : DynamicEntity(x, y, shellTextureInfo), m_angle(angle), m_active(true)
{
    // Set initial velocity based on angle and speed
    double vx = std::sin(m_angle * M_PI / 180.0) * SPEED;
    double vy = -std::cos(m_angle * M_PI / 180.0) * SPEED;
    setVelocity(vx, vy);
}

void Shell::update(double deltaTime) {
    if (!m_active) return;

    DynamicEntity::update(deltaTime);

    // TODO: Use collision system to check if shell is out of screen bounds
    if (getX() < 0 || getX() > 1600 || getY() < 0 || getY() > 960) {
        m_active = false;
    }
}

void Shell::render(SDL_Renderer* renderer) const {
    if (!m_active) return;

    SDL_Rect shellRect = getRect();

    // Temporary fix to render the shell at the correct position
    shellRect.x = getX() - getWidth() / 2;
    shellRect.y = getY() - getHeight() / 2;

    SDL_RenderCopyEx(renderer, m_textureInfo->texture, nullptr, &shellRect, m_angle, nullptr, SDL_FLIP_NONE);
}

Shell Shell::createShell(double x, double y, double angle, const TextureInfo& shellTextureInfo) {
    double shellX = x + std::sin(angle * M_PI / 180.0) * SPAWN_DISTANCE;
    double shellY = y - std::cos(angle * M_PI / 180.0) * SPAWN_DISTANCE;
    return Shell(shellX, shellY, angle, shellTextureInfo);
}