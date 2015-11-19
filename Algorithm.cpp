#include "Algorithm.h"
#include "Game6561.h"

Algorithm::Algorithm() :
        board(nullptr), gameState(nullptr) { }

void Algorithm::setBoard(Board* boardPtr) {
    board = boardPtr;
}

void Algorithm::setGameState(GameState* gameStatePtr) {
    gameState = gameStatePtr;
}
