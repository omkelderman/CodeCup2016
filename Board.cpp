#include "Board.h"

#include <stdexcept>
#include <iostream>

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
            ostream << 'E';
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

Board& Board::setPiece(coord x, coord y, PieceColor color, unsigned short value /*= 1*/) {
    if (!pieces[x][y].empty()) {
        throw std::logic_error("SHUT THE FUCK UP");
    }
    pieces[x][y].value = value;
    pieces[x][y].color = color;
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
    for (int y = 0; y < 4; ++y) {
        ostream << " |";
        for (int x = 0; x < 4; ++x) {
            ostream << " " << board.pieces[x][y] << " |";
        }
        ostream << std::endl;
    }
    ostream << " |}";
    return ostream;
}

const Piece& Board::getPiece(coord x, coord y) const {
    return pieces[x][y];
}

void Board::slideUp() {
    for (coord x = 0; x < 4; ++x) {
        Piece* localPieces[] = {&(pieces[x][0]), &(pieces[x][1]), &(pieces[x][2]), &(pieces[x][3])};
        slidePieces(localPieces);
    }
}

void Board::slideDown() {
    for (coord x = 0; x < 4; ++x) {
        Piece* localPieces[] = {&pieces[x][3], &pieces[x][2], &pieces[x][1], &pieces[x][0]};
        slidePieces(localPieces);
    }
}

void Board::slideLeft() {
    for (coord y = 0; y < 4; ++y) {
        Piece* localPieces[] = {&pieces[0][y], &pieces[1][y], &pieces[2][y], &pieces[3][y]};
        slidePieces(localPieces);
    }
}

void Board::slideRight() {
    for (coord y = 0; y < 4; ++y) {
        Piece* localPieces[] = {&pieces[3][y], &pieces[2][y], &pieces[1][y], &pieces[0][y]};
        slidePieces(localPieces);
    }
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
