#include "CompactPiece.h"

CompactPiece::CompactPiece() {
    pieceType = 0;
    pieceColor = 0;
}
CompactPiece::CompactPiece(Color color, Piece piece) {
    pieceType = piece;
    pieceColor = color;
}


Color CompactPiece::getColor() const {
    return (Color) pieceColor;
}


Piece CompactPiece::getPiece() const {
    return (Piece) pieceType;
}

bool CompactPiece::operator==(uint8_t other) const {
    return this->toInt() == other;
}

uint8_t CompactPiece::toInt() const {
    return (pieceType | (pieceColor << CPIECE_BITFIELD_SIZE));
}

ColoredPiece CompactPiece::toColored() {
    return ColoredPiece(this->getColor(), this->getPiece());
}

bool CompactPiece::operator==(CompactPiece& other) const {
    return pieceColor == other.pieceColor && pieceType == other.pieceType;
}


