#ifndef CODECUP_MONTECARLOALGORITHM_H
#define CODECUP_MONTECARLOALGORITHM_H


#include "Algorithm.h"

class MonteCarloAlgorithm : public Algorithm {
public:
    MonteCarloAlgorithm();

    virtual const Coords calculateRedMove() const;
    virtual const Coords calculateBlueMove() const;
    virtual const Coords calculateGreyMove() const;
    virtual SlideDirection calculateSlide() const;
};


#endif //CODECUP_MONTECARLOALGORITHM_H
