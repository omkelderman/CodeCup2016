#ifndef CODECUP_ADJACENTPIECEINFO_H
#define CODECUP_ADJACENTPIECEINFO_H

#include "Move.h"

struct PieceInfo {
    Coords coords;
    unsigned short value;
    Coords emptyAdjacentPlaces[4];
    std::size_t emptyAdjacentPlacesCount;
};


#endif //CODECUP_ADJACENTPIECEINFO_H
