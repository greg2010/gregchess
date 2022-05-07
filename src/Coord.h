#ifndef GREGCHESS_COORD_H
#define GREGCHESS_COORD_H

#include <cstdint>

#define COORD_BITFIELD_SIZE 4

class Coord {

    uint8_t i_x : COORD_BITFIELD_SIZE;
    uint8_t i_y : COORD_BITFIELD_SIZE;
public:
    [[nodiscard]] unsigned int x() const;

    [[nodiscard]] unsigned int y() const;

    [[nodiscard]] bool isEmpty() const;

    // A valid 8x8 board coordinate has x and y values in range 0..7
    Coord(unsigned int x, unsigned int y);

    // Represents an empty coordinate. Takes advantage of the fact that a valid coordinate has coords < 8.
    explicit Coord() = default;

    bool operator==(const Coord& other) const;

    Coord& operator=(const Coord& other);
};

#endif //GREGCHESS_COORD_H
