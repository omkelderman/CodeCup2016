#include "Simulation.h"
#include <algorithm>

Simulation::Simulation() :
        maxScore(0), startPointer(moves), endPointer(moves) {
}

Simulation::Simulation(const Simulation& otherSimulation) :
        maxScore(otherSimulation.maxScore) {
    copyMoves(otherSimulation, *this);
}

Simulation& Simulation::operator=(const Simulation& otherSimulation) {
    maxScore = otherSimulation.maxScore;
    copyMoves(otherSimulation, *this);
    return *this;
}

bool Simulation::operator<(const Simulation& otherSimulation) {
    return maxScore < otherSimulation.maxScore;
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

bool Simulation::checkFirstTwoMoves(const SlideDirection& direction1, const SlideDirection& direction2) const {
    return startPointer[0].direction == direction1 && startPointer[1].direction == direction2;
}

bool Simulation::checkFirstTwoMoves(const SlideDirection& direction, const Coords& coords) const {
    return startPointer[0].direction == direction && startPointer[1].coords == coords;
}

bool Simulation::checkFirstTwoMoves(const Coords& coords, const SlideDirection& direction) const {
    return startPointer[0].coords == coords && startPointer[1].direction == direction;
}

bool Simulation::checkFirstTwoMoves(const Coords& coords1, const Coords& coords2) const {
    return startPointer[0].coords == coords1 && startPointer[1].coords == coords2;
}

void Simulation::removeFirstTwo() {
    startPointer += 2;
}

std::size_t Simulation::getMovesCount() const {
    return endPointer - startPointer;
}

void Simulation::copyMoves(const Simulation& source, Simulation& destination) {
    // copy moves array
    std::copy(source.moves, source.moves+1000, destination.moves);

    // copy relative positions of start-pointer and end-pointer
    destination.startPointer = destination.moves + (source.startPointer - source.moves);
    destination.endPointer = destination.moves + (source.endPointer - source.moves);
}
