//

#include <stdexcept>
#include "MonteCarloAlgorithm.h"

MonteCarloAlgorithm::MonteCarloAlgorithm() :
        Algorithm() { }

const Coords MonteCarloAlgorithm::calculateRedMove() const {
    throw std::logic_error("Not implemented");
}

const Coords MonteCarloAlgorithm::calculateBlueMove() const {
    throw std::logic_error("Not implemented");
}

const Coords MonteCarloAlgorithm::calculateGreyMove() const {
    throw std::logic_error("Not implemented");
}

const SlideDirection MonteCarloAlgorithm::calculateSlide() const {
    throw std::logic_error("Not implemented");
}
