#include <stdexcept>
#include <algorithm>
#include "MonteCarloAlgorithm.h"

// constants
const int MonteCarloAlgorithm::SIMULATIONS_THRESHOLD = 10;
const std::size_t MonteCarloAlgorithm::MOVES_TO_SIMULATE = 100000;

MonteCarloAlgorithm::MonteCarloAlgorithm() :
        Algorithm(), bestSimulation(nullptr) {
    // seed the random generator with a (hopefully) non-deterministic random number
#ifdef DEBUG_BUILD
    randomGenerator.seed(69);
#else
    std::random_device rd;
    randomGenerator.seed(rd());
#endif
}

const Coords MonteCarloAlgorithm::calculateRedMove() const {
    return bestSimulation->getFirstMoveAsCoords();
}

const Coords MonteCarloAlgorithm::calculateBlueMove() const {
    return bestSimulation->getFirstMoveAsCoords();
}

const Coords MonteCarloAlgorithm::calculateGreyMove() const {
    return bestSimulation->getFirstMoveAsCoords();
}

SlideDirection MonteCarloAlgorithm::calculateSlide() const {
    return bestSimulation->getFirstMoveAsSlideDirection();
}

void MonteCarloAlgorithm::ensureValidState() {
    if (gameState->getMoveCounter() >= 2) {
        // remove simulation where the first two moves do not equal the last done moves
        simulations.remove_if([this](const Simulation& simulation) {
            if (simulation.getMovesCount() <= 2) {
                return true;
            }
            switch (gameState->getGameRhythmState()) {
                case GR_BLUE:
                    return !simulation.checkFirstTwoMoves(gameState->getLastDoneMoveAsSlideDirection(),
                                                          gameState->getLastReadMoveAsSlideDirection());
                case GR_RED:
                    return !simulation.checkFirstTwoMoves(gameState->getLastDoneMoveAsSlideDirection(),
                                                          gameState->getLastReadMoveAsCoords());
                case GR_GREY:
                case GR_SLIDE1:
                    return !simulation.checkFirstTwoMoves(gameState->getLastDoneMoveAsCoords(),
                                                          gameState->getLastReadMoveAsCoords());
                case GR_SLIDE2:
                    return !simulation.checkFirstTwoMoves(gameState->getLastDoneMoveAsCoords(),
                                                          gameState->getLastReadMoveAsSlideDirection());
                default:
                    return false;
            }
        });

        // remove the first two moves of the remaining simulations since those two have just been executed
        for (Simulation& simulation : simulations) {
            simulation.removeFirstTwo();
        }

        // we updated simulations, bestSimulation should update as well
        updateBestSimulation();
    }
    if (shouldSimulateMore()) {
        simulate(MOVES_TO_SIMULATE);
    }
}

void MonteCarloAlgorithm::updateBestSimulation() {
    if(distance(simulations.begin(), simulations.end()) == 0) {
            bestSimulation = nullptr;
        } else {
        bestSimulation = &(*max_element(simulations.begin(), simulations.end()));
    }
}

bool MonteCarloAlgorithm::shouldSimulateMore() const {
    return distance(simulations.begin(), simulations.end()) < SIMULATIONS_THRESHOLD;
}

void MonteCarloAlgorithm::simulate(std::size_t movesToCalculate) {
    while (movesToCalculate > 0) {
        movesToCalculate -= simulateGame(movesToCalculate);
    }
    updateBestSimulation();
}

std::size_t MonteCarloAlgorithm::simulateGame(std::size_t maxMovesInSimulation) {
    // A copy for the local board is needed, as it'll be used as a reference in the random functions below.
    // now we only use the local(Board/GameState) variables after this, as we don't want to change the 6561Game board.
    Board localBoard(*board);
    GameState localGameState(*gameState);

    Simulation simulation;
    bool simulationValid = true;
    std::size_t gameMaxMoves = Game6561::MAX_MOVES;
    std::size_t maxMoveCounter = std::min(maxMovesInSimulation + localGameState.getMoveCounter(), gameMaxMoves);
    while (simulationValid && localGameState.getMoveCounter() < maxMoveCounter) {
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

        simulation.maxScore = std::max(simulation.maxScore, localBoard.getBoardScore());
        ++localGameState;
    }

    if (simulation.getMovesCount() > 0) {
        simulations.push_front(simulation);
    }
    return simulation.getMovesCount();
}

unsigned short MonteCarloAlgorithm::generateRandomNumber(unsigned short max,
                                                         unsigned short exclusionList[] /*= nullptr*/,
                                                         unsigned short exclusionListLength /*= 0*/) {
    unsigned short localMax = max - exclusionListLength;
    std::uniform_int_distribution<unsigned short> dis(0, localMax);
    unsigned short rnd = dis(randomGenerator);
    for (unsigned short i = 0; i < exclusionListLength; ++i) {
        if (rnd >= exclusionList[i]) {
            rnd++;
        }
    }
    return rnd;
}

bool MonteCarloAlgorithm::addRandomSlideToSimulation(Simulation& simulation, Board& board) {
    unsigned short invalidSlides[4];
    unsigned short invalidSlidesLength = 0;
    while (invalidSlidesLength < 4) {
        unsigned short slideNr = generateRandomNumber(3, invalidSlides, invalidSlidesLength);
        SlideDirection slideDirection = static_cast<SlideDirection>(slideNr);
        if (board.isSlideValid(slideDirection)) {
            board.slide(slideDirection);
            simulation.addMove(slideDirection);
            return true;
        }
        invalidSlides[invalidSlidesLength] = slideNr;
        ++invalidSlidesLength;
        std::sort(invalidSlides, invalidSlides + invalidSlidesLength);
    }
    return false;
}

bool MonteCarloAlgorithm::addRandomCoordsToSimulation(Simulation& simulation, Board& board, PieceColor color) {
    unsigned short nonEmptyCoords[16];
    unsigned short nonEmptyCoordsLength = getNonEmptyCoords(nonEmptyCoords, board);

    if (nonEmptyCoordsLength == 16) {
        return false;
    }
    int rnd = generateRandomNumber(15, nonEmptyCoords, nonEmptyCoordsLength);
    Coords coords(static_cast<coord>(rnd & 0x3), static_cast<coord>(rnd >> 2));
    simulation.addMove(coords);
    board.setPiece(coords.row, coords.column, color);
    return true;
}

unsigned short MonteCarloAlgorithm::getNonEmptyCoords(unsigned short nonEmptyCoords[], const Board& board) {
    unsigned short nonEmptyCoordsLength = 0;
    for (coord column = 0; column < 4; ++column) {
        for (coord row = 0; row < 4; ++row) {
            if (!board.getPiece(row, column).empty()) {
                nonEmptyCoords[nonEmptyCoordsLength] = coordsToUShort(row, column);
                ++nonEmptyCoordsLength;
            }
        }
    }
    return nonEmptyCoordsLength;
}

unsigned short MonteCarloAlgorithm::coordsToUShort(coord row, coord column) {
    return row + (column << 2);
}
