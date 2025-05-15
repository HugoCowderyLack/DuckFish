#ifndef BOARD_H
#define BOARD_H

#include "Types.hpp"
#include "Output.hpp"

class Board {
public:
    // Board(FEN fen);
    Board();
    void printBoard() const;
    bool makeMove(Move move);
    Bitboard getPieceBB(Piece piece);
    Bitboard getColourBB(Colour colour);
    Bitboard getOccupiedBB();
    bool isWhiteToMove();
    Bitboard getEnPassantSquare(Colour colour);
    uint8_t getCastlingRights();

private:
    bool whiteToMove;
    uint8_t castlingRights;
    uint8_t enPassantTarget;
    int numHalfMoves;
    Bitboard PieceBBs[NUM_PIECES];
    Bitboard ColourBBs[NUM_COLOURS];
    Bitboard OccupiedBB;
};

void printBitBoard(Bitboard bitboard);

#endif