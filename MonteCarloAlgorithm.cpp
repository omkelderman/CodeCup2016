#include <stdexcept>
#include <algorithm>
#include "MonteCarloAlgorithm.h"

MonteCarloAlgorithm::MonteCarloAlgorithm() :
        Algorithm() {
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
    for(unsigned short i = 0; i < exclusionListLength; ++i) {
        if(rnd >= exclusionList[i]) {
            rnd++;
        }
    }
    return rnd;
}

bool MonteCarloAlgorithm::addRandomSlideToSimulation(Simulation& simulation, Board& board) {
    unsigned short invalidSlides[4];
    unsigned short invalidSlidesLength = 0;
    while (invalidSlidesLength < 4){
        unsigned short slideNr = generateRandomNumber(3, invalidSlides, invalidSlidesLength);
        SlideDirection slideDirection = static_cast<SlideDirection>(slideNr);
        if(board.isSlideValid(slideDirection)) {
            board.slide(slideDirection);
            simulation.addMove(slideDirection);
            return true;
        }
        invalidSlides[invalidSlidesLength] = slideNr;
        ++invalidSlidesLength;
    }
    return false;
}

bool MonteCarloAlgorithm::addRandomCoordsToSimulation(Simulation& simulation, Board& board, PieceColor color) {
    unsigned short nonEmptyCoords[16];
    unsigned short nonEmptyCoordsLength = getNonEmptyCoords(nonEmptyCoords, board);

    if(nonEmptyCoordsLength == 16) {
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
    for (coord row = 0; row < 3; ++row) {
        for (coord column = 0; column < 3; ++column) {
            if(!board.getPiece(row, column).empty()) {
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
