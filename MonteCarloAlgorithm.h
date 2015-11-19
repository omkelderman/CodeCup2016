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

    // randomDistributions
    std::uniform_int_distribution<unsigned short> randomSlideDistribution;
    std::uniform_int_distribution<unsigned short> randomCoordsDistribution;

    // generate a completely random slide
    SlideDirection generatorRandomSlide();

    // generate completely random coords
    Coords generatorRandomCoords();

    // add a random slide to the given simulation, and update the given board accordingly
    // returns true if a valid move was possible, false otherwise
    bool addRandomSlideToSimulation(Simulation& simulation, Board& board);

    // add a random peace placement to the given simulation, and update the given board accordingly
    // returns true if a valid move was possible, false otherwise
    bool addRandomCoordsToSimulation(Simulation& simulation, Board& board, PieceColor color);

    // simulations
    std::forward_list<Simulation> simulations;
    size_t simulateGame();
};

#endif //CODECUP_MONTECARLOALGORITHM_H
