#ifndef CODECUP_MONTECARLOTREESEARCHALGORITHM_H
#define CODECUP_MONTECARLOTREESEARCHALGORITHM_H

#include "Algorithm.h"
#include "MonteCarloPolicies.h"
#include <map>

struct Statistic {
    std::uint32_t score;
    std::uint16_t playCount;
};

typedef std::map<Board, Statistic> Statistics;

class MonteCarloTreeSearchAlgorithm : public Algorithm {
public:
    MonteCarloTreeSearchAlgorithm(std::size_t movesToSimulate, double ucb1Constant, std::size_t maxLocalMovesToSimulate, MonteCarloPolicy& policy);

    virtual const Coords calculateRedMove() const;
    virtual const Coords calculateBlueMove() const;
    virtual const Coords calculateGreyMove() const;
    virtual SlideDirection calculateSlide() const;

    virtual void ensureValidState();
private:
    // constants
    const std::size_t movesToSimulate;
    const double ucb1Constant;
    const std::size_t maxLocalMovesToSimulate;

    MonteCarloPolicy& policy;
    RandomMonteCarloPolicy randomPolicy;

    Move nextMove;
    Statistics statistics;

    void runSimulations(std::size_t movesToSimulate);
    std::size_t simulateGame(const std::size_t movesToSimulate);
};


#endif //CODECUP_MONTECARLOTREESEARCHALGORITHM_H
