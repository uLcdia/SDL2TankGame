#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "entity_manager.h"
#include <SDL.h>

class InputManager {
public:
    void handleInput(EntityManager& entityManager);
    void handleEvent(SDL_Event& event, EntityManager& entityManager);

private:
    bool m_rKeyPressed = false;
};

#endif // INPUT_MANAGER_H