#define SDL_MAIN_HANDLED
#include "core/game.h"

int main() {
    // Define game window resolution and title
    const int WIDTH = 1600;
    const int HEIGHT = 960;
    const char* WINDOW_TITLE = "SDL2 Tank Game";

    // Create a Game instance
    Game game(WINDOW_TITLE, WIDTH, HEIGHT);
    
    // Initialize SDL and game resources
    if (!game.init()) {
        // Exit if initialization fails
        return -1;
    }

    // Start the game loop
    game.run();

    return 0;
}