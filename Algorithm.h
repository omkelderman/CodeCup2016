#ifndef CODECUP_ALGORITHM_H
#define CODECUP_ALGORITHM_H

#include "Board.h"

class GameState;

class Algorithm {

public:
    Algorithm();

    virtual const Coords calculateRedMove() const = 0;
    virtual const Coords calculateBlueMove() const = 0;
    virtual const Coords calculateGreyMove() const = 0;
    virtual SlideDirection calculateSlide() const = 0;

    void setBoard(Board* boardPtr);
    void setGameState(GameState* gameStatePtr);

protected:
    Board* board;
    GameState* gameState;
};


#endif //CODECUP_ALGORITHM_H
