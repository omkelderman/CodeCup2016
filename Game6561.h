//

#ifndef CODECUP_GAME6561_H
#define CODECUP_GAME6561_H

#include <istream>
#include <ostream>
#include "Board.h"
#include <utility>

class Game6561 {
public:
    Game6561(std::istream& istream, std::ostream& ostream);

    void run();
private:
    std::istream& istream;
    std::ostream& ostream;
    Board board;

    unsigned short moveCounter;

    void runPlayerA();
    void runPlayerB();

    void readBluePiece();
    void readRedPiece();
    void readGreyPiece();
    const std::pair<coord, coord> readCoords() const;
    void readSlide();

    void placeBluePiece();
    void placeRedPiece();
    void placeGreyPiece();
    void doSlide();
};


#endif //CODECUP_GAME6561_H
