#ifndef GAME_STATE_MANAGER_H
#define GAME_STATE_MANAGER_H

#include <SDL.h>
#include "entity_manager.h"
#include "audio_manager.h"

class GameStateManager {
public:
    void update(EntityManager& entityManager, AudioManager& audioManager);

private:
    bool isPlayerLowHealth(const EntityManager& entityManager);
    bool isEnemyLowHealth(const EntityManager& entityManager);
    bool isEnemyEliminated(const EntityManager& entityManager);

    static constexpr double LOW_HEALTH_THRESHOLD = 30.0;
};

#endif // GAME_STATE_MANAGER_H