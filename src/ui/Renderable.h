#ifndef GREGCHESS_RENDERABLE_H
#define GREGCHESS_RENDERABLE_H


#include <SDL.h>
#include "Window.h"

class Window;

class Renderable {
public:
    Renderable(Window *window, int priority);
    virtual void render() = 0;
    virtual void handleEvent(SDL_Event *event) = 0;
};


#endif //GREGCHESS_RENDERABLE_H
