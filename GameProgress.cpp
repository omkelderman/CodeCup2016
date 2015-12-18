#include "GameProgress.h"

GameProgress::GameProgress() :
        moveCounter(0) {
}

unsigned short GameProgress::getMoveCounter() {
    return moveCounter;
}

Coords GameProgress::getLastDoneMoveAsCoords() const {
    return lastDoneMove.coords;
}

SlideDirection GameProgress::getLastDoneMoveAsSlideDirection() const {
    return lastDoneMove.direction;
}

Coords GameProgress::getLastReadMoveAsCoords() const {
    return lastReadMove.coords;
}

SlideDirection GameProgress::getLastReadMoveAsSlideDirection() const {
    return lastReadMove.direction;
}

void GameProgress::updateLastDoneMoveAndMoveCounter(const Move& move) {
    lastDoneMove = move;
    ++moveCounter;
}

void GameProgress::updateLastReadMoveAndMoveCounter(const Move& move) {
    lastReadMove = move;
    ++moveCounter;
}
