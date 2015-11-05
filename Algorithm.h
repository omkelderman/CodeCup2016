//

#ifndef CODECUP_ALGORITHM_H
#define CODECUP_ALGORITHM_H

#include "Board.h"

class Algorithm {

public:
    Algorithm();

    virtual const Coords calculateRedMove() const = 0;
    virtual const Coords calculateBlueMove() const = 0;
    virtual const Coords calculateGreyMove() const = 0;
    virtual const SlideDirection calculateSlide() const = 0;

    void setBoard(Board* boardPtr);

protected:
    Board* board;
};


#endif //CODECUP_ALGORITHM_H
