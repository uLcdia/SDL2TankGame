#ifndef GAME_H
#define GAME_H

#include "../managers/resource_manager.h"
#include "../managers/entity_manager.h"
#include "../managers/input_manager.h"
#include "../managers/audio_manager.h"
#include "../managers/game_state_manager.h"
#include <SDL.h>
#include <memory>

// Game class: Manages the main game loop, SDL initialization, and game state
class Game {
public:
    Game(const char* title, int width, int height);
    ~Game();

    bool init();
    void run();

private:
    void handleEvents();
    void render();
    void cleanup();

    const char* m_title;
    int m_width, m_height;
    bool m_isRunning;

    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    InputManager m_inputManager;
    ResourceManager m_resourceManager;
    GameStateManager m_gameStateManager;
    std::unique_ptr<EntityManager> m_entityManager;
    std::unique_ptr<AudioManager> m_audioManager;
};

#endif // GAME_H