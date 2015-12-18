#ifndef CODECUP_ALGORITHM_H
#define CODECUP_ALGORITHM_H

#include "Board.h"
#include "GameProgress.h"

class GameState;

class Algorithm {

public:
    Algorithm();

    virtual const Coords calculateRedMove() const = 0;
    virtual const Coords calculateBlueMove() const = 0;
    virtual const Coords calculateGreyMove() const = 0;
    virtual SlideDirection calculateSlide() const = 0;

    virtual void ensureValidState() = 0;

    void setGameBoardPtr(Board* gameBoardPtr);
    void setGameGameProgressPtr(GameProgress* gameGameProgressPtr);

protected:
    Board* gameBoardPtr;
    GameProgress* gameGameProgressPtr;
};


#endif //CODECUP_ALGORITHM_H
