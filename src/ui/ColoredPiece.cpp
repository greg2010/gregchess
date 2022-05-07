#include "ColoredPiece.h"


ColoredPiece::ColoredPiece() : ColoredPiece(no_color, no_piece) {}

ColoredPiece::ColoredPiece(Color color, Piece piece) {
    this->color = color;
    this->piece = piece;
}

Color ColoredPiece::getColor() const {
    return color;
}

Piece ColoredPiece::getPiece() const {
    return piece;
}

bool ColoredPiece::isNull() {
    return color == no_color || piece == no_piece;
}

CompactPiece ColoredPiece::toCompact() {
    return CompactPiece(color, piece);
}

int ColoredPiece::toInt() {
    return CompactPiece(color, piece).toInt();
}
