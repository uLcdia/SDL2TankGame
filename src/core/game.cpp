#include "game.h"
#include "../utils/sdl_utils.h"
#include <SDL_image.h>
#include <iostream>

// Constructor: Initializes game properties and creates the tank
Game::Game(const char* title, int width, int height)
    : m_title(title), m_width(width), m_height(height), m_isRunning(false),
      m_window(nullptr), m_renderer(nullptr), m_entityManager(nullptr)
{}

// Destructor: Cleans up SDL resources
Game::~Game() {
    cleanup();
}

// Initialize SDL, create window and renderer, and load resources
bool Game::init() {
    if (!initSDL(m_window, m_renderer, m_title, m_width, m_height)) {
        return false;
    }

    // Initialize SDL_image, better but optional
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }

    // Initialize ResourceManager
    m_resourceManager.init(m_renderer);

    // Initialize EntityManager
    m_entityManager = std::make_unique<EntityManager>(m_resourceManager);

    if (!m_entityManager->loadLevel("level1")) {
        std::cerr << "Failed to load level!" << std::endl;
        return false;
    }

    m_isRunning = true;
    return true;
}

// Main game loop
void Game::run() {
    Uint32 lastTime = SDL_GetTicks();

    while (m_isRunning) {
        // Calculate delta time for frame-rate independent movement
        Uint32 currentTime = SDL_GetTicks();
        double deltaTime = (currentTime - lastTime) / 1000.0;
        lastTime = currentTime;

        handleEvents();
        update(deltaTime);
        render();
    }
}

// Process SDL events
void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                m_isRunning = false;
                break;
            default:
                m_inputManager.handleEvent(event, *m_entityManager);
                break;
        }
    }
}

// Update game state
void Game::update(double deltaTime) {
    m_entityManager->update(deltaTime);
    m_inputManager.handleInput(*m_entityManager, deltaTime);
}

// Render game objects
void Game::render() {
    // Clear screen
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    SDL_RenderClear(m_renderer);
    
    // Render background
    const auto& backgroundInfo = m_resourceManager.getTextureInfo("background");
    SDL_RenderCopy(m_renderer, backgroundInfo->texture, nullptr, nullptr);
    
    // Render entities
    m_entityManager->render(m_renderer);
    
    SDL_RenderPresent(m_renderer);
}

// Cleanup SDL resources
void Game::cleanup() {
    m_entityManager.reset();
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    IMG_Quit();
    SDL_Quit();
}