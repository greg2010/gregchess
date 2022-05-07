#include "Move.h"
#include "Coord.h"

Move::Move(Coord from, Coord to) : Move(from, to, MoveType::QUIET) {}

Move::Move(Coord from, Coord to, MoveType type): from(from), to(to), type(type) {}

MoveType Move::getMoveType() const {
    return (MoveType) type;
}

Move::Move(Move move, MoveType type) : Move(move.from, move.to, type) {}
