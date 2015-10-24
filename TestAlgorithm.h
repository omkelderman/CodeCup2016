//

#ifndef CODECUP_TESTALGORITHM_H
#define CODECUP_TESTALGORITHM_H


#include "Algorithm.h"

class TestAlgorithm : public Algorithm {
public:
    TestAlgorithm();

    virtual const std::pair<coord, coord> calculateRedMove() const;
    virtual const std::pair<coord, coord> calculateBlueMove() const;
    virtual const std::pair<coord, coord> calculateGreyMove() const;
    virtual const SlideDirection calculateSlide() const;
    const std::pair<coord, coord> getFirstEmpty() const;
    bool slideUpIsValid() const;
    bool slideDownIsValid() const;
    bool slideLeftIsValid() const;
    bool slideRightIsValid() const;
};


#endif //CODECUP_TESTALGORITHM_H
