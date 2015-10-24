//

#ifndef CODECUP_ALGORITHM_H
#define CODECUP_ALGORITHM_H

#include "Board.h"

class Algorithm {

public:
    Algorithm();

    virtual const std::pair<coord, coord> calculateRedMove() const = 0;
    virtual const std::pair<coord, coord> calculateBlueMove() const = 0;
    virtual const std::pair<coord, coord> calculateGreyMove() const = 0;
    virtual const SlideDirection calculateSlide() const = 0;

    void setBoard(Board* boardPtr);

protected:
    Board* board;
};


#endif //CODECUP_ALGORITHM_H
