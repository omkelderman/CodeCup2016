#include "Simulation.h"
#include <algorithm>

Simulation::Simulation() :
        maxScore(0) {
}

Simulation::Simulation(const Simulation& otherSimulation) :
        moves(otherSimulation.moves), maxScore(otherSimulation.maxScore) {
}

Simulation& Simulation::operator=(const Simulation& otherSimulation) {
    moves = otherSimulation.moves;
    maxScore = otherSimulation.maxScore;
    return *this;
}

bool Simulation::operator<(const Simulation& otherSimulation) {
    return maxScore < otherSimulation.maxScore;
}

void Simulation::addMove(const SlideDirection& direction) {
    moves.push_back(direction);
}

void Simulation::addMove(const Coords& coords) {
    moves.push_back(coords);
}

const SlideDirection& Simulation::getFirstMoveAsSlideDirection() {
    return moves.begin()->direction;
}

const Coords& Simulation::getFirstMoveAsCoords() {
    return moves.begin()->coords;
}

bool Simulation::checkFirstTwoMoves(const SlideDirection& direction1, const SlideDirection& direction2) const {
    return moves[0].direction == direction1 && moves[1].direction == direction2;
}

bool Simulation::checkFirstTwoMoves(const SlideDirection& direction, const Coords& coords) const {
    return moves[0].direction == direction && moves[1].coords == coords;
}

bool Simulation::checkFirstTwoMoves(const Coords& coords, const SlideDirection& direction) const {
    return moves[0].coords == coords && moves[1].direction == direction;
}

bool Simulation::checkFirstTwoMoves(const Coords& coords1, const Coords& coords2) const {
    return moves[0].coords == coords1 && moves[1].coords == coords2;
}

void Simulation::removeFirstTwo() {
    moves.pop_front();
    moves.pop_front();
}

std::size_t Simulation::getMovesCount() const {
    return moves.size();
}
