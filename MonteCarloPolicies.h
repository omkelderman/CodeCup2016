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

class HeuristicMonteCarloPolicy : public MonteCarloPolicy {
public:
    virtual std::size_t getNextMove(const Board& board, Move* validMoves, std::size_t validMovesCount);
private:

    std::size_t getNextSlideMove(const Board& board, Move* validMoves, std::size_t validMovesCount);
    std::size_t getNextCoordsMove(const Board& board, Move* validMoves, std::size_t validMovesCount);

    std::size_t getIndexOfMove(Move* validMoves, std::size_t validMovesCount, const Coords& coords);

    /**
     * rhythmColor must be one of the colors
     * color must not be equal to the rhythmColor
     */
    PieceColor determineOtherJunkColor(const GameRhythmState& rhythmColor, const PieceColor& color);
};

#endif //CODECUP_MONTECARLOPOLICIES_H
