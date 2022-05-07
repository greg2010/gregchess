#ifndef GREGCHESS_BOARD_H
#define GREGCHESS_BOARD_H

#define LIGHT_RED 240
#define LIGHT_GREEN 217
#define LIGHT_BLUE 181
#define LIGHT_ALPHA 255

#define DARK_RED 181
#define DARK_GREEN 136
#define DARK_BLUE 99
#define DARK_ALPHA 255



#include "Renderable.h"
#include <SDL.h>
#include "Window.h"
#include "../common.h"
#include "../Coord.h"

// Draws chess board underneath pieces
class Board : public Renderable {
public:
    explicit Board(Window *window);
    Board(int lightRed, int lightGreen, int lightBlue, int lightAlpha, int darkRed, int darkGreen, int darkBlue,
          int darkAlpha, Window *window);
    void render();
    void handleEvent(SDL_Event *event);
    SDL_Rect getSDLRectFor(int i, int j);
    Coord getCellIndexForCoords(int x, int y);
private:
    const Window *window;
    int lightRed;
    int lightGreen;
    int lightBlue;
    int lightAlpha;
    int darkRed;
    int darkGreen;
    int darkBlue;
    int darkAlpha;
    Board();

    SDL_Rect rectCoordArr[8][8];
};


#endif //GREGCHESS_BOARD_H
