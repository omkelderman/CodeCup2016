#ifndef CODECUP_HEURISTICALGORITHM_H
#define CODECUP_HEURISTICALGORITHM_H

#include "Algorithm.h"
#include "MonteCarloPolicies.h"

class HeuristicAlgorithm : public Algorithm {
public:
    HeuristicAlgorithm();

    virtual const Coords calculateRedMove() const;
    virtual const Coords calculateBlueMove() const;
    virtual const Coords calculateGreyMove() const;
    virtual SlideDirection calculateSlide() const;
    virtual void ensureValidState();
private:
    HeuristicMonteCarloPolicy heuristicMonteCarloPolicy;
    Move nextMove;
};


#endif //CODECUP_HEURISTICALGORITHM_H
