#ifndef CODECUP_TESTALGORITHM_H
#define CODECUP_TESTALGORITHM_H


#include "Algorithm.h"

class TestAlgorithm : public Algorithm {
public:
    TestAlgorithm();

    virtual const Coords calculateRedMove() const;
    virtual const Coords calculateBlueMove() const;
    virtual const Coords calculateGreyMove() const;
    virtual SlideDirection calculateSlide() const;
    virtual void ensureValidState();

private:
    const Coords getFirstEmpty() const;
};


#endif //CODECUP_TESTALGORITHM_H
