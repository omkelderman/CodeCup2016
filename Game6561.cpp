//

#include "Game6561.h"

#include <iostream>
#include <stdexcept>
#include "GameException.h"

Game6561::Game6561(std::istream& istream, std::ostream& ostream, Algorithm& algorithm) :
        istream(istream), ostream(ostream), algorithm(algorithm), moveCounter(0) {
    algorithm.setBoard(&board);
}

void Game6561::run() {
    try {
        char c = readLine()[0];
        if (c == 'A') {
            runPlayerA();
        } else if (c == 'B') {
            runPlayerB();
        } else {
            throw std::domain_error("No valid begin found!");
        }
    } catch (const GameException& e) {
        std::cerr << "Game ended: " << e.what() << std::endl;
    }
    std::string line = readLine(0);
    std::cerr << "end of program, line received: " << line << std::endl;
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
    const Coords& xy = readCoords();
    board.setPiece(xy.row, xy.column, BLUE);
}

void Game6561::readRedPiece() {
    const Coords& xy = readCoords();
    board.setPiece(xy.row, xy.column, RED);
}

void Game6561::readGreyPiece() {
    const Coords& xy = readCoords();
    board.setPiece(xy.row, xy.column, GREY);
}

const Coords Game6561::readCoords() {
    std::string line = readLine(2);
    if(line[0] < '1' || line[0] > '4' || line[1] < '1' || line[1] > '4'){
        throw std::domain_error("Could not read valid coords! Line: " + line);
    }
    coord row = (coord) (line[0] - '1');
    coord column = (coord) (line[1] - '1');
    return Coords(row, column);
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
            throw std::domain_error("Could not read valid slide! Line: " + line);

    }
    board.slide(direction);
}

void Game6561::placeBluePiece() {
    const Coords& move = algorithm.calculateBlueMove();
    board.setPiece(move.row, move.column, BLUE);
    writeCoords(move);
}

void Game6561::placeRedPiece() {
    const Coords& move = algorithm.calculateRedMove();
    board.setPiece(move.row, move.column, RED);
    writeCoords(move);
}

void Game6561::placeGreyPiece() {
    const Coords& move = algorithm.calculateGreyMove();
    board.setPiece(move.row, move.column, GREY);
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
    if(expectedLength != 0 && line.size() != expectedLength){
        throw std::domain_error("Line is not of the expected length: " + line);
    }
    return line;
}

void Game6561::writeCoords(const Coords& coords) {
    ostream << coords.row + 1 << coords.column + 1 << std::endl;
}
