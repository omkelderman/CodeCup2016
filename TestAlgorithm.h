//

#ifndef CODECUP_TESTALGORITHM_H
#define CODECUP_TESTALGORITHM_H


#include "Algorithm.h"

class TestAlgorithm : public Algorithm {
public:
    TestAlgorithm();

    virtual const Coords calculateRedMove() const;
    virtual const Coords calculateBlueMove() const;
    virtual const Coords calculateGreyMove() const;
    virtual const SlideDirection calculateSlide() const;
    const Coords getFirstEmpty() const;
    bool slideUpIsValid() const;
    bool slideDownIsValid() const;
    bool slideLeftIsValid() const;
    bool slideRightIsValid() const;
};


#endif //CODECUP_TESTALGORITHM_H
