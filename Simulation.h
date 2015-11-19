#ifndef CODECUP_SIMULATION_H
#define CODECUP_SIMULATION_H

#include "Board.h"
#include "Move.h"

class Simulation {
    friend class MonteCarloAlgorithm;
public:
    Simulation();

    void addMove(const SlideDirection& direction);
    void addMove(const Coords& coords);

    const SlideDirection& getFirstMoveAsSlideDirection();
    const Coords& getFirstMoveAsCoords();

    bool checkFirstTwoMoves(const SlideDirection& direction1, const SlideDirection& direction2);
    bool checkFirstTwoMoves(const SlideDirection& direction, const Coords& coords);
    bool checkFirstTwoMoves(const Coords& coords, const SlideDirection& direction);
    bool checkFirstTwoMoves(const Coords& coords1, const Coords& coords2);

    void removeFirstTwo();
    std::size_t getMovesCount();
private:
    Move moves[1000];
    std::uint32_t maxScore;

    Move* startPointer;
    Move* endPointer;
};


#endif //CODECUP_SIMULATION_H
