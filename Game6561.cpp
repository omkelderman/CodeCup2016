#include "Game6561.h"
#include "GameException.h"

Game6561::Game6561(std::istream& istream, std::ostream& ostream, std::ostream& logStream, Algorithm& algorithm) :
        istream(istream), ostream(ostream), logStream(logStream), algorithm(algorithm) {
    algorithm.setGameBoardPtr(&board);
    algorithm.setGameGameProgressPtr(&gameProgress);
}

void Game6561::run() {
    readNextLine();
    if (nextLine[0] == 'A') {
        doMove();
#ifdef DEBUG_BUILD
        printBoard();
#endif
    }
    while (readNextLine()) {
        parseNextLine();
#ifdef DEBUG_BUILD
        printBoard();
#endif
        doMove();
#ifdef DEBUG_BUILD
        printBoard();
#endif
    }
}

bool Game6561::readNextLine() {
    std::getline(istream, nextLine);
    return nextLine != "Quit";
}

void Game6561::parseNextLine() {
    switch (board.getGameRhythmState()) {
        case GR_BLUE:
            readPiece(BLUE);
            break;
        case GR_RED:
            readPiece(RED);
            break;
        case GR_GREY:
            readPiece(GREY);
            break;
        case GR_SLIDE1:
        case GR_SLIDE2:
            readSlide();
            break;
    }
}

void Game6561::readPiece(PieceColor color) {
    const Coords& coords = readCoords();
    board.setPiece(coords, color);
    gameProgress.updateLastReadMoveAndMoveCounter(coords);
}

void Game6561::readSlide() {
    switch (nextLine[0]) {
        case 'U':
            board.slideUp();
            gameProgress.updateLastReadMoveAndMoveCounter(SD_UP);
            break;
        case 'D':
            board.slideDown();
            gameProgress.updateLastReadMoveAndMoveCounter(SD_DOWN);
            break;
        case 'L':
            board.slideLeft();
            gameProgress.updateLastReadMoveAndMoveCounter(SD_LEFT);
            break;
        case 'R':
            board.slideRight();
            gameProgress.updateLastReadMoveAndMoveCounter(SD_RIGHT);
            break;
        default:
            break;
    }
}

const Coords Game6561::readCoords() {
    coord row = (coord) (nextLine[0] - '1');
    coord column = (coord) (nextLine[1] - '1');
    return Coords(row, column);
}

void Game6561::doMove() {
    if (gameProgress.moveCounter >= MAX_MOVES) {
        logStream << "Max moves reached: " << std::endl;
        return;
    }

    try {
        Move lastDoneMove;
        algorithm.ensureValidState();
        switch (board.getGameRhythmState()) {
            case GR_BLUE:
                lastDoneMove.coords = algorithm.calculateBlueMove();
                board.setPiece(lastDoneMove.coords, BLUE);
                writeCoords(lastDoneMove.coords);
                break;
            case GR_RED:
                lastDoneMove.coords = algorithm.calculateRedMove();
                board.setPiece(lastDoneMove.coords, RED);
                writeCoords(lastDoneMove.coords);
                break;
            case GR_GREY:
                lastDoneMove.coords = algorithm.calculateGreyMove();
                board.setPiece(lastDoneMove.coords, GREY);
                writeCoords(lastDoneMove.coords);
                break;
            case GR_SLIDE1:
            case GR_SLIDE2:
                lastDoneMove.direction = algorithm.calculateSlide();
                board.slide(lastDoneMove.direction);
                writeSlide(lastDoneMove.direction);
                break;
        }
        gameProgress.updateLastDoneMoveAndMoveCounter(lastDoneMove);
    } catch (const GameException& e) {
        logStream << "Impossible move detected: " << e.what() << std::endl;
    }
}

void Game6561::writeCoords(const Coords& coords) {
    ostream << coords.row + 1 << coords.column + 1 << std::endl;
}

void Game6561::writeSlide(const SlideDirection& slideDirection) {
    ostream << slideDirection << std::endl;
}

void Game6561::printBoard() {
    logStream << gameProgress.moveCounter << ": " << board << std::endl;
}
