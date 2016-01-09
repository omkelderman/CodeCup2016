#ifndef CODECUP_SIMULATION_H
#define CODECUP_SIMULATION_H

#include "Board.h"
#include "Move.h"

#include <deque>

class Simulation {
    friend class MonteCarloAlgorithm;
public:
    Simulation();
    Simulation(const Simulation& otherSimulation);

    Simulation& operator=(const Simulation& otherSimulation);

    void addMove(const SlideDirection& direction);
    void addMove(const Coords& coords);

    bool operator<(const Simulation& otherSimulation);

    const SlideDirection& getFirstMoveAsSlideDirection();
    const Coords& getFirstMoveAsCoords();

    bool checkFirstTwoMoves(const SlideDirection& direction1, const SlideDirection& direction2) const;
    bool checkFirstTwoMoves(const SlideDirection& direction, const Coords& coords) const;
    bool checkFirstTwoMoves(const Coords& coords, const SlideDirection& direction) const;
    bool checkFirstTwoMoves(const Coords& coords1, const Coords& coords2) const;

    void removeFirstTwo();
    std::size_t getMovesCount() const;
private:
    std::deque<Move> moves;
    std::uint32_t maxScore;
};


#endif //CODECUP_SIMULATION_H
