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

SlideDirection MonteCarloAlgorithm::calculateSlide() const {
    throw std::logic_error("Not implemented");
}

void MonteCarloAlgorithm::simulate(std::size_t movesToCalculate) {
    for (std::size_t i = 0; i < movesToCalculate; ) {
        i += simulateGame();
    }
}

size_t MonteCarloAlgorithm::simulateGame() {
    return 0;
}
