#include "Game6561.h"
#include "GameException.h"

GameRhythmState& operator++(GameRhythmState& gameRhythmState) {
    switch(gameRhythmState) {
        case GR_BLUE:
            gameRhythmState = GR_RED;
            break;
        case GR_RED:
            gameRhythmState = GR_GREY;
            break;
        case GR_GREY:
            gameRhythmState = GR_SLIDE1;
            break;
        case GR_SLIDE1:
            gameRhythmState = GR_SLIDE2;
            break;
        case GR_SLIDE2:
            gameRhythmState = GR_BLUE;
            break;
    }
    return gameRhythmState;
}

GameRhythmState operator++(GameRhythmState& gameRhythmState, int) {
    GameRhythmState tmp = gameRhythmState;
    ++gameRhythmState;
    return tmp;
}

Game6561::Game6561(std::istream& istream, std::ostream& ostream, std::ostream& logStream, Algorithm& algorithm) :
        istream(istream), ostream(ostream), logStream(logStream), algorithm(algorithm), gameRhythmState(GR_BLUE), moveCounter(0) {
    algorithm.setBoard(&board);
}

void Game6561::run() {
    readNextLine();
    if(nextLine[0] == 'A') {
        doMove();
#ifdef DO_DEBUG_LOG
        printBoard();
#endif
    }
    while(readNextLine()) {
        parseNextLine();
#ifdef DO_DEBUG_LOG
        printBoard();
#endif
        doMove();
#ifdef DO_DEBUG_LOG
        printBoard();
#endif
    }
}

bool Game6561::readNextLine() {
    std::getline(istream, nextLine);
    return nextLine != "Quit";
}

void Game6561::parseNextLine() {
    switch(gameRhythmState++){
        case GR_BLUE: {
            const Coords& coords = readCoords();
            board.setPiece(coords.row, coords.column, BLUE);
            break;
        }
        case GR_RED: {
            const Coords& coords = readCoords();
            board.setPiece(coords.row, coords.column, RED);
            break;
        }
        case GR_GREY: {
            const Coords& coords = readCoords();
            board.setPiece(coords.row, coords.column, GREY);
            break;
        }
        case GR_SLIDE1:
        case GR_SLIDE2:
            readSlide();
            break;
    }
    ++moveCounter;
}

void Game6561::readSlide() {
    switch (nextLine[0]) {
        case 'U':
            board.slideUp();
            break;
        case 'D':
            board.slideDown();
            break;
        case 'L':
            board.slideLeft();
            break;
        case 'R':
            board.slideRight();
            break;
        default:break;
    }
}

const Coords Game6561::readCoords() {
    coord row = (coord) (nextLine[0] - '1');
    coord column = (coord) (nextLine[1] - '1');
    return Coords(row, column);
}

void Game6561::doMove() {
    if(moveCounter >= MAX_MOVES) {
        logStream << "Max moves reached: " << std::endl;
        return;
    }

    try {
        switch (gameRhythmState++) {
            case GR_BLUE: {
                const Coords& coords = algorithm.calculateBlueMove();
                board.setPiece(coords.row, coords.column, BLUE);
                writeCoords(coords);
                break;
            }
            case GR_RED: {
                const Coords& coords = algorithm.calculateRedMove();
                board.setPiece(coords.row, coords.column, RED);
                writeCoords(coords);
                break;
            }
            case GR_GREY: {
                const Coords& coords = algorithm.calculateGreyMove();
                board.setPiece(coords.row, coords.column, GREY);
                writeCoords(coords);
                break;
            }
            case GR_SLIDE1:
            case GR_SLIDE2:
                SlideDirection slideDirection = algorithm.calculateSlide();
                board.slide(slideDirection);
                ostream << slideDirection << std::endl;
                break;
        }
    } catch (const GameException& e) {
        logStream << "Impossible move detected: " << e.what() << std::endl;
    }
    ++moveCounter;
}

void Game6561::writeCoords(const Coords& coords) {
    ostream << coords.row + 1 << coords.column + 1 << std::endl;
}

void Game6561::printBoard() {
    logStream << moveCounter << ": " << board << std::endl;
}
