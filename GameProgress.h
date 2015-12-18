#ifndef CODECUP_GAMEPROGRESS_H
#define CODECUP_GAMEPROGRESS_H

#include "Move.h"

class GameProgress {
    friend class Game6561;

public:
    GameProgress();

    unsigned short getMoveCounter();
    Coords getLastDoneMoveAsCoords() const;
    SlideDirection getLastDoneMoveAsSlideDirection() const;
    Coords getLastReadMoveAsCoords() const;
    SlideDirection getLastReadMoveAsSlideDirection() const;

private:
    unsigned short moveCounter;
    Move lastDoneMove;
    Move lastReadMove;

    void updateLastDoneMoveAndMoveCounter(const Move& move);
    void updateLastReadMoveAndMoveCounter(const Move& move);
};


#endif //CODECUP_GAMEPROGRESS_H
