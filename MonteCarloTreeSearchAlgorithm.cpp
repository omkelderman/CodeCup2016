#include <stdexcept>
#include "MonteCarloTreeSearchAlgorithm.h"
#include <forward_list>
#ifdef _WIN32
#include <ctime>
#endif

MonteCarloTreeSearchAlgorithm::MonteCarloTreeSearchAlgorithm(std::size_t movesToSimulate, double ucb1Constant) :
        movesToSimulate(movesToSimulate), ucb1Constant(ucb1Constant) {
    // seed the random generator with a (hopefully) non-deterministic random number
#ifdef DEBUG_BUILD
    randomGenerator.seed(69);
#else
#ifdef _WIN32
    randomGenerator.seed((unsigned)time(nullptr));
#else
    std::random_device rd;
    randomGenerator.seed(rd());
#endif
#endif
}

const Coords MonteCarloTreeSearchAlgorithm::calculateRedMove() const {
    return nextMove.coords;
}

const Coords MonteCarloTreeSearchAlgorithm::calculateBlueMove() const {
    return nextMove.coords;
}

const Coords MonteCarloTreeSearchAlgorithm::calculateGreyMove() const {
    return nextMove.coords;
}

SlideDirection MonteCarloTreeSearchAlgorithm::calculateSlide() const {
    return nextMove.direction;
}

void MonteCarloTreeSearchAlgorithm::ensureValidState() {
    Move validMoves[16];
    std::size_t validMoveCounter = gameBoardPtr->getValidMoves(validMoves);
    // if validMoveCounter == 0 --> BOOM, we don't check, should be checked by caia
    if (validMoveCounter == 1) {
        nextMove = validMoves[0];
        return;
    }
#ifdef DEBUG_BUILD
    if(validMoveCounter == 0) {
        throw std::logic_error("No valid moves found, this shouldn't have happened....????");
    }
#endif

    runSimulations(movesToSimulate);

    // RIP CODE, i need this thing to be initalized with copies of localBoard so yeah....
    Board validNextBoards[16] = {*gameBoardPtr, *gameBoardPtr, *gameBoardPtr, *gameBoardPtr, *gameBoardPtr,
                                 *gameBoardPtr, *gameBoardPtr, *gameBoardPtr, *gameBoardPtr, *gameBoardPtr,
                                 *gameBoardPtr, *gameBoardPtr, *gameBoardPtr, *gameBoardPtr, *gameBoardPtr,
                                 *gameBoardPtr};

    std::size_t theChosenMoveIndex = 0;
    std::uint32_t bestScore = 0;
    for (std::size_t validMoveIndex = 0; validMoveIndex < validMoveCounter; ++validMoveIndex) {
        validNextBoards[validMoveIndex].doMove(validMoves[validMoveIndex]);
        auto it = statistics.find(validNextBoards[validMoveIndex]);
        if(it != statistics.end()) {
            if(it->second.score > bestScore) {
                theChosenMoveIndex = validMoveIndex;
                bestScore = it->second.score;
            }
        }
    }

    nextMove = validMoves[theChosenMoveIndex];
}

void MonteCarloTreeSearchAlgorithm::runSimulations(std::size_t movesToSimulate) {
    statistics.clear();
    while (movesToSimulate > 0) {
        movesToSimulate -= simulateGame(movesToSimulate);
    }
}

std::size_t MonteCarloTreeSearchAlgorithm::simulateGame(const std::size_t movesToSimulate) {
    std::forward_list<Board> visitedBoardStates;

    Board localBoard = *gameBoardPtr;
    std::uint32_t maxScoreOfSimulation = 0;
    Move validMoves[16];
    std::size_t simulatedMovesCount = 0;
    bool expensionPhaseHasHappend = false;
    while (simulatedMovesCount < movesToSimulate) {
        std::size_t validMovesCount = localBoard.getValidMoves(validMoves);
        if (validMovesCount == 0) {
            // no more moves, them game is done
            break;
        }

        // RIP CODE, i need this thing to be initalized with copies of localBoard so yeah....
        Board validNextBoards[16] = {localBoard, localBoard, localBoard, localBoard, localBoard, localBoard, localBoard,
                                     localBoard, localBoard, localBoard, localBoard, localBoard, localBoard, localBoard,
                                     localBoard, localBoard};
        bool statsKnown = true;
        for (std::size_t validMoveIndex = 0; validMoveIndex < validMovesCount; ++validMoveIndex) {
            validNextBoards[validMoveIndex].doMove(validMoves[validMoveIndex]);
            if (statistics.find(validNextBoards[validMoveIndex]) == statistics.end()) {
                statsKnown = false;
                break;
            }
        }
        std::size_t theChosenMoveIndex = 0;
        if (statsKnown) {
            // selection with UCB1-stuff
            std::uint32_t playCountSum = 0;
            for (std::size_t validIndex = 0; validIndex < validMovesCount; ++validIndex) {
                playCountSum += statistics[validNextBoards[validIndex]].playCount;
            }
            double logOfPlayCountSum = std::log(playCountSum);
            double maxUcb1Value = 0;
            for (std::size_t validIndex = 0; validIndex < validMovesCount; ++validIndex) {
                Statistic& stat = statistics[validNextBoards[validIndex]];
                double ucb1Value = stat.score + ucb1Constant * std::sqrt(logOfPlayCountSum / stat.playCount);
                if (ucb1Value > maxUcb1Value) {
                    maxUcb1Value = ucb1Value;
                    theChosenMoveIndex = validIndex;
                }
            }
        } else {
            // selection with random, or simulation with random, depending on where we are in the algorithm
            theChosenMoveIndex = generateRandomNumber(validMovesCount - 1);
        }

        // update localBoard with the chosen move
        localBoard.doMove(validMoves[theChosenMoveIndex]);
        // update max score
        maxScoreOfSimulation = std::max(maxScoreOfSimulation, localBoard.getBoardScore());

        if (!expensionPhaseHasHappend && statistics.find(localBoard) == statistics.end()) {
            expensionPhaseHasHappend = true;
            statistics.insert(std::make_pair(localBoard, Statistic {0, 0}));
        }

        visitedBoardStates.push_front(localBoard);

        ++simulatedMovesCount;
    }

    std::uint32_t prevScore = 0;
    for (const Board& visitedBoard : visitedBoardStates) {
        auto it = statistics.find(visitedBoard);
        if (it != statistics.end()) {
            Statistic& stat = it->second;
            ++stat.playCount;

            if(prevScore == 0) {
                // first board in visitied list that exists in the statistics, so it has to be the just expanded board
                // this means this board should have the value of the just done simulation
                stat.score = maxScoreOfSimulation;
            } else {
                // otherwise do fancy shizz
                stat.score = std::max(stat.score, prevScore);
            }
            prevScore = stat.score;
        }
    }

    return simulatedMovesCount;
}

std::size_t MonteCarloTreeSearchAlgorithm::generateRandomNumber(std::size_t max) {
    std::uniform_int_distribution<std::size_t> dis(0, max);
    return dis(randomGenerator);
}