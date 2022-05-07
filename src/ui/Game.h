#ifndef GREGCHESS_GAME_H
#define GREGCHESS_GAME_H


#include <map>
#include "Renderable.h"
#include "Window.h"
#include "Board.h"
#include "../GameState.h"
#include "ColoredPiece.h"

// Main game class tying together UI and logic
class Game : Renderable {
public:
    Game(Window *window);
    Game(Window *window, std::string FENString);
    ~Game();
    void render();
    void handleEvent(SDL_Event *event);

private:
    const Window *window;
    Board *board;
    // Stores all textures for all pieces (Rook, Queen, etc)
    std::map<int, SDL_Texture*> pieceMap;

    // Move SFX
    Mix_Music *moveSFX;

    GameState *gameState;


    // Related to drawing moving pieces
    bool isHoldingPiece;
    ColoredPiece holdingPiece;
    Coord holdingPieceCoord;
    void handleMouseDown(int x, int y);
};


#endif //GREGCHESS_GAME_H
