#include "Coord.h"


#include <cassert>

unsigned int toSingleInt(const unsigned int x, const unsigned int y) {
    unsigned int xy = x;
    xy |= (y << 4);
    return xy;
}


[[nodiscard]] unsigned int Coord::x() const {
    return i_xy & 0b00001111;
}

[[nodiscard]] unsigned int Coord::y() const {
    return (i_xy & 0b11110000) >> 4;
}

[[nodiscard]] bool Coord::isEmpty() const {
    return x() > 7 || y() > 7;
}

// A valid 8x8 board coordinate has x and y values in range 0..7
Coord::Coord(const unsigned int x, const unsigned int y) {
    assert(x < 8 && y < 8);
    i_xy = toSingleInt(x, y);
}

bool Coord::operator==(const Coord& other) const {
    return x() == other.x() && y() == other.y();
}

Coord& Coord::operator=(const Coord& other) {
    i_xy = toSingleInt(other.x(), other.y());
    return *this;
}
