#include "Window.h"

bool compPairs(std::pair<Renderable *, int> lhs, std::pair<Renderable *, int> rhs) {
    return lhs.second < rhs.second;
}

Window::Window(int windowWidth, int windowHeight) {

    this->running = true;
    this->renderables = std::vector<std::pair<Renderable *, int>>();
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;

    int rendererFlags, windowFlags;
    rendererFlags = SDL_RENDERER_ACCELERATED;

    windowFlags = 0;
    windowFlags = SDL_WINDOW_RESIZABLE;

    // Initialize SDL and its subsystems

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        spdlog::error("Couldn't initialize SDL: {}", SDL_GetError());
        return;
    }

    if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 512) < 0) {
        spdlog::error("Failed to start audio subsystem: {}", Mix_GetError());
        return;
    }

    if (IMG_Init(0) < 0) {
        spdlog::error("Failed to start image subsystem: {}", IMG_GetError());
        return;
    }


    SDL_DisplayMode mode = SDL_DisplayMode{};
    if (SDL_GetDisplayMode(0, 0, &mode) < 0) {
        spdlog::error("Failed to get display mode: {}", SDL_GetError());
        screenRefreshRate = 60;
    }
    screenRefreshRate = mode.refresh_rate;

    // Create window
    window = SDL_CreateWindow("Greg's Chess",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              windowWidth,
                              windowHeight,
                              windowFlags);
    if (!window) {
        spdlog::error("Failed to open {} x {} window: {}", windowWidth, windowHeight, SDL_GetError());
        return;
    }
    SDL_SetWindowMinimumSize(window, MIN_WINDOW_WIDTH, MIN_WINDOW_HEIGHT);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, rendererFlags);
    if (!renderer){
        spdlog::error("Failed to create renderer: {}", SDL_GetError());
        return;
    }
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}

void Window::addRenderable(Renderable *renderable, int priority) {


    std::pair<Renderable*, int> pair = std::pair(renderable, priority);
    this->renderables.push_back(pair);
    std::sort(renderables.begin(), renderables.end(), compPairs);
}

void Window::render() {
    SDL_SetRenderDrawColor(renderer, BACKGROUND_RED, BACKGROUND_GREEN, BACKGROUND_BLUE, 255);
    SDL_RenderClear(renderer);

    for (auto elem : this->renderables) {
        elem.first->render();
    }

    SDL_RenderPresent(renderer);
}


void Window::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {

        // TODO handle window close more gracefully
        switch (event.type) {
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                    this->windowWidth = event.window.data1;
                    this->windowHeight = event.window.data2;
                }
                spdlog::debug("Received window resize event {} {}", windowWidth, windowHeight);
                break;
            case SDL_QUIT:
                spdlog::debug("Received quit event");
                this->running = false;
                break;
        }
        for (auto elem: this->renderables) {
            elem.first->handleEvent(&event);
        }
    }
}

Window::~Window() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


void Window::gameLoop() {

    // 1 second / screen refresh rate in hz
    int delay = 1000 / screenRefreshRate;

    while (running) {
        handleEvents();
        render();
        SDL_Delay(delay);
    }
}

int Window::getWindowWidth() const {
    return windowWidth;
}

int Window::getWindowHeight() const {
    return windowHeight;
}
