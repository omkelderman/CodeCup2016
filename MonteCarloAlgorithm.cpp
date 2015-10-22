//

#include "MonteCarloAlgorithm.h"

MonteCarloAlgorithm::MonteCarloAlgorithm() :
        Algorithm() { }

const std::pair<coord, coord> MonteCarloAlgorithm::calculateRedMove() {
    return std::pair<coord, coord>();
}

const std::pair<coord, coord> MonteCarloAlgorithm::calculateBlueMove() {
    return std::pair<coord, coord>();
}

const std::pair<coord, coord> MonteCarloAlgorithm::calculateGreyMove() {
    return std::pair<coord, coord>();
}

const SlideDirection MonteCarloAlgorithm::calculateSlide() {
    return UP;
}
