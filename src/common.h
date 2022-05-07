#ifndef GREGCHESS_COMMON_H
#define GREGCHESS_COMMON_H

#include <assert.h>

enum Piece {
    no_piece,
    king,
    queen,
    bishop,
    knight,
    rook,
    pawn
};

enum Color {
    no_color,
    black,
    white
};

#endif //GREGCHESS_COMMON_H
