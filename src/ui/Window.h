#ifndef GREGCHESS_WINDOW_H
#define GREGCHESS_WINDOW_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "spdlog/spdlog.h"
#include "Renderable.h"

#define MIN_WINDOW_WIDTH 400
#define MIN_WINDOW_HEIGHT 400

#define BACKGROUND_RED 122
#define BACKGROUND_GREEN 122
#define BACKGROUND_BLUE 122

// class forward to keep compiler happy
class Renderable;

// Handles low-level SDL2 system init and render
class Window {
public:
    Window(int windowWidth, int windowHeight);
    ~Window();

    // Do not call this directly. Only children of Renderable must call it via parent constructor
    void addRenderable(Renderable *renderable, int priority);

    int getWindowHeight() const;

    int getWindowWidth() const;

    SDL_Renderer *renderer;

    void gameLoop();
private:
    bool running;
    int windowWidth;
    int windowHeight;
    int screenRefreshRate;
    SDL_Window *window;
    std::vector<std::pair<Renderable*, int>> renderables;

    void render();
    void handleEvents();
};


#endif //GREGCHESS_WINDOW_H
