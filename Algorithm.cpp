#include "Algorithm.h"

Algorithm::Algorithm() :
        gameBoardPtr(nullptr), gameGameProgressPtr(nullptr) { }

void Algorithm::setGameBoardPtr(Board* gameBoardPtr) {
    Algorithm::gameBoardPtr = gameBoardPtr;
}

void Algorithm::setGameGameProgressPtr(GameProgress* gameGameProgressPtr) {
    Algorithm::gameGameProgressPtr = gameGameProgressPtr;
}
