#ifndef CODECUP_MOVE_H
#define CODECUP_MOVE_H

#include "Board.h"

union Move {
    Coords coords;
    SlideDirection direction;

    Move();
    Move(const Coords& coords);
    Move(coord row, coord column);
    Move(const SlideDirection& direction);
};


#endif //CODECUP_MOVE_H
