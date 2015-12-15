#ifndef CODECUP_MOVE_H
#define CODECUP_MOVE_H

#include <iostream>

typedef unsigned char coord;

struct Coords {
    coord row;
    coord column;

    Coords(coord row, coord column);

    bool operator==(const Coords& coords);
};

enum SlideDirection {
    SD_UP, SD_DOWN, SD_LEFT, SD_RIGHT
};

std::ostream& operator<<(std::ostream& ostream, const Coords& coords);
std::ostream& operator<<(std::ostream& ostream, const SlideDirection& direction);
std::istream& operator>>(std::istream& istream, SlideDirection& direction);

union Move {
    Coords coords;
    SlideDirection direction;

    Move();
    Move(const Coords& coords);
    Move(coord row, coord column);
    Move(const SlideDirection& direction);
};


#endif //CODECUP_MOVE_H
