//

#include <stdexcept>
#include "MonteCarloAlgorithm.h"

MonteCarloAlgorithm::MonteCarloAlgorithm() :
        Algorithm() { }

const std::pair<coord, coord> MonteCarloAlgorithm::calculateRedMove() const {
    throw std::logic_error("Not implemented");
}

const std::pair<coord, coord> MonteCarloAlgorithm::calculateBlueMove() const {
    throw std::logic_error("Not implemented");
}

const std::pair<coord, coord> MonteCarloAlgorithm::calculateGreyMove() const {
    throw std::logic_error("Not implemented");
}

const SlideDirection MonteCarloAlgorithm::calculateSlide() const {
    throw std::logic_error("Not implemented");
}
