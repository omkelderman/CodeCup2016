#ifndef CODECUP_MONTECARLOALGORITHM_H
#define CODECUP_MONTECARLOALGORITHM_H


#include <forward_list>
#include "Algorithm.h"
#include "Move.h"
#include "Simulation.h"

class MonteCarloAlgorithm : public Algorithm {
public:
    MonteCarloAlgorithm();

    virtual const Coords calculateRedMove() const;
    virtual const Coords calculateBlueMove() const;
    virtual const Coords calculateGreyMove() const;
    virtual SlideDirection calculateSlide() const;

    void simulate(std::size_t movesToCalculate);

    //monte carlo stuff
private:
    std::forward_list<Simulation> simulations;
    size_t simulateGame();
};

#endif //CODECUP_MONTECARLOALGORITHM_H
