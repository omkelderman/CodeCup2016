//

#ifndef CODECUP_MONTECARLOALGORITHM_H
#define CODECUP_MONTECARLOALGORITHM_H


#include "Algorithm.h"

class MonteCarloAlgorithm : public Algorithm {
public:
    MonteCarloAlgorithm();

    virtual const std::pair<coord, coord> calculateRedMove() const;
    virtual const std::pair<coord, coord> calculateBlueMove() const;
    virtual const std::pair<coord, coord> calculateGreyMove() const;
    virtual const SlideDirection calculateSlide() const;
};


#endif //CODECUP_MONTECARLOALGORITHM_H
