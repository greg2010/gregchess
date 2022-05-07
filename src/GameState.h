#ifndef GREGCHESS_GAMESTATE_H
#define GREGCHESS_GAMESTATE_H


#include <vector>
#include <string>
#include "CompactPiece.h"
#include "ui/ColoredPiece.h"
#include "Move.h"
#include "Coord.h"
#include <bits/stdc++.h>


enum Castle {
    None, King, Queen, Both
};

enum Direction {
    N, NE, E, SE, S, SW, W, NW
};

// Encodes and decodes GameState. Uses mailbox notation to keep track of pieces
class GameState {
public:

    [[nodiscard]] Color getCurrentMoveColor() const;

    std::unordered_map<Color, Castle> castleAvailable;
    std::string enPassant;
    int halfmove;
    int fullmove;
    std::string fenStr;
    explicit GameState(std::string fenString);

    CompactPiece pieceAt(Coord coord);
    void makeMove(Move move);

    std::vector<Move> movesFor(const Coord &coord);


private:
    void placePieceAt(Coord coord, CompactPiece piece);
    std::array<std::array<CompactPiece, 8>, 8> boardArr;
    Color currentMoveColor;
    void parseFenToMailbox(std::string fen);

    std::vector<Move> movesForRook(const Coord& coord, Color color);

    std::list<Coord> scanLine(const Coord &coord, Direction d, int maxDist);

    std::vector<Move> movesForDirs(const Coord &coord, Color color, const std::vector<Direction>& dirs, int maxDist = -1, bool canTake = true);

    std::vector<Move> movesForBishop(const Coord &coord, Color color);

    std::vector<Move> movesForQueen(const Coord &coord, Color color);

    std::vector<Move> movesForKing(const Coord &coord, Color color);

    std::vector<Move> movesForKnight(const Coord &coord, Color color);

    std::vector<Move> movesForPawn(const Coord &coord, Color color);

};


#endif //GREGCHESS_GAMESTATE_H
