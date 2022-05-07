#ifndef GREGCHESS_COMPACTPIECE_H
#define GREGCHESS_COMPACTPIECE_H

#include <cstdint>
#include <utility>
#include "common.h"
#include "ui/ColoredPiece.h"


#define CPIECE_BITFIELD_SIZE 4

class ColoredPiece;

// Represents piece and its color as a 16 bit unsigned int
class CompactPiece {
public:
    CompactPiece();
    CompactPiece(Color color, Piece piece);
    Color getColor() const;
    Piece getPiece() const;

    bool operator==(uint8_t other) const;
    bool operator==(CompactPiece& other) const;
    uint8_t toInt() const;
    ColoredPiece toColored();
private:
    uint8_t pieceType : CPIECE_BITFIELD_SIZE;
    uint8_t pieceColor : CPIECE_BITFIELD_SIZE;
};


#endif //GREGCHESS_COMPACTPIECE_H
