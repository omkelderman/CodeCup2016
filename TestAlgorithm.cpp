//

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
    SlideDirection dir;
    if (slideUpIsValid()) {
        dir = UP;
    } else if (slideDownIsValid()) {
        dir = DOWN;
    } else if (slideLeftIsValid()) {
        dir = LEFT;
    } else if (slideRightIsValid()) {
        dir = RIGHT;
    } else {
        throw GameException("No valid slide possible");
    }
    std::cerr << "Slide direction: " << dir << std::endl;
    return dir;
}

bool TestAlgorithm::slideUpIsValid() const {
    for (coord column = 0; column < 4; ++column) {
        bool hasEmpty = false;
        for (coord row = 0; row < 4; ++row) {
            if (hasEmpty) {
                if (!board->getPiece(row, column).empty()) {
                    return true;
                }
            } else {
                if (board->getPiece(row, column).empty()) {
                    hasEmpty = true;
                }
            }
        }

        unsigned short lastValue = 0;
        for (coord row = 0; row < 4; ++row) {
            const Piece& p = board->getPiece(row, column);
            if (!p.empty() && p.value == lastValue) {
                return true;
            }
            lastValue = p.value;
        }
    }
    return false;
}

bool TestAlgorithm::slideDownIsValid() const {
    for (coord column = 0; column < 4; ++column) {
        bool hasEmpty = false;
        for (coord row = 4; row-- > 0; ) {
            if (hasEmpty) {
                if (!board->getPiece(row, column).empty()) {
                    return true;
                }
            } else {
                if (board->getPiece(row, column).empty()) {
                    hasEmpty = true;
                }
            }
        }

        unsigned short lastValue = 0;
        for (coord row = 4; row-- > 0; ) {
            const Piece& p = board->getPiece(row, column);
            if (!p.empty() && p.value == lastValue) {
                return true;
            }
            lastValue = p.value;
        }
    }
    return false;
}

bool TestAlgorithm::slideLeftIsValid() const {
    for (coord row = 0; row < 4; ++row) {
        bool hasEmpty = false;
        for (coord column = 0; column < 4; ++column) {
            if (hasEmpty) {
                if (!board->getPiece(row, column).empty()) {
                    return true;
                }
            } else {
                if (board->getPiece(row, column).empty()) {
                    hasEmpty = true;
                }
            }
        }

        unsigned short lastValue = 0;
        for (coord column = 0; column < 4; ++column) {
            const Piece& p = board->getPiece(row, column);
            if (!p.empty() && p.value == lastValue) {
                return true;
            }
            lastValue = p.value;
        }
    }
    return false;
}

bool TestAlgorithm::slideRightIsValid() const {
    for (coord row = 0; row < 4; ++row) {
        bool hasEmpty = false;
        for (coord column = 4; column-- > 0;) {
            if (hasEmpty) {
                if (!board->getPiece(row, column).empty()) {
                    return true;
                }
            } else {
                if (board->getPiece(row, column).empty()) {
                    hasEmpty = true;
                }
            }
        }

        unsigned short lastValue = 0;
        for (coord column = 4; column-- > 0; ) {
            const Piece& p = board->getPiece(row, column);
            if (!p.empty() && p.value == lastValue) {
                return true;
            }
            lastValue = p.value;
        }
    }
    return false;
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
