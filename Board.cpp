#include "Board.hpp"
#include <iostream>
#include <cctype>
#include <string>
#include <windows.h>

Board::Board() : 
    whiteToMove(true),
    castlingRights(0x0F),
    enPassantTarget(0),
    numHalfMoves(0) 
    {
        PieceBBs[PAWN] = 0x00FF00000000FF00ULL;
        PieceBBs[ROOK] = 0x8100000000000081ULL;
        PieceBBs[KNIGHT] = 0x4200000000000042ULL;
        PieceBBs[BISHOP] = 0x2400000000000024ULL;
        PieceBBs[QUEEN] = 0x0800000000000008ULL;
        PieceBBs[KING] = 0x1000000000000010ULL;  
        ColourBBs[WHITE] = 0x000000000000FFFFULL;
        ColourBBs[BLACK] = 0xFFFF000000000000ULL;
        OccupiedBB = 0xFFFF00000000FFFFULL;
    };

Bitboard Board::getPieceBB(Piece piece) {
    return PieceBBs[piece];
}

Bitboard Board::getColourBB(Colour colour) {
    return ColourBBs[colour];
}

Bitboard Board::getOccupiedBB() {
    return OccupiedBB;
}

bool Board::isWhiteToMove() {
    return whiteToMove;
}

Bitboard Board::getEnPassantSquare(Colour colour) {
    if (enPassantTarget) {
        return enPassantTarget << ((colour == WHITE ? 5 : 2) * 8);
    }
    return 0;
}

uint8_t Board::getCastlingRights() {
    return castlingRights;
}

// Board::Board(FEN fen) {
//     int rank = 7;
//     int file = 0;
//     char c = fen[0];
//     for (int i = 0; c != NULL; i++) {
//         Bitboard currBit = 1ULL << (rank * 8 + file);
//         switch
//     }
//         BBs[PAWN] = 0x00FF00000000FF00ULL;
//         BBs[ROOK] = 0x8100000000000081ULL;
//         BBs[KNIGHT] = 0x4200000000000042ULL;
//         BBs[BISHOP] = 0x2400000000000024ULL;
//         BBs[QUEEN] = 0x0800000000000008ULL;
//         BBs[KING] = 0x1000000000000010ULL;
//         BBs[WHITE] = 0x000000000000FFFFULL;
//         BBs[BLACK] = 0xFFFF000000000000ULL;
//     };

bool Board::makeMove(Move move) {
    if (!(whiteToMove == (move.colour == WHITE))) {
        return false;
    }
    Bitboard fromBB = move.fromToBB & ColourBBs[move.colour];
    Bitboard toBB = move.fromToBB & ColourBBs[move.colour == WHITE ? BLACK : WHITE];

    PieceBBs[move.piece] ^= move.fromToBB;
    ColourBBs[move.colour] ^= move.fromToBB;
    
    if (move.cPiece != NONE) { // update bitboards
        PieceBBs[move.cPiece] ^= toBB;
        ColourBBs[(move.colour == WHITE) ? BLACK : WHITE] ^= toBB;
        OccupiedBB ^= fromBB;
    } else {
        OccupiedBB ^= move.fromToBB;
    }
    whiteToMove = !whiteToMove;

    if (move.cPiece != NONE || move.piece == PAWN) { // update/reset half-move counter for 50 move rule
        numHalfMoves++;
    } else {
        numHalfMoves = 1;
    }
    // check if move touches e1
    // check if move touches e8
    // check if move touches a1
    // a8
    //h1
    //h8
    
    return true;
}

void Board::printBoard() const {
    char pieceSignatures[6] = {'P', 'R', 'N', 'B', 'Q', 'K'};
    for (int rank = 7; rank >= 0; --rank) {  // Iterate over ranks (rows) from 8 to 1
        for (int file = 0; file < 8; ++file) {  // Iterate over files (columns) from a to h
            int square = rank * 8 + file;  // Calculate the square index
            uint64_t mask = 1ULL << square;  // Create a mask for the current square
            
            // Check if the bit at the current square is set (piece present)
            if (OccupiedBB & mask) {
                for (int i = 0; i < 6; i++) {
                    if (PieceBBs[i] & mask) {
                        std::cout << "\033[" << ((ColourBBs[WHITE] & mask) ? 96 : 31) << "m" << pieceSignatures[i] << "\033[" << 0 << "m" << " ";
                    }
                    continue;
                }
            } else {
                std::cout << ". ";  // Print '. ' if the bit is not set
            }
        }
        std::cout << "\n";  // Newline after each rank
    }
    std::cout << "\n";  // Extra newline for spacing
}

void printBitBoard(Bitboard bitboard) {
    for (int rank = 7; rank >= 0; --rank) {  // Iterate over ranks (rows) from 8 to 1
        for (int file = 0; file < 8; ++file) {  // Iterate over files (columns) from a to h
            int square = rank * 8 + file;  // Calculate the square index
            uint64_t mask = 1ULL << square;  // Create a mask for the current square
            
            // Check if the bit at the current square is set (piece present)
            if (bitboard & mask) {
                std::cout << "1 ";
            } else {
                std::cout << "0 ";  // Print '0' if the bit is not set
            }
        }
        std::cout << std::endl;  // Newline after each rank
    }
    std::cout << std::endl;  // Extra newline for spacing
}