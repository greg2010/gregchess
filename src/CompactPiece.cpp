#include "CompactPiece.h"

#define COLOR_SHIFT_DEPTH 4
#define PIECE_AND_VALUE 15

CompactPiece::CompactPiece() {
    pieceRepr = 0;
}
//color||piece
//  0000 0000
//  1111 1111
CompactPiece::CompactPiece(Color color, Piece piece) {
    pieceRepr = (color << COLOR_SHIFT_DEPTH) | piece;
}

// Grab last 4 bits
Color CompactPiece::getColor() {
    return (Color) (pieceRepr >> COLOR_SHIFT_DEPTH);
}

// Grab first 4 bits
Piece CompactPiece::getPiece() {
    return (Piece) (pieceRepr & PIECE_AND_VALUE);
}

bool CompactPiece::operator==(int other) const {
    return pieceRepr == other;
}

uint8_t CompactPiece::toInt() const {
    return pieceRepr;
}

ColoredPiece CompactPiece::toColored() {
    return ColoredPiece(this->getColor(), this->getPiece());
}


