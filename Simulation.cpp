#include "Simulation.h"

Simulation::Simulation() :
        maxScore(0), startPointer(moves), endPointer(moves) {
}

void Simulation::addMove(const SlideDirection& direction) {
    endPointer->direction = direction;
    ++endPointer;
}

void Simulation::addMove(const Coords& coords) {
    endPointer->coords = coords;
    ++endPointer;
}

const SlideDirection& Simulation::getFirstMoveAsSlideDirection() {
    return startPointer->direction;
}

const Coords& Simulation::getFirstMoveAsCoords() {
    return startPointer->coords;
}

bool Simulation::checkFirstTwoMoves(const SlideDirection& direction1, const SlideDirection& direction2) {
    return startPointer[0].direction == direction1 && startPointer[1].direction == direction2;
}

bool Simulation::checkFirstTwoMoves(const SlideDirection& direction, const Coords& coords) {
    return startPointer[0].direction == direction && startPointer[1].coords == coords;
}

bool Simulation::checkFirstTwoMoves(const Coords& coords, const SlideDirection& direction) {
    return startPointer[0].coords == coords && startPointer[1].direction == direction;
}

bool Simulation::checkFirstTwoMoves(const Coords& coords1, const Coords& coords2) {
    return startPointer[0].coords == coords1 && startPointer[1].coords == coords2;
}

void Simulation::removeFirstTwo() {
    startPointer += 2;
}

std::size_t Simulation::getMovesCount() {
    return endPointer - startPointer;
}