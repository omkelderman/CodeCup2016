#include "Algorithm.h"

Algorithm::Algorithm() :
        board(nullptr) { }

void Algorithm::setBoard(Board* boardPtr) {
    board = boardPtr;
}
