//

#ifndef CODECUP_GAME6561_H
#define CODECUP_GAME6561_H

#include <istream>
#include <ostream>
#include "Board.h"
#include "Algorithm.h"
#include <utility>
#include <string>

enum GameRhythmState {
    GR_BLUE, GR_RED, GR_GREY, GR_SLIDE1, GR_SLIDE2
};

GameRhythmState& operator++(GameRhythmState& gameRhythmState);

GameRhythmState operator++(GameRhythmState& gameRhythmState, int);

class Game6561 {
public:
    Game6561(std::istream& istream, std::ostream& ostream, std::ostream& logStream, Algorithm& algorithm);

    void run();
private:
    static const int MAX_MOVES = 1000;
    std::istream& istream;
    std::ostream& ostream;
    std::ostream& logStream;
    Board board;
    Algorithm& algorithm;
    GameRhythmState gameRhythmState;

    std::string nextLine;

    unsigned short moveCounter;

    /**
     * Reads one line from input and stores it into global var 'nextLine'
     * @return false if nextLine equals 'Quit', true otherwise
     */
    bool readNextLine();

    /**
     * parses the content of the 'nextLine' var and updates the board accordingly
     */
    void parseNextLine();

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
