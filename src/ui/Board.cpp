#include "Board.h"
#include "../common.h"

int getCellDim(const Window *window) {
    int minDim = std::min(window->getWindowWidth(), window->getWindowHeight());
    return minDim / 8;
}

Board::Board(Window *window): Renderable(window, 0) {
    this->lightRed = LIGHT_RED;
    this->lightGreen = LIGHT_GREEN;
    this->lightBlue = LIGHT_BLUE;
    this->lightAlpha = LIGHT_ALPHA;

    this->darkRed = DARK_RED;
    this->darkGreen = DARK_GREEN;
    this->darkBlue = DARK_BLUE;
    this-> darkAlpha = DARK_ALPHA;

    this->window = window;
}

Board::Board(int lightRed, int lightGreen, int lightBlue, int lightAlpha,
             int darkRed, int darkGreen, int darkBlue, int darkAlpha,
             Window * window): Renderable(window, 0) {
    this->lightRed = lightRed;
    this->lightGreen = lightGreen;
    this->lightBlue = lightBlue;
    this->lightAlpha = lightAlpha;

    this->darkRed = darkRed;
    this->darkGreen = darkGreen;
    this->darkBlue = darkBlue;
    this-> darkAlpha = darkAlpha;
}


void Board::render() {

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            SDL_Rect r = getSDLRectFor(i, j);
            rectCoordArr[i][j] = r;
            if ((i + j) % 2 == 0) {
                SDL_SetRenderDrawColor(window->renderer,
                                       this->lightRed,
                                       this->lightGreen,
                                       this->lightBlue,
                                       this->lightAlpha);
            } else {
                SDL_SetRenderDrawColor(window->renderer,
                                       this->darkRed,
                                       this->darkGreen,
                                       this->darkBlue,
                                       this->darkAlpha);
            }
            SDL_RenderFillRect(window->renderer, &r );
        }
    }
}

void Board::handleEvent(SDL_Event *event) {}

SDL_Rect Board::getSDLRectFor(int i, int j) {
    int cellDim = getCellDim(this->window);
    int paddingX = (window->getWindowWidth() - cellDim * 8) / 2;
    int paddingY = (window->getWindowHeight() - cellDim * 8) / 2;
    return {paddingX + j * cellDim,
            paddingY + i * cellDim,
            cellDim,
            cellDim};
}

Coord Board::getCellIndexForCoords(int x, int y) {
    for (unsigned int i = 0; i < 8; ++i) {
        for (unsigned int j = 0; j < 8; ++j) {
            SDL_Rect cell = rectCoordArr[i][j];
            if ((cell.x <= x) && (x <= cell.x + cell.w) && (cell.y <= y) && (y <= cell.y + cell.h)) {
                return {i, j};
            }
        }
    }
    return Coord();
}
