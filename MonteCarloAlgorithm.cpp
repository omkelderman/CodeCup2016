#include <stdexcept>
#include <algorithm>
#include "MonteCarloAlgorithm.h"

MonteCarloAlgorithm::MonteCarloAlgorithm() :
        Algorithm(), randomSlideDistribution(0, 3), randomCoordsDistribution(0, 15) {
    // seed the random generator with a (hopefully) non-deterministic random number
    std::random_device rd;
    randomGenerator.seed(rd());
}

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
    while (movesToCalculate > 0) {
        movesToCalculate -= simulateGame(movesToCalculate);
    }
}

SlideDirection MonteCarloAlgorithm::generatorRandomSlide() {
    return static_cast<SlideDirection>(randomSlideDistribution(randomGenerator));
}

Coords MonteCarloAlgorithm::generatorRandomCoords() {
    // generate random number between 0 and 15
    unsigned short rnd = randomCoordsDistribution(randomGenerator);
    // take two bits of the number as row, the other two bits as column
    return Coords(static_cast<coord>(rnd & 0x3), static_cast<coord>(rnd >> 2));
}

std::size_t MonteCarloAlgorithm::simulateGame(std::size_t maxMovesInSimulation) {
    // A copy for the local board is needed, as it'll be used as a reference in the random functions below.
    // now we only use the local(Board/GameState) variables after this, as we don't want to change the 6561Game board.
    Board localBoard(*board);
    GameState localGameState(*gameState);

    Simulation simulation;
    bool simulationValid = true;
    std::size_t gameMaxMoves = Game6561::MAX_MOVES;
    std::size_t maxMoves = std::min(maxMovesInSimulation, gameMaxMoves);
    while (simulationValid && localGameState.getMoveCounter() < maxMoves) {
        switch (localGameState.getGameRhythmState()) {
            case GR_BLUE:
                simulationValid = addRandomCoordsToSimulation(simulation, localBoard, BLUE);
                break;
            case GR_RED:
                simulationValid = addRandomCoordsToSimulation(simulation, localBoard, RED);
                break;
            case GR_GREY:
                simulationValid = addRandomCoordsToSimulation(simulation, localBoard, GREY);
                break;
            case GR_SLIDE1:
            case GR_SLIDE2:
                simulationValid = addRandomSlideToSimulation(simulation, localBoard);
                break;
        }

        ++localGameState;
    }

    if(simulation.getMovesCount() > 0) {
        simulations.push_front(simulation);
    }
    return simulation.getMovesCount();
}

bool MonteCarloAlgorithm::addRandomSlideToSimulation(Simulation& simulation, Board& board) {
    // TODO try random slides till valid
    return false;
}

bool MonteCarloAlgorithm::addRandomCoordsToSimulation(Simulation& simulation, Board& board, PieceColor color) {
    // TODO try random placements till valid
    return false;
}
