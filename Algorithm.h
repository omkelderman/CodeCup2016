//

#ifndef CODECUP_ALGORITHM_H
#define CODECUP_ALGORITHM_H

#include "Board.h"

class Algorithm {

public:
    Algorithm();

    virtual const std::pair<coord, coord> calculateRedMove() = 0;
    virtual const std::pair<coord, coord> calculateBlueMove() = 0;
    virtual const std::pair<coord, coord> calculateGreyMove() = 0;
    virtual const SlideDirection calculateSlide() = 0;

    void setBoard(Board* boardPtr);

private:
    Board* board;
};


#endif //CODECUP_ALGORITHM_H
