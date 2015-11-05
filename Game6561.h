//

#ifndef CODECUP_GAME6561_H
#define CODECUP_GAME6561_H

#include <istream>
#include <ostream>
#include "Board.h"
#include "Algorithm.h"
#include <utility>

class Game6561 {
public:
    Game6561(std::istream& istream, std::ostream& ostream, Algorithm& algorithm);

    void run();
private:
    std::istream& istream;
    std::ostream& ostream;
    Board board;
    Algorithm& algorithm;

    unsigned short moveCounter;

    void runPlayerA();
    void runPlayerB();

    void readBluePiece();
    void readRedPiece();
    void readGreyPiece();
    const std::pair<coord, coord> readCoords();
    void readSlide();
    std::string readLine(std::size_t expectedLength = 1);

    void placeBluePiece();
    void placeRedPiece();
    void placeGreyPiece();
    void doSlide();
    void writeCoords(const std::pair<coord, coord>& coords);
    void printBoard();
};


#endif //CODECUP_GAME6561_H
