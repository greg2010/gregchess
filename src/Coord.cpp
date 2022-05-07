#include "Coord.h"


#include <cassert>


[[nodiscard]] unsigned int Coord::x() const {
    return i_x;
}

[[nodiscard]] unsigned int Coord::y() const {
    return i_y;
}

[[nodiscard]] bool Coord::isEmpty() const {
    return x() > 7 || y() > 7;
}

// A valid 8x8 board coordinate has x and y values in range 0..7
Coord::Coord(const unsigned int x, const unsigned int y) {
    assert(x < 8 && y < 8);
    i_x = x;
    i_y = y;
}

bool Coord::operator==(const Coord& other) const {
    return x() == other.x() && y() == other.y();
}

Coord& Coord::operator=(const Coord& other) {
    i_x = other.x();
    i_y = other.y();
    return *this;
}
