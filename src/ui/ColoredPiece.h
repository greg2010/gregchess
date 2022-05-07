#ifndef GREGCHESS_COLOREDPIECE_H
#define GREGCHESS_COLOREDPIECE_H


#include "../CompactPiece.h"


class CompactPiece;

class ColoredPiece {
public:
    ColoredPiece();
    ColoredPiece(Color color, Piece piece);
    Color getColor() const;

    Piece getPiece() const;

    bool isNull();

    CompactPiece toCompact();
    int toInt();

private:
    Color color;
    Piece piece;
};


#endif //GREGCHESS_COLOREDPIECE_H
