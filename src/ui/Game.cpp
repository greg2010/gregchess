#include "Game.h"

std::string getPieceFn(Color enumColor, Piece enumPiece) {
    // If we are given invalid piece, no texture path exists
    if (enumPiece == no_piece || enumColor == no_color) return "";

    // extract char for color [bw]
    char color;
    if (enumColor == Color::white) {
        color = 'w';
    } else {
        color = 'b';
    }

    // extract char for piece [KQBNRP]
    char piece;
    switch (enumPiece) {
        case Piece::king:
            piece = 'K';
            break;
        case Piece::queen:
            piece = 'Q';
            break;
        case Piece::bishop:
            piece = 'B';
            break;
        case Piece::knight:
            piece = 'N';
            break;
        case Piece::rook:
            piece = 'R';
            break;
        case Piece::pawn:
            piece = 'P';
            break;
    }

    return fmt::format("../assets/{}{}.png", color, piece);
}


// Default GameState string
Game::Game(Window *window) : Game(window, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1") {}

Game::Game(Window *window, std::string FENString) : Renderable(window, 1) {
    this->window = window;
    this->board = new Board(window);
    this->gameState = new GameState(FENString);
    this->isHoldingPiece = false;
    this->holdingPiece = ColoredPiece(no_color, no_piece);

    this->moveSFX = Mix_LoadMUS("../assets/move.ogg");

    for (int color = 1; color < 3; ++color) {
        for (int piece = 1; piece < 7; ++piece) {
            auto enumColor = (Color) color;
            auto enumPiece = (Piece) piece;
            auto coloredPiece = ColoredPiece(enumColor, enumPiece);
            std::string texturePath = getPieceFn(enumColor, enumPiece);
            SDL_Texture *texture = IMG_LoadTexture(window->renderer, texturePath.c_str());
            this->pieceMap[coloredPiece.toInt()] = texture;
        }
    }
    this->pieceMap[ColoredPiece(no_color, no_piece).toInt()] = nullptr;

}

void Game::render() {
    // Render potential move location
    if (isHoldingPiece) {
        SDL_Rect rect = this->board->getSDLRectFor(holdingPieceCoord.x(),holdingPieceCoord.y());
        SDL_SetRenderDrawColor(window->renderer,0 ,255,255,50);
        SDL_RenderFillRect(window->renderer, &rect);
        std::vector<Move> moves = gameState->movesFor(holdingPieceCoord);
        for (auto move : moves) {
            SDL_Rect moveRect = board->getSDLRectFor(move.to.x(), move.to.y());
            SDL_SetRenderDrawColor(window->renderer,0 ,255,255,50);
            SDL_RenderFillRect(window->renderer, &moveRect);
        }

    }

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (isHoldingPiece) {
                if (i == holdingPieceCoord.x() && j == holdingPieceCoord.y()) {
                    // This piece is being held, skip render
                    continue;
                }
            }
            SDL_Rect rect = this->board->getSDLRectFor(i,j);
            CompactPiece cPiece = gameState->pieceAt(Coord(i,j));
            Color color = cPiece.getColor();
            Piece piece = cPiece.getPiece();
            SDL_RenderCopy(window->renderer,
                           pieceMap.at(ColoredPiece(color, piece).toInt()),
                           nullptr,
                           &rect);
        }
    }

    if (isHoldingPiece) {
        int mouseX, mouseY = 0;
        SDL_GetMouseState(&mouseX, &mouseY);
        int cellDim = this->board->getSDLRectFor(0,0).h;
        SDL_Rect drawRect = { mouseX, mouseY, cellDim, cellDim};
        SDL_RenderCopy(window->renderer,
                       pieceMap.at(holdingPiece.toInt()),
                       nullptr, &drawRect);

    }
}

void Game::handleEvent(SDL_Event *event) {
    switch (event->type) {
        case SDL_MOUSEBUTTONDOWN:
            if (event->button.button == SDL_BUTTON_LEFT) {
                handleMouseDown(event->button.x, event->button.y);
            }
            break;
    }
}

void Game::handleMouseDown(int x, int y) {
    Coord index = board->getCellIndexForCoords(x, y);
    // We found the index
    if (!index.isEmpty()) {
        if (!isHoldingPiece) {
            CompactPiece cPiece = gameState->pieceAt(index);
            // Clicked empty cell, do nothing
            if (cPiece == 0) return;
            isHoldingPiece = true;
            holdingPiece = cPiece.toColored();
            holdingPieceCoord = index;
        } else {
            Mix_PlayMusic(moveSFX, 1);
            isHoldingPiece = false;
            gameState->makeMove(Move(holdingPieceCoord, index));
            //gameState->placePieceAt(index.first, index.second, holdingPiece);
        }
    }
}

Game::~Game() {
    Mix_FreeMusic(moveSFX);
    for (auto elem : pieceMap) {
        if (elem.second != nullptr) {
            SDL_DestroyTexture(elem.second);
        }
    }
    delete gameState;
    delete board;
}
