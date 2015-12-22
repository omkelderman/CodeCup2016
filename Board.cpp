#include "Board.h"

#include <stdexcept>

Board::Board() :
        gameRhythmState(GR_BLUE) {
}

Board::Board(const Board& otherBoard) {
    // copy them pieaces
    std::copy(&otherBoard.pieces[0][0], &otherBoard.pieces[0][0] + 4 * 4, &pieces[0][0]);
    gameRhythmState = otherBoard.gameRhythmState;
}

bool Board::operator<(const Board& otherBoard) const {
    if (gameRhythmState == otherBoard.gameRhythmState) {
        // compare with board
        for (coord row = 0; row < 4; ++row) {
            for (coord column = 0; column < 4; ++column) {
                if (pieces[row][column].value == otherBoard.pieces[row][column].value) {
                    if (pieces[row][column].value != 0 &&
                        pieces[row][column].color != otherBoard.pieces[row][column].color) {
                        return pieces[row][column].color < otherBoard.pieces[row][column].color;
                    }
                } else {
                    return pieces[row][column].value < otherBoard.pieces[row][column].value;
                }
            }
        }
        return false;
    } else {
        // gameRhythmState is not equal, compare with that
        return gameRhythmState < otherBoard.gameRhythmState;
    }
}

GameRhythmState Board::getGameRhythmState() const {
    return gameRhythmState;
}

std::ostream& operator<<(std::ostream& ostream, const Board& board) {
    ostream << "{|" << std::endl;
    for (int row = 0; row < 4; ++row) {
        ostream << " |";
        for (int column = 0; column < 4; ++column) {
            ostream << " " << board.pieces[row][column] << " |";
        }
        ostream << std::endl;
    }
    ostream << " |}";
    return ostream;
}

Board& Board::setPiece(const Coords& coords, PieceColor color, unsigned short value /*= 1*/) {
    if (!pieces[coords.row][coords.column].empty()) {
        throw std::invalid_argument("Piece already exists on this spot");
    }
    pieces[coords.row][coords.column].value = value;
    pieces[coords.row][coords.column].color = color;
    ++gameRhythmState;
    return *this;
}

void Board::slide(SlideDirection direction) {
    switch (direction) {
        case SD_UP:
            slideUp();
            break;
        case SD_DOWN:
            slideDown();
            break;
        case SD_LEFT:
            slideLeft();
            break;
        case SD_RIGHT:
            slideRight();
            break;
    }
}

void Board::slideUp() {
    for (coord column = 0; column < 4; ++column) {
        Piece* localPieces[] = {&(pieces[0][column]), &(pieces[1][column]), &(pieces[2][column]), &(pieces[3][column])};
        slidePieces(localPieces);
    }
    ++gameRhythmState;
}

void Board::slideDown() {
    for (coord column = 0; column < 4; ++column) {
        Piece* localPieces[] = {&(pieces[3][column]), &(pieces[2][column]), &(pieces[1][column]), &(pieces[0][column])};
        slidePieces(localPieces);
    }
    ++gameRhythmState;
}

void Board::slideLeft() {
    for (coord row = 0; row < 4; ++row) {
        Piece* localPieces[] = {&pieces[row][0], &pieces[row][1], &pieces[row][2], &pieces[row][3]};
        slidePieces(localPieces);
    }
    ++gameRhythmState;
}

void Board::slideRight() {
    for (coord row = 0; row < 4; ++row) {
        Piece* localPieces[] = {&pieces[row][3], &pieces[row][2], &pieces[row][1], &pieces[row][0]};
        slidePieces(localPieces);
    }
    ++gameRhythmState;
}

void Board::doMove(const Move& move) {
    switch (gameRhythmState) {
        case GR_BLUE:
            setPiece(move.coords, BLUE);
            break;
        case GR_RED:
            setPiece(move.coords, RED);
            break;
        case GR_GREY:
            setPiece(move.coords, GREY);
            break;
        case GR_SLIDE1:
        case GR_SLIDE2:
            slide(move.direction);
            break;
    }
}

const Piece& Board::getPiece(const Coords& coords) const {
    return getPiece(coords.row, coords.column);
}

const Piece& Board::getPiece(coord row, coord column) const {
    return pieces[row][column];
}

bool Board::isSlideValid(const SlideDirection& slideDirection) const {
    switch (slideDirection) {
        case SD_UP:
            return isSlideUpValid();
        case SD_DOWN:
            return isSlideDownValid();
        case SD_LEFT:
            return isSlideLeftValid();
        case SD_RIGHT:
            return isSlideRightValid();
    }
    return false;
}

/* static */ void Board::slidePieces(Piece* pieces[]) {
    removeWhitespace(pieces);
    removeDuplicates(pieces);
    removeWhitespace(pieces);
}

/* static */ void Board::removeWhitespace(Piece* pieces[]) {
    for (coord i = 0; i < 4; ++i) {
        if (pieces[i]->empty()) {
            for (int j = i + 1; j < 4; ++j) {
                if (!pieces[j]->empty()) {
                    pieces[i]->replaceWith(*pieces[j]);
                    break;
                }
            }
        }
    }
}

/* static */ void Board::removeDuplicates(Piece* pieces[]) {
    for (coord i = 0; i < 3; ++i) {
        if (!pieces[i]->empty() && (pieces[i]->value == pieces[i + 1]->value)) {
            // is mergable, lets check how to merge
            if (pieces[i]->color == pieces[i + 1]->color) {
                pieces[i]->value *= 3;
            } else {
                pieces[i]->clear();
            }
            pieces[i + 1]->clear();
        }
    }
}

std::uint32_t Board::getBoardScore() const {
    std::uint32_t score = 0;
    for (coord row = 0; row < 3; ++row) {
        for (coord column = 0; column < 3; ++column) {
            score += pieces[row][column].value;
        }
    }
    return score;
}

bool Board::isSlideUpValid() const {
    for (coord column = 0; column < 4; ++column) {
        bool hasEmpty = false;
        for (coord row = 0; row < 4; ++row) {
            if (hasEmpty) {
                if (!getPiece(row, column).empty()) {
                    return true;
                }
            } else {
                if (getPiece(row, column).empty()) {
                    hasEmpty = true;
                }
            }
        }

        unsigned short lastValue = 0;
        for (coord row = 0; row < 4; ++row) {
            const Piece& p = getPiece(row, column);
            if (!p.empty() && p.value == lastValue) {
                return true;
            }
            lastValue = p.value;
        }
    }
    return false;
}

bool Board::isSlideDownValid() const {
    for (coord column = 0; column < 4; ++column) {
        bool hasEmpty = false;
        for (coord row = 4; row-- > 0;) {
            if (hasEmpty) {
                if (!getPiece(row, column).empty()) {
                    return true;
                }
            } else {
                if (getPiece(row, column).empty()) {
                    hasEmpty = true;
                }
            }
        }

        unsigned short lastValue = 0;
        for (coord row = 4; row-- > 0;) {
            const Piece& p = getPiece(row, column);
            if (!p.empty() && p.value == lastValue) {
                return true;
            }
            lastValue = p.value;
        }
    }
    return false;
}

bool Board::isSlideLeftValid() const {
    for (coord row = 0; row < 4; ++row) {
        bool hasEmpty = false;
        for (coord column = 0; column < 4; ++column) {
            if (hasEmpty) {
                if (!getPiece(row, column).empty()) {
                    return true;
                }
            } else {
                if (getPiece(row, column).empty()) {
                    hasEmpty = true;
                }
            }
        }

        unsigned short lastValue = 0;
        for (coord column = 0; column < 4; ++column) {
            const Piece& p = getPiece(row, column);
            if (!p.empty() && p.value == lastValue) {
                return true;
            }
            lastValue = p.value;
        }
    }
    return false;
}

bool Board::isSlideRightValid() const {
    for (coord row = 0; row < 4; ++row) {
        bool hasEmpty = false;
        for (coord column = 4; column-- > 0;) {
            if (hasEmpty) {
                if (!getPiece(row, column).empty()) {
                    return true;
                }
            } else {
                if (getPiece(row, column).empty()) {
                    hasEmpty = true;
                }
            }
        }

        unsigned short lastValue = 0;
        for (coord column = 4; column-- > 0;) {
            const Piece& p = getPiece(row, column);
            if (!p.empty() && p.value == lastValue) {
                return true;
            }
            lastValue = p.value;
        }
    }
    return false;
}

std::size_t Board::getValidMoves(Move validMoves[16]) const {
    std::size_t validMoveCounter = 0;
    if (gameRhythmStateIsSlide(gameRhythmState)) {
        // slide
        if (isSlideUpValid()) {
            validMoves[validMoveCounter].direction = SD_UP;
            ++validMoveCounter;
        }
        if (isSlideDownValid()) {
            validMoves[validMoveCounter].direction = SD_DOWN;
            ++validMoveCounter;
        }
        if (isSlideLeftValid()) {
            validMoves[validMoveCounter].direction = SD_LEFT;
            ++validMoveCounter;
        }
        if (isSlideRightValid()) {
            validMoves[validMoveCounter].direction = SD_RIGHT;
            ++validMoveCounter;
        }
    } else {
        // coords
        for (coord column = 0; column < 4; ++column) {
            for (coord row = 0; row < 4; ++row) {
                if (getPiece(row, column).empty()) {
                    validMoves[validMoveCounter].coords.row = row;
                    validMoves[validMoveCounter].coords.column = column;
                    ++validMoveCounter;
                }
            }
        }
    }
    return validMoveCounter;
}

const Piece* Board::getPieceByMaxValue(Coords& coords) const {
    const Piece* maxPiece = &pieces[coords.row][coords.column];
    for (coord column = 0; column < 4; ++column) {
        for (coord row = 0; row < 4; ++row) {
            if (pieces[row][column].value > maxPiece->value) {
                maxPiece = &pieces[row][column];
                coords.row = row;
                coords.column = column;
            }
        }
    }

    return maxPiece;
}

bool Board::getPieceByMinValue(Coords& coords, Coords* blacklist /* = nullptr */,
                               std::size_t blacklistSize /* = 0 */) const {
    unsigned short minValue = UINT16_MAX;

    for (coord column = 0; column < 4; ++column) {
        for (coord row = 0; row < 4; ++row) {
            if (pieces[row][column].empty()) {
                continue;
            }

            bool inBlackList = false;
            for (std::size_t i = 0; i < blacklistSize; ++i) {
                if(blacklist[i].row == row && blacklist[i].column == column) {
                    inBlackList = true;
                }
            }
            if (!inBlackList && pieces[row][column].value < minValue) {
                minValue = pieces[row][column].value;
                coords.row = row;
                coords.column = column;
            }
        }
    }

    return minValue != UINT16_MAX;
}

const Piece* Board::getPieceByColorAndValue(const PieceColor& color, unsigned short value, Coords& coords) const {
    for (coord column = 0; column < 4; ++column) {
        for (coord row = 0; row < 4; ++row) {
            if (pieces[row][column].color == color && pieces[row][column].value == value) {
                coords.row = row;
                coords.column = column;
                return &pieces[row][column];
            }
        }
    }

    return nullptr;
}

bool Board::isPieceEmpty(coord row, coord column) const {
    return pieces[row][column].empty();
}

bool Board::isPieceEmpty(const Coords& coords) const {
    return isPieceEmpty(coords.row, coords.column);
}

std::size_t Board::findAdjecentPiecesWithSameColor(const Coords& coords, PieceColor color,
                                                   AdjacentPieceInfo* adjacentPieces) const {
    std::size_t adjacentPiecesCount = 0;
    // check left
    if (coords.column > 0) {
        const Coords leftCoords = coords - Coords(0, 1);
        const Piece& leftPiece = getPiece(leftCoords);
        if (!leftPiece.empty() && leftPiece.color == color) {
            adjacentPieces[adjacentPiecesCount].adjacentPieceCoords = leftCoords;
            adjacentPieces[adjacentPiecesCount].adjacentPieceValue = leftPiece.value;
            adjacentPieces[adjacentPiecesCount].emptyAdjacentPlacesOfAdjacentPieceSize = findEmptyAdjacentPieces(
                    adjacentPieces[adjacentPiecesCount].emptyAdjacentPlacesOfAdjacentPiece, leftCoords);
            adjacentPiecesCount++;
        }
    }
    // check right
    if (coords.column < 3) {
        const Coords rightCoords = coords + Coords(0, 1);
        const Piece& rightPiece = getPiece(rightCoords);
        if (!rightPiece.empty() && rightPiece.color == color) {
            adjacentPieces[adjacentPiecesCount].adjacentPieceCoords = rightCoords;
            adjacentPieces[adjacentPiecesCount].adjacentPieceValue = rightPiece.value;
            adjacentPieces[adjacentPiecesCount].emptyAdjacentPlacesOfAdjacentPieceSize = findEmptyAdjacentPieces(
                    adjacentPieces[adjacentPiecesCount].emptyAdjacentPlacesOfAdjacentPiece, rightCoords);
            adjacentPiecesCount++;
        }
    }
    // check up
    if (coords.row > 0) {
        const Coords upCoords = coords - Coords(1, 0);
        const Piece& upPiece = getPiece(upCoords);
        if (!upPiece.empty() && upPiece.color == color) {
            adjacentPieces[adjacentPiecesCount].adjacentPieceCoords = upCoords;
            adjacentPieces[adjacentPiecesCount].adjacentPieceValue = upPiece.value;
            adjacentPieces[adjacentPiecesCount].emptyAdjacentPlacesOfAdjacentPieceSize = findEmptyAdjacentPieces(
                    adjacentPieces[adjacentPiecesCount].emptyAdjacentPlacesOfAdjacentPiece, upCoords);
            adjacentPiecesCount++;
        }
    }
    // check down
    if (coords.row < 3) {
        const Coords downCoords = coords + Coords(1, 0);
        const Piece& downPiece = getPiece(downCoords);
        if (!downPiece.empty() && downPiece.color == color) {
            adjacentPieces[adjacentPiecesCount].adjacentPieceCoords = downCoords;
            adjacentPieces[adjacentPiecesCount].adjacentPieceValue = downPiece.value;
            adjacentPieces[adjacentPiecesCount].emptyAdjacentPlacesOfAdjacentPieceSize = findEmptyAdjacentPieces(
                    adjacentPieces[adjacentPiecesCount].emptyAdjacentPlacesOfAdjacentPiece, downCoords);
            adjacentPiecesCount++;
        }
    }
    return adjacentPiecesCount;
}

size_t Board::findEmptyAdjacentPieces(Coords adjacentEmptyPieces[3], const Coords& coords) const {
    std::size_t adjacentPiecesCount = 0;
    // check left
    if (coords.column > 0) {
        const Coords& leftCoords = coords - Coords(0, 1);
        if (getPiece(leftCoords).empty()) {
            adjacentEmptyPieces[adjacentPiecesCount] = leftCoords;
            ++adjacentPiecesCount;
        }
    }
    // check right
    if (coords.column < 3) {
        const Coords& rightCoords = coords + Coords(0, 1);
        if (getPiece(rightCoords).empty()) {
            adjacentEmptyPieces[adjacentPiecesCount] = rightCoords;
            ++adjacentPiecesCount;
        }
    }
    // check up
    if (coords.row > 0) {
        const Coords& upCoords = coords - Coords(1, 0);
        if (getPiece(upCoords).empty()) {
            adjacentEmptyPieces[adjacentPiecesCount] = upCoords;
            ++adjacentPiecesCount;
        }
    }
    // check down
    if (coords.row < 3) {
        const Coords& downCoords = coords + Coords(1, 0);
        if (getPiece(downCoords).empty()) {
            adjacentEmptyPieces[adjacentPiecesCount] = downCoords;
            ++adjacentPiecesCount;
        }
    }
    return adjacentPiecesCount;
}
