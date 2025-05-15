#include "MoveGeneration.hpp"
#include <iostream>

//TODO: 
// -fix the terrible pawn method
// -make each piece function return a list and then get all moves combines all of them
// -castling

Bitboard getPawnMoves(Board board, Square square, Colour colour) {
    Bitboard bb = 0ULL;
    if (colour == WHITE) {
        if ((1ULL << (square + 8)) & ~board.getOccupiedBB()) {
            bb |= 1ULL << (square + 8);
            if ((1ULL << square) & 0x000000000000FF00ULL && 
                (1ULL << (square + 16)) & ~board.getOccupiedBB()) {
                    bb |= 1ULL << (square + 16);
                }
        }
        if (square % 8 != 0 && (1ULL << (square + 7)) & (board.getColourBB(BLACK) | board.getEnPassantSquare(colour))) {
            bb |= 1ULL << (square + 7);
        }
        if (square % 8 != 7 && (1ULL << (square + 9)) & (board.getColourBB(BLACK) | board.getEnPassantSquare(colour))) {
            bb |= 1ULL << (square + 9);
        }
    } else {
        if ((1ULL << (square - 8)) & ~board.getOccupiedBB()) {
            bb |= 1ULL << (square - 8);
            if ((1ULL << square) & 0x00FF000000000000ULL && 
                (1ULL << (square - 16)) & ~board.getOccupiedBB()) {
                    bb |= 1ULL << (square - 16);
                }
        }
        if (square % 8 != 7 && 1ULL << (square - 7) & (board.getColourBB(WHITE) | board.getEnPassantSquare(colour))) {
            bb |= 1ULL << (square - 7);
        }
        if (square %8 != 0 && 1ULL << (square - 9) & (board.getColourBB(WHITE) | board.getEnPassantSquare(colour))) {
            bb |= 1ULL << (square - 9);
        }
    }
    return bb;
}

Bitboard getKnightMoves(Board board, Square square, Colour colour) {
    return knightLookUp(square) & ~(colour == WHITE ? board.getColourBB(WHITE) : board.getColourBB(BLACK));
}

Bitboard getBishopMoves(Board board, Square square, Colour colour) {
    Bitboard bb = 0ULL;
    for (int dir = 0; dir < NUM_DIR; dir++) {
        if (dir % 2 == 0) {
            continue;
        }
        bb |= getRayAttacks(board, square, dir);
    }
    return bb & ~(colour == WHITE ? board.getColourBB(WHITE) : board.getColourBB(BLACK));
}

Bitboard getRookMoves(Board board, Square square, Colour colour) {
    Bitboard bb = 0ULL;
    for (int dir = 0; dir < NUM_DIR; dir++) {
        if (dir % 2 == 1) {
            continue;
        }
        bb |= getRayAttacks(board, square, dir);
    }
    return bb & ~(colour == WHITE ? board.getColourBB(WHITE) : board.getColourBB(BLACK));
}

Bitboard getKingMoves(Board board, Square square, Colour colour) {
    Bitboard bb = 0ULL;
    Bitboard king = 1ULL << square;
    for (int dir = 0; dir < NUM_DIR; dir++) {
        if ((1ULL << square) & rayStoppers[dir]) {
            continue;
        }
        bb |= dirVectors[dir] > 0 ? king << (dirVectors[dir]) : king >> (-dirVectors[dir]);
    }

    return bb & ~(colour == WHITE ? board.getColourBB(WHITE) : board.getColourBB(BLACK));
}

Bitboard getQueenMoves(Board board, Square square, Colour colour) {
    return getBishopMoves(board, square, colour) | getRookMoves(board, square, colour);
}

Bitboard getRayAttacks(Board board, Square square, int dir) {
    Bitboard attacks = rayLookUp(square, dir); 
    Bitboard blocker = attacks & board.getOccupiedBB();
    unsigned long sq = square;
    dirVectors[dir] > 0 ? _BitScanForward64(&sq, blocker | 0x8000000000000000ULL) : _BitScanReverse64(&sq, blocker | 1ULL); // gets the square of the first blocker piece
    return attacks ^ rayLookUp(sq, dir);    // removes section of ray that blocked piece blocks
}

std::list<Move> getAllMoves(Board board, Colour colour) {
    std::list<Move> moveList;
    for (int p = 0; p < NUM_PIECES; p++) {
        Piece piece = static_cast<Piece>(p);
        Bitboard pieceBB = board.getPieceBB(static_cast<Piece>(piece)) & board.getColourBB(colour);
        while (pieceBB) {
            Bitboard nextPiece = getLeastSignificantBit(pieceBB); // extract a single piece 
            pieceBB ^= nextPiece;
            unsigned long square;
            _BitScanForward64(&square, nextPiece);
            Bitboard moveBB = doGetMoves(board, square, piece, colour); // get all moves that piece can make
            while (moveBB) {
                Bitboard nextMove = getLeastSignificantBit(moveBB); // extract a single move
                moveBB ^= nextMove;
                Piece cPiece = (nextMove & board.getOccupiedBB()) ? getPieceType(board, nextMove) : NONE; // determine if this is a capture
                moveList.push_back({colour, static_cast<Piece>(piece), nextMove | nextPiece, cPiece});   // add move to the moveList
            }
        }
    }
    return moveList;
}

Bitboard doGetMoves(Board board, Square square, Piece piece, Colour colour) {
    switch (piece) {
    case PAWN:
        return getPawnMoves(board, square, colour);
    case KNIGHT:
        return getKnightMoves(board, square, colour);
    case BISHOP:
        return getBishopMoves(board, square, colour);
    case ROOK:
        return getRookMoves(board, square, colour);
    case QUEEN:
        return getQueenMoves(board, square, colour);
    case KING:
        return getKingMoves(board, square, colour);
    default:
        return 0ULL;
    }
}

Bitboard getLeastSignificantBit(Bitboard bb) {
    return bb & -bb;
}

Piece getPieceType(Board board, Bitboard piece) {
    for (int p = 0; p < NUM_PIECES; p++) {
        if (board.getPieceBB(static_cast<Piece>(p)) & piece) {
            return static_cast<Piece>(p);
        }
    }
    return NONE;
}

Move createMove(Board board, Bitboard fromToBB, Piece piece, Colour colour) {
    Bitboard fromBB = fromToBB & board.getColourBB(colour);
    Bitboard toBB = fromToBB & board.getColourBB(colour == WHITE ? BLACK : WHITE);
    Move move = {colour, piece, fromToBB, NONE, false, 0, NONE};
    switch (piece) {
    case PAWN:
        if (fromToBB & board.getEnPassantSquare(colour)) {
            move.isEnPassant = true;
        }
        // check for promotion
        break;
    case KING:
        if (fromToBB == WHITE_OO_MASK) {
            move.isCastle = WHITE_OO_RIGHTS_MASK;
        } else if (fromToBB == WHITE_OOO_MASK) {
            move.isCastle = WHITE_OOO_RIGHTS_MASK;
        } else if (fromToBB == BLACK_OO_MASK) {
            move.isCastle = BLACK_OO_RIGHTS_MASK;
        } else if (fromToBB == BLACK_OOO_MASK) {
            move.isCastle = BLACK_OOO_RIGHTS_MASK;
        }
    
    default:
        break;
    }
}