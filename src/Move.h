#ifndef GREGCHESS_MOVE_H
#define GREGCHESS_MOVE_H


#include "common.h"
#include "Coord.h"

// https://www.chessprogramming.org/Encoding_Moves
enum MoveType {
    QUIET,
    DOUBLE_PAWN_PUSH,
    KING_CASTLE,
    QUEEN_CASTLE,
    CAPTURE,
    EP_CAPTURE,
    KNIGHT_PROMO,
    BISHOP_PROMO,
    ROOK_PROMO,
    QUEEN_PROMO,
    KNIGHT_PROMO_CAPTURE,
    BISHOP_PROMO_CAPTURE,
    ROOK_PROMO_CAPTURE,
    QUEEN_PROMO_CAPTURE
};

class Move {
    const int type: 4;
public:
    explicit Move(Coord from, Coord to);
    Move(Move move, MoveType newType);
    Move(Coord from, Coord to, MoveType type);
    const Coord from;
    const Coord to;

    [[nodiscard]] MoveType getMoveType() const;
};


#endif //GREGCHESS_MOVE_H
