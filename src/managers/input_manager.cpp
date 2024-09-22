#include "input_manager.h"

void InputManager::handleInput(EntityManager& entityManager, double deltaTime) {
    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    Tank* playerTank = entityManager.getPlayerTank();
    
    if (!playerTank) return;

    if (keystate[SDL_SCANCODE_W]) {
        playerTank->move(TankMovements::Movement::FORWARD);
    } else if (keystate[SDL_SCANCODE_S]) {
        playerTank->move(TankMovements::Movement::BACKWARD);
    } else {
        playerTank->move(TankMovements::Movement::NONE);
    }

    if (keystate[SDL_SCANCODE_A]) {
        playerTank->rotate(TankMovements::Rotation::COUNTERCLOCKWISE, deltaTime);
    } else if (keystate[SDL_SCANCODE_D]) {
        playerTank->rotate(TankMovements::Rotation::CLOCKWISE, deltaTime);
    }

    if (keystate[SDL_SCANCODE_Q]) {
        playerTank->rotateTurret(TankMovements::Rotation::COUNTERCLOCKWISE, deltaTime);
    } else if (keystate[SDL_SCANCODE_E]) {
        playerTank->rotateTurret(TankMovements::Rotation::CLOCKWISE, deltaTime);
    }

    if (keystate[SDL_SCANCODE_SPACE]) {
        entityManager.handlePlayerFire();
    }
}

void InputManager::handleEvent(SDL_Event& event, EntityManager& entityManager) {
    Tank* playerTank = entityManager.getPlayerTank();
    if (!playerTank) return;

    switch (event.type) {
        case SDL_KEYDOWN:
            if (event.key.keysym.scancode == SDL_SCANCODE_R && !m_rKeyPressed) {
                m_rKeyPressed = true;
                playerTank->cycleCartridge();
            }
            break;
        case SDL_KEYUP:
            if (event.key.keysym.scancode == SDL_SCANCODE_R) {
                m_rKeyPressed = false;
            }
            break;
    }
}