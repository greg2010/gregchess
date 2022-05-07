#ifndef GREGCHESS_COORD_H
#define GREGCHESS_COORD_H

class Coord {

    unsigned int i_xy = 0b11111111;
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
