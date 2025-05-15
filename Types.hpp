#ifndef TYPE_H
#define TYPE_H

#include <cstdint>
#include <string>

#define NUM_SQUARES 64
#define WHITE_OO_MASK 0x0000000000000050ULL
#define WHITE_OOO_MASK 0x0000000000000014ULL
#define BLACK_OO_MASK 0x5000000000000000ULL
#define BLACK_OOO_MASK 0x1400000000000000ULL

#define WHITE_OO_RIGHTS_MASK 0x1
#define WHITE_OOO_RIGHTS_MASK 0x2
#define BLACK_OO_RIGHTS_MASK 0x4
#define BLACK_OOO_RIGHTS_MASK 0x8

using Bitboard = uint64_t;
using Square = int;
using FEN = std::string;

enum Direction {
    NORTH,
    NORTH_EAST,
    EAST,
    SOUTH_EAST,
    SOUTH,
    SOUTH_WEST,
    WEST,
    NORTH_WEST,
    NUM_DIR
};

const int dirVectors[NUM_DIR] = {8, 9, 1, -7, -8, -9, -1, 7};
const Bitboard rayStoppers[NUM_DIR] = {
    0xFF00000000000000ULL,
    0xFF80808080808080ULL,
    0x8080808080808080ULL,
    0x80808080808080FFULL,
    0x00000000000000FFULL,
    0x01010101010101FFULL,
    0x0101010101010101ULL,
    0xFF01010101010101ULL,  
};

enum Piece {
    PAWN,
    ROOK,
    KNIGHT,
    BISHOP,
    QUEEN,
    KING,
    NUM_PIECES,
    NONE
};

enum Colour {
    WHITE,
    BLACK,
    NUM_COLOURS
};

struct Move {
    Colour colour;
    Piece piece;
    Bitboard fromToBB;
    Piece cPiece;   // NONE if not a capture
    bool isEnPassant;
    uint8_t isCastle;
    Piece isPromotion;
};

#endif