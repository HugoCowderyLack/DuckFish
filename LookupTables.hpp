#ifndef LOOKUP_TABLES_H
#define LOOKUP_TABLES_H

#include <array>

#include "Types.hpp"

extern Bitboard knightMoveTable[NUM_SQUARES];
extern Bitboard rayTable[NUM_SQUARES][NUM_DIR];

void initialiseKnightLookup();
void initialiseRayLookup();
void initialiseAll();

Bitboard knightLookUp(Square sqaure);
Bitboard rayLookUp(Square square, int dir);

#endif