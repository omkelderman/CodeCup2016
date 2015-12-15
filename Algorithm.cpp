#include "Algorithm.h"
#include "Game6561.h"

Algorithm::Algorithm() :
        gameBoardPtr(nullptr), gameMoveCounterPtr(nullptr) { }

void Algorithm::setGameBoardPtr(Board* gameBoardPtr) {
    Algorithm::gameBoardPtr = gameBoardPtr;
}

void Algorithm::setGameMoveCounterPtr(unsigned short* gameMoveCounterPtr) {
    Algorithm::gameMoveCounterPtr = gameMoveCounterPtr;
}
