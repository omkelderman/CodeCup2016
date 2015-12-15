#include "Board.h"

#include <stdexcept>

Board::Board() :
        gameRhythmState(GR_BLUE) {
}

Board::Board(const Board& otherBoard) {
    // copy them pieaces
    std::copy(&otherBoard.pieces[0][0], &otherBoard.pieces[0][0] + 4 * 4, &pieces[0][0]);
    gameRhythmState = otherBoard.gameRhythmState;
    lastTwoMoves[0] = otherBoard.lastTwoMoves[0];
    lastTwoMoves[1] = otherBoard.lastTwoMoves[1];
}

GameRhythmState Board::getGameRhythmState() const {
    return gameRhythmState;
}

Coords Board::getLastMoveAsCoords() const {
    return lastTwoMoves[0].coords;
}

SlideDirection Board::getLastMoveAsSlideDirection() const {
    return lastTwoMoves[0].direction;
}

Coords Board::getSecondLastMoveAsCoords() const {
    return lastTwoMoves[1].coords;
}

SlideDirection Board::getSecondLastMoveAsSlideDirection() const {
    return lastTwoMoves[1].direction;
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
    addLastMove(coords);
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
    addLastMove(SD_UP);
}

void Board::slideDown() {
    for (coord column = 0; column < 4; ++column) {
        Piece* localPieces[] = {&(pieces[3][column]), &(pieces[2][column]), &(pieces[1][column]), &(pieces[0][column])};
        slidePieces(localPieces);
    }
    ++gameRhythmState;
    addLastMove(SD_DOWN);
}

void Board::slideLeft() {
    for (coord row = 0; row < 4; ++row) {
        Piece* localPieces[] = {&pieces[row][0], &pieces[row][1], &pieces[row][2], &pieces[row][3]};
        slidePieces(localPieces);
    }
    ++gameRhythmState;
    addLastMove(SD_LEFT);
}

void Board::slideRight() {
    for (coord row = 0; row < 4; ++row) {
        Piece* localPieces[] = {&pieces[row][3], &pieces[row][2], &pieces[row][1], &pieces[row][0]};
        slidePieces(localPieces);
    }
    ++gameRhythmState;
    addLastMove(SD_RIGHT);
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

void Board::addLastMove(const Move& move) {
    lastTwoMoves[1] = lastTwoMoves[0];
    lastTwoMoves[0] = move;
}
