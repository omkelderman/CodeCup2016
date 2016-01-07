#include "HeuristicAlgorithm.h"

HeuristicAlgorithm::HeuristicAlgorithm() :
        Algorithm() {
}

const Coords HeuristicAlgorithm::calculateRedMove() const {
    return nextMove.coords;
}

const Coords HeuristicAlgorithm::calculateBlueMove() const {
    return nextMove.coords;
}

const Coords HeuristicAlgorithm::calculateGreyMove() const {
    return nextMove.coords;
}

SlideDirection HeuristicAlgorithm::calculateSlide() const {
    return nextMove.direction;
}

void HeuristicAlgorithm::ensureValidState() {
    Move validMoves[16];
    std::size_t validMoveCounter = gameBoardPtr->getValidMoves(validMoves);

    std::size_t theChosenMoveIndex = heuristicMonteCarloPolicy.getNextMove(*gameBoardPtr, validMoves, validMoveCounter);
    nextMove = validMoves[theChosenMoveIndex];
}
