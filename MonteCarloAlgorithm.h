//

#ifndef CODECUP_MONTECARLOALGORITHM_H
#define CODECUP_MONTECARLOALGORITHM_H


#include "Algorithm.h"

class MonteCarloAlgorithm : public Algorithm {
public:
    MonteCarloAlgorithm();

    virtual const std::pair<coord, coord> calculateRedMove();
    virtual const std::pair<coord, coord> calculateBlueMove();
    virtual const std::pair<coord, coord> calculateGreyMove();
    virtual const SlideDirection calculateSlide();
};


#endif //CODECUP_MONTECARLOALGORITHM_H
