//

#include "Game6561.h"

#include <iostream>
#include <stdexcept>

Game6561::Game6561(std::istream& istream, std::ostream& ostream, Algorithm& algorithm) :
        istream(istream), ostream(ostream), algorithm(algorithm), moveCounter(0) {
    algorithm.setBoard(&board);
}

void Game6561::run() {
    char c = readLine()[0];
    if (c == 'A') {
        runPlayerA();
    } else if (c == 'B') {
        runPlayerB();
    } else {
        throw std::logic_error("No valid begin found!");
    }
}

void Game6561::runPlayerA() {
    std::cerr << "Start player A" << std::endl;
    for (moveCounter = 0; moveCounter < 1000; ) {
        placeBluePiece();
        printBoard();
        readRedPiece();
        printBoard();
        placeGreyPiece();
        printBoard();
        readSlide();
        printBoard();
        doSlide();
        printBoard();
        readBluePiece();
        printBoard();
        placeRedPiece();
        printBoard();
        readGreyPiece();
        printBoard();
        doSlide();
        printBoard();
        readSlide();
        printBoard();
    }
}

void Game6561::runPlayerB() {
    std::cerr << "Start player B" << std::endl;
    for (moveCounter = 0; moveCounter < 1000; ) {
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

const std::pair<coord, coord> Game6561::readCoords() {
    std::string line = readLine(2);
    if(line[0] < '1' || line[0] > '4' || line[1] < '1' || line[1] > '4'){
        throw std::logic_error("Invalid coords given! Line: " + line);
    }
    coord y = (coord) (line[0] - '1');
    coord x = (coord) (line[1] - '1');

    return std::make_pair(x, y);
}

void Game6561::readSlide() {
    std::string line = readLine();
    SlideDirection direction;
    switch (line[0]) {
        case 'U':
            direction = UP;
            break;
        case 'D':
            direction = DOWN;
            break;
        case 'L':
            direction = LEFT;
            break;
        case 'R':
            direction = RIGHT;
            break;
        default:
            throw std::logic_error("Invalid slide! Line: " + line);

    }
    board.slide(direction);
}

void Game6561::placeBluePiece() {
    const std::pair<coord, coord>& move = algorithm.calculateBlueMove();
    board.setPiece(move.first, move.second, BLUE);
    writeCoords(move);
}

void Game6561::placeRedPiece() {
    const std::pair<coord, coord>& move = algorithm.calculateRedMove();
    board.setPiece(move.first, move.second, RED);
    writeCoords(move);
}

void Game6561::placeGreyPiece() {
    const std::pair<coord, coord>& move = algorithm.calculateGreyMove();
    board.setPiece(move.first, move.second, GREY);
    writeCoords(move);
}

void Game6561::doSlide() {
    SlideDirection move = algorithm.calculateSlide();
    board.slide(move);
    ostream << move << std::endl;
}

void Game6561::printBoard() {
    std::cerr << moveCounter++ << ": " << board << std::endl;
}

std::string Game6561::readLine(std::size_t expectedLength /*= 1*/) {
    std::string line;
    std::getline(istream, line);
    if(line.size() != expectedLength){
        throw std::logic_error("Line is not of the expected length");
    }
    return line;
}

void Game6561::writeCoords(const std::pair<coord, coord>& coords) {
    ostream << coords.first + 1 << coords.second + 1 << std::endl;
}
