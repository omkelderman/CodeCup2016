#ifndef CODECUP_MONTECARLOPOLICIES_H
#define CODECUP_MONTECARLOPOLICIES_H

#include "Board.h"
#include <random>

class MonteCarloPolicy {
public:
    virtual std::size_t getNextMove(const Board& board, Move validMoves[], std::size_t validMovesCount) = 0;
};

class RandomMonteCarloPolicy : public MonteCarloPolicy {
public:
    RandomMonteCarloPolicy();
    virtual std::size_t getNextMove(const Board& board, Move* validMoves, std::size_t validMovesCount);

    template<class T>
    T generateRandomNumber(T max) {
        std::uniform_int_distribution<T> dis(0, max);
        return dis(randomGenerator);
    }

private:
    std::mt19937 randomGenerator;
};

#endif //CODECUP_MONTECARLOPOLICIES_H
