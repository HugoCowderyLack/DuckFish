#include "LookupTables.hpp"

Bitboard knightMoveTable[NUM_SQUARES];
Bitboard rayTable[NUM_SQUARES][NUM_DIR];

void initialiseAll() {
    initialiseKnightLookup();
    initialiseRayLookup();
}

void initialiseKnightLookup() {
    for (int i = 0; i < NUM_SQUARES; i++) {
        Bitboard bb = 0ULL;
        if (i % 8 >= 2 && i <= 55) {
            bb |= 1ULL << (i + 6);
        }
        if (i % 8 >= 1 && i <= 47) {
            bb |= 1ULL << (i + 15);
        }
        if (i % 8 <= 6 && i <= 47) {
            bb |= 1ULL << (i + 17);
        }
        if (i % 8 <= 5 && i <= 55) {
            bb |= 1ULL << (i + 10);
        }
        if (i % 8 <= 5 && i >= 8) {
            bb |=  1ULL << (i - 6);
        }
        if (i % 8 <= 6 && i >= 16) {
            bb |= 1ULL << (i - 15);
        }
        if (i % 8 >= 1 && i >= 16) {
            bb |= 1ULL << (i - 17);
        }
        if (i % 8 >= 2 && i >= 8) {
            bb |= 1ULL << (i - 10);
        }

        knightMoveTable[i] = bb;
    }
}

void initialiseRayLookup() {
    for (int sq = 0; sq < NUM_SQUARES; sq++) {
        for (int dir = 0; dir < NUM_DIR; dir++) {
            Bitboard bb = 0ULL;
            Bitboard piece = 1ULL << sq;
            if (piece & rayStoppers[dir]) {
                continue;
            }
            for (int i = 1; i < 8; i++) {
                bb |= dirVectors[dir] > 0 ? piece << (i * dirVectors[dir]) : piece >> (i * -dirVectors[dir]);
                if (bb & rayStoppers[dir]) {
                    break;
                }
            }
            rayTable[sq][dir] = bb;
        }
    }
}

Bitboard knightLookUp(Square sqaure) {
    return knightMoveTable[sqaure];
}
Bitboard rayLookUp(Square square, int dir) {
    return rayTable[square][dir];
}