#include "Renderable.h"


Renderable::Renderable(Window *window, int priority) {
    window->addRenderable(this, priority);
}