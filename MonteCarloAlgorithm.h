#ifndef CODECUP_MONTECARLOALGORITHM_H
#define CODECUP_MONTECARLOALGORITHM_H

#include <forward_list>
#include <random>
#include "Algorithm.h"
#include "Move.h"
#include "Simulation.h"
#include "Game6561.h"

class MonteCarloAlgorithm : public Algorithm {
public:
    MonteCarloAlgorithm();

    virtual const Coords calculateRedMove() const;
    virtual const Coords calculateBlueMove() const;
    virtual const Coords calculateGreyMove() const;
    virtual SlideDirection calculateSlide() const;

    void simulate(std::size_t movesToCalculate);

    //monte carlo stuff
private:
    // random generator
    std::mt19937 randomGenerator;

    // simulations
    std::forward_list<Simulation> simulations;
    std::size_t simulateGame(std::size_t maxMovesInSimulation);

    unsigned short generateRandomNumber(unsigned short max, unsigned short exclusionList[] = nullptr,
                                        unsigned short exclusionListLength = 0);

    // add a random slide to the given simulation, and update the given board accordingly
    // returns true if a valid move was possible, false otherwise
    bool addRandomSlideToSimulation(Simulation& simulation, Board& board);

    // add a random piece placement to the given simulation, and update the given board accordingly
    // returns true if a valid move was possible, false otherwise
    bool addRandomCoordsToSimulation(Simulation& simulation, Board& board, PieceColor color);

    unsigned short getNonEmptyCoords(unsigned short nonEmptyCoords[], const Board& board);
    unsigned short coordsToUShort(coord row, coord column);
};

#endif //CODECUP_MONTECARLOALGORITHM_H
