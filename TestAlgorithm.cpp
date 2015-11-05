//

#include <stdexcept>
#include <iostream>
#include "TestAlgorithm.h"

TestAlgorithm::TestAlgorithm() :
        Algorithm() { }

const std::pair<coord, coord> TestAlgorithm::calculateRedMove() const {
    const std::pair<coord, coord>& redMove = getFirstEmpty();
    std::cerr << "Red move: " << redMove.first << redMove.second << std::endl;
    return redMove;
}

const std::pair<coord, coord> TestAlgorithm::calculateBlueMove() const {
    const std::pair<coord, coord>& blueMove = getFirstEmpty();
    std::cerr << "Blue move: " << blueMove.first << blueMove.second << std::endl;
    return blueMove;
}

const std::pair<coord, coord> TestAlgorithm::calculateGreyMove() const {
    const std::pair<coord, coord>& greyMove = getFirstEmpty();
    std::cerr << "Grey move: " << greyMove.first << greyMove.second << std::endl;
    return greyMove;
}

const SlideDirection TestAlgorithm::calculateSlide() const {
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
        throw std::logic_error("No valid move possible");
    }
    std::cerr << "Slide direction: " << dir << std::endl;
    return dir;
}

bool TestAlgorithm::slideUpIsValid() const {
    for (coord x = 0; x < 4; ++x) {
        bool hasEmpty = false;
        for (coord y = 0; y < 4; ++y) {
            if (hasEmpty) {
                if (!board->getPiece(x, y).empty()) {
                    return true;
                }
            } else {
                if (board->getPiece(x, y).empty()) {
                    hasEmpty = true;
                }
            }
        }

        unsigned short lastValue = 0;
        for (coord y = 0; y < 4; ++y) {
            const Piece& p = board->getPiece(x, y);
            if (!p.empty() && p.value == lastValue) {
                return true;
            }
            lastValue = p.value;
        }
    }
    return false;
}

bool TestAlgorithm::slideDownIsValid() const {
    for (coord x = 0; x < 4; ++x) {
        bool hasEmpty = false;
        for (coord y = 3; y >= 0; --y) {
            if (hasEmpty) {
                if (!board->getPiece(x, y).empty()) {
                    return true;
                }
            } else {
                if (board->getPiece(x, y).empty()) {
                    hasEmpty = true;
                }
            }
        }

        unsigned short lastValue = 0;
        for (coord y = 3; y >= 0; --y) {
            const Piece& p = board->getPiece(x, y);
            if (!p.empty() && p.value == lastValue) {
                return true;
            }
            lastValue = p.value;
        }
    }
    return false;
}

bool TestAlgorithm::slideLeftIsValid() const {
    for (coord y = 0; y < 4; ++y) {
        bool hasEmpty = false;
        for (coord x = 0; x < 4; ++x) {
            if (hasEmpty) {
                if (!board->getPiece(x, y).empty()) {
                    return true;
                }
            } else {
                if (board->getPiece(x, y).empty()) {
                    hasEmpty = true;
                }
            }
        }

        unsigned short lastValue = 0;
        for (coord x = 0; x < 4; ++x) {
            const Piece& p = board->getPiece(x, y);
            if (!p.empty() && p.value == lastValue) {
                return true;
            }
            lastValue = p.value;
        }
    }
    return false;
}

bool TestAlgorithm::slideRightIsValid() const {
    for (coord y = 0; y < 4; ++y) {
        bool hasEmpty = false;
        for (coord x = 3; x >= 0; --x) {
            if (hasEmpty) {
                if (!board->getPiece(x, y).empty()) {
                    return true;
                }
            } else {
                if (board->getPiece(x, y).empty()) {
                    hasEmpty = true;
                }
            }
        }

        unsigned short lastValue = 0;
        for (coord x = 3; x >= 0; --x) {
            const Piece& p = board->getPiece(x, y);
            if (!p.empty() && p.value == lastValue) {
                return true;
            }
            lastValue = p.value;
        }
    }
    return false;
}

const std::pair<coord, coord> TestAlgorithm::getFirstEmpty() const {
    for (coord y = 0; y < 3; ++y) {
        for (coord x = 0; x < 3; ++x) {
            if (board->getPiece(x, y).empty()) {
                return std::make_pair(x, y);
            }
        }
    }
    throw std::logic_error("No valid move possible");
}
