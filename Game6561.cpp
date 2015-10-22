//

#include "Game6561.h"

#include <iostream>

Game6561::Game6561(std::istream& istream, std::ostream& ostream, Algorithm& algorithm) :
        istream(istream), ostream(ostream), algorithm(algorithm), moveCounter(0) {
    algorithm.setBoard(&board);
}

void Game6561::run() {
    char c;
    istream >> c;
    if (c == 'A') {
        runPlayerA();
    } else if (c == 'B') {
        runPlayerB();
    } else {
        ostream << "FUCKING CAIA WHATchU DOIN'???";
    }
}

void Game6561::runPlayerA() {
    std::cerr << "Start player A" << std::endl;
    for (moveCounter = 0; moveCounter < 1000; moveCounter += 10) {
        placeBluePiece();
        readRedPiece();
        placeGreyPiece();
        readSlide();
        doSlide();
        readBluePiece();
        placeRedPiece();
        readGreyPiece();
        doSlide();
        readSlide();
    }
}

void Game6561::runPlayerB() {
    std::cerr << "Start player B" << std::endl;
    for (moveCounter = 0; moveCounter < 1000; moveCounter += 10) {
        readBluePiece();
        placeRedPiece();
        readGreyPiece();
        doSlide();
        readSlide();
        placeBluePiece();
        readRedPiece();
        placeGreyPiece();
        readSlide();
        doSlide();
    }
}

void Game6561::readBluePiece() {
    const std::pair<coord, coord>& xy = readCoords();
    board.setPiece(xy.first, xy.second, BLUE);
}

void Game6561::readRedPiece() {
    const std::pair<coord, coord>& xy = readCoords();
    board.setPiece(xy.first, xy.second, RED);
}

void Game6561::readGreyPiece() {
    const std::pair<coord, coord>& xy = readCoords();
    board.setPiece(xy.first, xy.second, GREY);
}

const std::pair<coord, coord> Game6561::readCoords() const {
    coord x, y;
    istream >> y >> x;
    return std::make_pair(x, y);
}

void Game6561::readSlide() {
    SlideDirection dir;
    istream >> dir;
    board.slide(dir);
}

void Game6561::placeBluePiece() {
    const std::pair<coord, coord>& move = algorithm.calculateBlueMove();
    board.setPiece(move.first, move.second, BLUE);
    ostream << move.first << move.second;
}

void Game6561::placeRedPiece() {
    const std::pair<coord, coord>& move = algorithm.calculateRedMove();
    board.setPiece(move.first, move.second, RED);
    ostream << move.first << move.second;
}

void Game6561::placeGreyPiece() {
    const std::pair<coord, coord>& move = algorithm.calculateGreyMove();
    board.setPiece(move.first, move.second, GREY);
    ostream << move.first << move.second;
}

void Game6561::doSlide() {
    SlideDirection move = algorithm.calculateSlide();
    board.slide(move);
    ostream << move;
}