#ifndef GREGCHESS_COMPACTPIECE_H
#define GREGCHESS_COMPACTPIECE_H

#include <cstdint>
#include <utility>
#include "common.h"
#include "ui/ColoredPiece.h"

class ColoredPiece;

// Represents piece and its color as a 16 bit unsigned int
class CompactPiece {
public:
    CompactPiece();
    CompactPiece(Color color, Piece piece);
    Color getColor();
    Piece getPiece();

    bool operator==(int other) const;
    uint8_t toInt() const;
    ColoredPiece toColored();
private:
    uint8_t pieceRepr;
};


#endif //GREGCHESS_COMPACTPIECE_H
