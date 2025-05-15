#ifndef MOVE_GENERATION_H
#define MOVE_GENERATION_H

#include "Types.hpp"
#include "Board.hpp"
#include "LookupTables.hpp"

#include <intrin.h>
#include <list>

Bitboard getPawnMoves(Board board, Square square, Colour colour);
Bitboard getKnightMoves(Board board, Square square, Colour colour);
Bitboard getBishopMoves(Board board, Square square, Colour colour);
Bitboard getRookMoves(Board board, Square square, Colour colour);
Bitboard getKingMoves(Board board, Square square, Colour colour);
Bitboard getQueenMoves(Board board, Square square, Colour colour);

Bitboard getRayAttacks(Board board, Square square, int dir);
std::list<Move> getAllMoves(Board board, Colour colour);
Bitboard doGetMoves(Board board, Square square, Piece piece, Colour colour);

Bitboard getLeastSignificantBit(Bitboard bb);
Piece getPieceType(Board board, Bitboard piece);

#endif