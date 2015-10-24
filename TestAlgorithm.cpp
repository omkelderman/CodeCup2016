//

#include <stdexcept>
#include "TestAlgorithm.h"

TestAlgorithm::TestAlgorithm() :
        Algorithm() { }

const std::pair<coord, coord> TestAlgorithm::calculateRedMove() const {
    return getFirstEmpty();
}

const std::pair<coord, coord> TestAlgorithm::calculateBlueMove() const {
    return getFirstEmpty();
}

const std::pair<coord, coord> TestAlgorithm::calculateGreyMove() const {
    return getFirstEmpty();
}

const SlideDirection TestAlgorithm::calculateSlide() const {
    if (slideUpIsValid()) {
        return UP;
    }
    if (slideDownIsValid()) {
        return DOWN;
    }
    if (slideLeftIsValid()) {
        return LEFT;
    }
    if (slideRightIsValid()) {
        return RIGHT;
    }
    throw std::logic_error("No valid move possible");
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
