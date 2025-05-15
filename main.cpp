#include "Board.hpp"
#include "LookupTables.hpp"
#include "MoveGeneration.hpp"
#include <iostream>
#include <list>

int main() {
    initialiseAll();
    Board board;
    // Bitboard fromToBB = 1ULL | (1ULL << 24);
    // board.makeMove({WHITE, ROOK, fromToBB, NONE});
    // board.printBitBoard(getQueenMoves(board, 28, WHITE));
    
    std::list<Move> moveList = getAllMoves(board, board.isWhiteToMove() ? WHITE : BLACK);
    board.makeMove(moveList.back());

    moveList = getAllMoves(board, board.isWhiteToMove() ? WHITE : BLACK);
    board.makeMove(moveList.back());

    moveList = getAllMoves(board, board.isWhiteToMove() ? WHITE : BLACK);
    board.makeMove(moveList.back());

    moveList = getAllMoves(board, board.isWhiteToMove() ? WHITE : BLACK);
    board.makeMove(moveList.back());

    moveList = getAllMoves(board, board.isWhiteToMove() ? WHITE : BLACK);
    board.makeMove(moveList.back());

    moveList = getAllMoves(board, board.isWhiteToMove() ? WHITE : BLACK);
    board.makeMove(moveList.back());

    moveList = getAllMoves(board, board.isWhiteToMove() ? WHITE : BLACK);
    board.makeMove(moveList.back());

    board.printBoard();

    return 0;
}
