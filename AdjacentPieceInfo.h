#ifndef CODECUP_ADJACENTPIECEINFO_H
#define CODECUP_ADJACENTPIECEINFO_H

#include "Move.h"

struct AdjacentPieceInfo {
    Coords adjacentPieceCoords;
    unsigned short adjacentPieceValue;
    Coords emptyAdjacentPlacesOfAdjacentPiece[3];
    std::size_t emptyAdjacentPlacesOfAdjacentPieceSize;
};


#endif //CODECUP_ADJACENTPIECEINFO_H
