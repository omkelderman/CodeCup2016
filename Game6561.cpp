#include "Game6561.h"
#include "GameException.h"

/*GameState::GameState() :
        moveCounter(0), gameRhythmState(GR_BLUE) { }

GameState& GameState::operator++() {
    ++moveCounter;
    ++gameRhythmState;
    return *this;
}

GameState GameState::operator++(int) {
    GameState tmp(*this);
    operator++();
    return tmp;
}*/

Game6561::Game6561(std::istream& istream, std::ostream& ostream, std::ostream& logStream, Algorithm& algorithm) :
        istream(istream), ostream(ostream), logStream(logStream), algorithm(algorithm), moveCounter(0) {
    algorithm.setGameBoardPtr(&board);
    algorithm.setGameMoveCounterPtr(&moveCounter);
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
    ++moveCounter;
}

void Game6561::readPiece(PieceColor color) {
    const Coords& coords = readCoords();
    board.setPiece(coords, color);
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
    if (moveCounter >= MAX_MOVES) {
        logStream << "Max moves reached: " << std::endl;
        return;
    }

    try {
        algorithm.ensureValidState();
        switch (board.getGameRhythmState()) {
            case GR_BLUE: {
                const Coords& coords = algorithm.calculateBlueMove();
                board.setPiece(coords, BLUE);
                writeCoords(coords);
                break;
            }
            case GR_RED: {
                const Coords& coords = algorithm.calculateRedMove();
                board.setPiece(coords, RED);
                writeCoords(coords);
                break;
            }
            case GR_GREY: {
                const Coords& coords = algorithm.calculateGreyMove();
                board.setPiece(coords, GREY);
                writeCoords(coords);
                break;
            }
            case GR_SLIDE1:
            case GR_SLIDE2:
                SlideDirection slideDirection = algorithm.calculateSlide();
                board.slide(slideDirection);
                writeSlide(slideDirection);
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

void Game6561::writeSlide(const SlideDirection& slideDirection) {
    ostream << slideDirection << std::endl;
}

void Game6561::printBoard() {
    logStream << moveCounter << ": " << board << std::endl;
}

/*unsigned short GameState::getMoveCounter() const {
    return moveCounter;
}

GameRhythmState GameState::getGameRhythmState() const {
    return gameRhythmState;
}

void GameState::setLastDoneMove(const Coords& coords) {
    lastDoneMove.coords = coords;
}

void GameState::setLastDoneMove(const SlideDirection& slideDirection) {
    lastDoneMove.direction = slideDirection;
}

Coords GameState::getLastDoneMoveAsCoords() const {
    return lastDoneMove.coords;
}

SlideDirection GameState::getLastDoneMoveAsSlideDirection() const {
    return lastDoneMove.direction;
}

void GameState::setLastReadMove(const Coords& coords) {
    lastReadMove.coords = coords;
}

void GameState::setLastReadMove(const SlideDirection& slideDirection) {
    lastReadMove.direction = slideDirection;
}

Coords GameState::getLastReadMoveAsCoords() const {
    return lastReadMove.coords;
}

SlideDirection GameState::getLastReadMoveAsSlideDirection() const {
    return lastReadMove.direction;
}*/
