#ifndef CODECUP_GAME6561_H
#define CODECUP_GAME6561_H

#include <istream>
#include <ostream>
#include "Board.h"
#include "Algorithm.h"
#include <utility>
#include <string>

/**
 * An enumeration to keep track of the Rhythm, applied in the 6561 game.
 * This "rhythm" decides what to do in the current turn.
 */
enum GameRhythmState {
    GR_BLUE, GR_RED, GR_GREY, GR_SLIDE1, GR_SLIDE2
};

GameRhythmState& operator++(GameRhythmState& gameRhythmState);

GameRhythmState operator++(GameRhythmState& gameRhythmState, int);

class GameState {
public:
    GameState();
    // implicit copy constructor and assignment operator should do

    GameState& operator++();
    GameState operator++(int);

    unsigned short getMoveCounter() const;
    GameRhythmState getGameRhythmState() const;
private:
    unsigned short moveCounter;
    GameRhythmState gameRhythmState;
};

class Game6561 {
public:
    static const int MAX_MOVES = 1000;

    Game6561(std::istream& istream, std::ostream& ostream, std::ostream& logStream, Algorithm& algorithm);
    void run();
private:
    std::istream& istream;
    std::ostream& ostream;
    std::ostream& logStream;
    Board board;
    Algorithm& algorithm;
    GameState gameState;

    std::string nextLine;

    /**
     * Reads one line from input and stores it into global var 'nextLine'
     * @return false if nextLine equals 'Quit', true otherwise
     */
    bool readNextLine();

    /**
     * parses the content of the 'nextLine' var and updates the board accordingly
     */
    void parseNextLine();

    void readPiece(PieceColor color);
    void readSlide();

    const Coords readCoords();
    /**
     * calculate the next move, updates the board and tells output that move.
     * If no valid move is available or the 1000 moves have been reached, this does nothing.
     */
    void doMove();
    void writeCoords(const Coords& coords);


    // debug functions
    void printBoard();
};


#endif //CODECUP_GAME6561_H
