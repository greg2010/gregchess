#include "GameState.h"
#include "Coord.h"
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Ray {
public:
    const Coord from;
    const Coord to;
    bool isEmpty() {
        return from == to;
    }
};

// Utility - splits string s by char c
vector<string> splitBy(string s, const char c) {
    auto end = s.cend();
    auto start = end;

    std::vector<std::string> v;
    for( auto it = s.cbegin(); it != end; ++it ) {
        if( *it != c ) {
            if( start == end )
                start = it;
            continue;
        }
        if( start != end ) {
            v.emplace_back(start, it);
            start = end;
        }
    }
    if( start != end )
        v.emplace_back(start, end);
    return v;
}

// Converts GameState character representing piece to tuple of Color and Piece
ColoredPiece charToColoredPiece(char c) {
    Color color = isupper(c) ? white : black;

    switch (tolower(c)) {
        case 'p':
            return {color, Piece::pawn};
        case 'n':
            return {color, Piece::knight};
        case 'b':
            return {color, Piece::bishop};
        case 'r':
            return {color, Piece::rook};
        case 'q':
            return {color, Piece::queen};
        case 'k':
            return {color, Piece::king};
    }
    return {Color::no_color, Piece::no_piece};
}

int fenCastleToInt(char c) {
    int castle = 0;

    // Tied into castle enum, or-ing 1 and 2 yields 3 which is index of "Both"
    return tolower(c) == 'k' ? 1 : 2;
}

unordered_map<Color, Castle> castleFromFen(string fen) {
    if (fen == "-") {
        return {{white, None}, {black, None}};
    }

    int w = 0;
    int b = 0;
    for (auto c : fen) {
        if (isupper(c)) {
            w |= fenCastleToInt(c);
        } else {
            b |= fenCastleToInt(c);
        }
    }

    return {{white, (Castle) w}, {black, (Castle) b}};
}

// Parses the GameState piece string to mailbox
void GameState::parseFenToMailbox(string fen) {
    vector<string>linePieces = splitBy(fen, '/');
    for (int i = 0; i < 8; ++i) {
        string word = linePieces[i];
        int jOut = 0;
        for (int j = 0; j < word.length(); ++j) {
            char c = word[j];
            if (isdigit(c)) {
                int toSkip = atoi(&c);
                int upper = jOut + toSkip;
                for (; jOut < upper; ++jOut) {
                    boardArr[i][jOut] = CompactPiece(Color::no_color, Piece::no_piece);
                }
            } else {
                ColoredPiece cp = charToColoredPiece(c);
                boardArr[i][jOut] = CompactPiece(cp.getColor(), cp.getPiece());
                ++jOut;
            }
        }
    }
}

GameState::GameState(std::string fenString) {
    fenStr = fenString;
    vector<string> fenPieces = splitBy(fenString, ' ');
    parseFenToMailbox(fenPieces[0]);

    currentMoveColor = fenPieces[1] == "w" ? white : black;
    castleAvailable = castleFromFen(fenPieces[2]);
    enPassant = fenPieces[3];
    halfmove = atoi(fenPieces[4].c_str());
    fullmove = atoi(fenPieces[5].c_str());
}

void GameState::placePieceAt(Coord coord, CompactPiece piece) {
    boardArr[coord.x()][coord.y()] = CompactPiece(piece.getColor(), piece.getPiece());
}

void GameState::makeMove(Move move) {
    placePieceAt(move.to, pieceAt(move.from));
    placePieceAt(move.from, CompactPiece());
    currentMoveColor = getCurrentMoveColor() == white ? black : white;
}

// TODO make this return start and end coordinates for the ray
std::list<Coord> GameState::scanLine(const Coord &coord, Direction d, int maxDist) {
    int upper = 7;
    int lower = 0;

    list<Coord> scanned = {};
    bool rayHit = false;
    unsigned int iterI = coord.x();
    unsigned int iterJ = coord.y();

    int dist = 0;

    while (!rayHit && (maxDist == -1 || dist < maxDist)) {

        // Advance ray trace
        switch (d) {
            case N:
                --iterI;
                break;
            case NE:
                --iterI;
                ++iterJ;
                break;
            case E:
                ++iterJ;
                break;
            case SE:
                ++iterI;
                ++iterJ;
                break;
            case S:
                ++iterI;
                break;
            case SW:
                ++iterI;
                --iterJ;
                break;
            case W:
                --iterJ;
                break;
            case NW:
                --iterI;
                --iterJ;
                break;
        }

        // Detect boundary
        if (iterI < lower || iterI > upper || iterJ < lower || iterJ > upper) {
            rayHit = true;

        // Detect piece occlusion
        } else if (boardArr[iterI][iterJ] != 0) {
            rayHit = true;
            scanned.emplace_back(iterI, iterJ);
        } else {
            scanned.emplace_back(iterI, iterJ);
        }
        // increment distance
        ++dist;
    }

    return scanned;
}

// Calculates linear moves for array of direction dirs. Takes into account color.
// Pieces can take the opposite color but can't take their own color.
vector<Move> GameState::movesForDirs(const Coord &coord,
                                     const Color color,
                                     const std::vector<Direction>& dirs,
                                     int maxDist, bool canTake) {
    vector<Move> moves = {};

    for (auto dir : dirs) {
        auto dirScanned = scanLine(coord, dir, maxDist);
        for (auto move : dirScanned) {
            auto pieceAt = boardArr[move.x()][move.y()];
            // Reject moves that encroach on the same colored piece
            if (pieceAt != 0 && pieceAt.getColor() == color) continue;
            // If taking is disallowed reject it too
            if (pieceAt != 0 && !canTake) continue;

            moves.emplace_back(coord, move);
        }
    }

    return moves;
}

vector<Move> GameState::movesForRook(const Coord& coord, Color color) {
    return movesForDirs(coord,color, {Direction::N, Direction::S, Direction::W, Direction::E});
}

vector<Move> GameState::movesForBishop(const Coord &coord, Color color) {
    return movesForDirs(coord,color, {Direction::NE, Direction::NW, Direction::SE, Direction::SW});
}

vector<Move> GameState::movesForQueen(const Coord &coord, Color color) {
    std::vector<Direction> directions = {};
    // There are total of 8 cardinal directions
    for (int i = 0; i < 8; ++i) {
        // Cast int i to Direction enum
        directions.push_back((Direction) i);
    }
    return movesForDirs(coord,color, directions);
}



vector<Move> GameState::movesForKing(const Coord &coord, const Color color) {
    // First, generate normal king moves
    std::vector<Direction> directions = {};
    // There are total of 8 cardinal directions
    for (int ii = 0; ii < 8; ++ii) {
        // Cast int i to Direction enum
        directions.push_back((Direction) ii);
    }

    vector<Move> moves = movesForDirs(coord,color, directions, 1);


    // Then, generate castle moves
    Castle castle = castleAvailable.at(color);

    // Verify that lines are between king and rook and empty
    auto verifyLineClear =  [&](Direction d, int lastJ) {
       auto scanned = scanLine(coord, d, -1);
       return !scanned.empty() && scanned.back().y() == lastJ;
    };

    switch (castle) {
        case Both: // Fallthrough
        case King: // Fallthrough if castle != King
            if (verifyLineClear(Direction::E, 7)) moves.push_back(Move(coord, {coord.x(), 7}));
            if (castle == King) break;
        case Queen: // Fallthrough if castle != Queen
            if (verifyLineClear(Direction::W, 0)) moves.push_back(Move(coord, {coord.x(), 0}));
            if (castle == Queen) break;
        case None:
            break;
    }
    return moves;
}

vector<Move> GameState::movesForKnight(const Coord &coord, const Color color) {
    vector<Move> moves = {};

    // First, iterate over all possible moves
    vector<int> validMoveDist = {1, -1, 2, -2};
    for (int dist1 : validMoveDist) {
        for (int dist2 : validMoveDist) {
            // For the knight, one coord must change by 1 and the other by 2
            if (abs(dist1) != abs(dist2)) {
                unsigned int moveI = coord.x() + dist1;
                unsigned int moveJ = coord.y() + dist2;

                // Skip moves that exceed boundaries
                if (moveI < 0 || moveI > 7 || moveJ < 0 || moveJ > 7) continue;

                // Reject moves that encroach on the same colored piece
                auto pieceAt = boardArr[moveI][moveJ];
                if (pieceAt != 0 && pieceAt.getColor() == color) continue;

                // Finally, record valid move
                moves.push_back(Move(coord, {moveI, moveJ}));
            }
        }
    }

    return moves;
}

// Generates semi-valid moves for pawns
vector<Move> GameState::movesForPawn(const Coord &coord, Color color) {
    vector<Move> moves;

    // First, calculate normal pawn moves
    if (color == black) {
        // black pawn in starting location
        int allowedDist = coord.x() == 1 ? 2 : 1;
        moves = movesForDirs(coord,color, {Direction::S}, allowedDist, false);
    } else if (color == white) {
        // white pawn in starting location
        int allowedDist = coord.x() == 6 ? 2 : 1;
        moves = movesForDirs(coord,color, {Direction::N}, allowedDist, false);
    } else {
        // unreachable
        assert(false);
    }
    if (moves.size() == 2) {
        auto newMove =  Move(moves.back(), MoveType::DOUBLE_PAWN_PUSH);
        moves.pop_back();
        moves.push_back(newMove);
    }

    // Then, calculate take moves
    if (color == black) {
        auto maybeTakes = movesForDirs(coord, color, {Direction::SE, Direction::SW}, 1);
        for (auto maybeTake : maybeTakes) {
            auto pieceAt = boardArr[maybeTake.to.x()][maybeTake.to.y()];
            if (pieceAt != 0) moves.push_back(maybeTake);
        }

    } else {
        auto maybeTakes = movesForDirs(coord ,color, {Direction::NE, Direction::NW}, 1);
        for (auto maybeTake : maybeTakes) {
            auto pieceAt = boardArr[maybeTake.to.x()][maybeTake.to.y()];
            if (pieceAt != 0) moves.push_back(maybeTake);
        }
    }

    return moves;
}

vector<Move> GameState::movesFor(const Coord &coord) {
    CompactPiece piece = boardArr[coord.x()][coord.y()];
    ColoredPiece cPiece = piece.toColored();
    switch (cPiece.getPiece()) {
        case pawn:
            return movesForPawn(coord ,cPiece.getColor());
        case king:
            return movesForKing(coord,cPiece.getColor());
        case queen:
            return movesForQueen(coord,cPiece.getColor());
        case bishop:
            return movesForBishop(coord,cPiece.getColor());
        case knight:
            return movesForKnight(coord,cPiece.getColor());
        case rook:
            return movesForRook(coord, cPiece.getColor());
        case no_piece:
        default:
            return {};
    }
}

Color GameState::getCurrentMoveColor() const {
    return currentMoveColor;
}

CompactPiece GameState::pieceAt(Coord coord) {
    assert(!coord.isEmpty());
    return boardArr[coord.x()][coord.y()];
}
