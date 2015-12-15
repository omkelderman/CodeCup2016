#ifndef CODECUP_GAME6561_H
#define CODECUP_GAME6561_H

#include <istream>
#include <ostream>
#include "Board.h"
#include "Algorithm.h"
#include "Move.h"
#include <utility>
#include <string>
#include "GameRhythmState.h"

/*class GameState {
public:
    GameState();
    // implicit copy constructor and assignment operator should do

    GameState& operator++();
    GameState operator++(int);

    unsigned short getMoveCounter() const;
    GameRhythmState getGameRhythmState() const;

    void setLastDoneMove(const Coords& coords);
    void setLastDoneMove(const SlideDirection& slideDirection);

    Coords getLastDoneMoveAsCoords() const;
    SlideDirection getLastDoneMoveAsSlideDirection() const;

    void setLastReadMove(const Coords& coords);
    void setLastReadMove(const SlideDirection& slideDirection);

    Coords getLastReadMoveAsCoords() const;
    SlideDirection getLastReadMoveAsSlideDirection() const;
private:
    unsigned short moveCounter;
    GameRhythmState gameRhythmState;

    Move lastDoneMove;
    Move lastReadMove;
};*/

class Game6561 {
public:
    static const std::size_t MAX_MOVES = 1000;

    Game6561(std::istream& istream, std::ostream& ostream, std::ostream& logStream, Algorithm& algorithm);
    void run();
private:
    std::istream& istream;
    std::ostream& ostream;
    std::ostream& logStream;
    Board board;
    Algorithm& algorithm;
    unsigned short moveCounter;

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
    void writeSlide(const SlideDirection& slideDirection);


    // debug functions
    void printBoard();
};


#endif //CODECUP_GAME6561_H
