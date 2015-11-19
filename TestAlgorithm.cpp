#include <stdexcept>
#include <iostream>
#include "TestAlgorithm.h"
#include "GameException.h"

TestAlgorithm::TestAlgorithm() :
        Algorithm() { }

const Coords TestAlgorithm::calculateRedMove() const {
    const Coords& redMove = getFirstEmpty();
    std::cerr << "Red move: " << redMove << std::endl;
    return redMove;
}

const Coords TestAlgorithm::calculateBlueMove() const {
    const Coords& blueMove = getFirstEmpty();
    std::cerr << "Blue move: " << blueMove << std::endl;
    return blueMove;
}

const Coords TestAlgorithm::calculateGreyMove() const {
    const Coords& greyMove = getFirstEmpty();
    std::cerr << "Grey move: " << greyMove << std::endl;
    return greyMove;
}

SlideDirection TestAlgorithm::calculateSlide() const {
    for(SlideDirection dir : {UP, DOWN, LEFT, RIGHT}) {
        if(board->isSlideValid(dir)) {
            std::cerr << "Slide direction: " << dir << std::endl;
            return dir;
        }
    }
    throw GameException("No valid slide possible");
}

const Coords TestAlgorithm::getFirstEmpty() const {
    for (coord row = 0; row < 4; ++row) {
        for (coord column = 0; column < 4; ++column) {
            if (board->getPiece(row, column).empty()) {
                return Coords(row, column);
            }
        }
    }
    throw GameException("No first empty found");
}
