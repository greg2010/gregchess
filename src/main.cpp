#include "SDL.h"
#include "ui/Window.h"
#include "ui/Game.h"


int main(int argc, char *argv[]) {

    Window *window = new Window(1920, 1080);
    Game *game = new Game(window);
    // Game loop method of window must only be called once
    window->gameLoop();

    delete game;
    delete window;
}
