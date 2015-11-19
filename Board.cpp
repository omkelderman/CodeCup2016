#include "Board.h"

#include <stdexcept>
#include <iostream>

Coords::Coords(coord row, coord column) :
        row(row), column(column) {
}

bool Coords::operator==(const Coords& coords) {
    return row == coords.row && column == coords.column;
}

std::ostream& operator<<(std::ostream& ostream, const Coords& coords) {
    ostream << '[' << ((int) coords.row) << ',' << ((int) coords.column) << ']';
    return ostream;
}

std::ostream& operator<<(std::ostream& ostream, const SlideDirection& direction) {
    switch (direction) {
        case UP:
            ostream << 'U';
            break;
        case DOWN:
            ostream << 'D';
            break;
        case LEFT:
            ostream << 'L';
            break;
        case RIGHT:
            ostream << 'R';
            break;
    }
    return ostream;
}

std::istream& operator>>(std::istream& istream, SlideDirection& direction) {
    char c;
    istream >> c;
    switch (c) {
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
            // I don't f*cking know
            break;
    }
    return istream;
}

Board::Board() {
}

Board& Board::setPiece(coord row, coord column, PieceColor color, unsigned short value /*= 1*/) {
    if (!pieces[row][column].empty()) {
        throw std::invalid_argument("Piece already exists on this spot");
    }
    pieces[row][column].value = value;
    pieces[row][column].color = color;
    return *this;
}

void Board::slide(SlideDirection direction) {
    switch (direction) {
        case UP:
            slideUp();
            break;
        case DOWN:
            slideDown();
            break;
        case LEFT:
            slideLeft();
            break;
        case RIGHT:
            slideRight();
            break;
    }
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

const Piece& Board::getPiece(coord row, coord column) const {
    return pieces[row][column];
}

void Board::slideUp() {
    for (coord column = 0; column < 4; ++column) {
        Piece* localPieces[] = {&(pieces[0][column]), &(pieces[1][column]), &(pieces[2][column]), &(pieces[3][column])};
        slidePieces(localPieces);
    }
}

void Board::slideDown() {
    for (coord column = 0; column < 4; ++column) {
        Piece* localPieces[] = {&(pieces[3][column]), &(pieces[2][column]), &(pieces[1][column]), &(pieces[0][column])};
        slidePieces(localPieces);
    }
}

void Board::slideLeft() {
    for (coord row = 0; row < 4; ++row) {
        Piece* localPieces[] = {&pieces[row][0], &pieces[row][1], &pieces[row][2], &pieces[row][3]};
        slidePieces(localPieces);
    }
}

void Board::slideRight() {
    for (coord row = 0; row < 4; ++row) {
        Piece* localPieces[] = {&pieces[row][3], &pieces[row][2], &pieces[row][1], &pieces[row][0]};
        slidePieces(localPieces);
    }
}

bool Board::isSlideValid(const SlideDirection& slideDirection) const {
    switch (slideDirection) {
        case UP:
            return isSlideUpValid();
        case DOWN:
            return isSlideDownValid();
        case LEFT:
            return isSlideLeftValid();
        case RIGHT:
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
        for (coord row = 4; row-- > 0; ) {
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
        for (coord row = 4; row-- > 0; ) {
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
        for (coord column = 4; column-- > 0; ) {
            const Piece& p = getPiece(row, column);
            if (!p.empty() && p.value == lastValue) {
                return true;
            }
            lastValue = p.value;
        }
    }
    return false;
}
