#include "Piece.h"

#include <iomanip>

std::ostream& operator<<(std::ostream& ostream, const PieceColor& color) {
    switch (color) {
        case BLUE:
            ostream << "B";
            break;
        case RED:
            ostream << "R";
            break;
        case GREY:
            ostream << "G";
            break;
    }
    return ostream;
}

Piece::Piece() :
        color(GREY), value(0) {
    // bleh default color, as long as value is 0 color is "invalid"
}

Piece::Piece(const PieceColor& color, unsigned short value) :
        color(color), value(value) {
}

std::ostream& operator<<(std::ostream& ostream, const Piece& piece) {
    if (piece.empty()) {
        ostream << "     ";
    } else {
        ostream << piece.color << std::setw(4) << piece.value;
    }
    return ostream;
}

void Piece::replaceWith(Piece& otherPiece) {
    color = otherPiece.color;
    value = otherPiece.value;
    otherPiece.clear();
}

bool Piece::empty() const {
    return value == 0;
}

void Piece::clear() {
    value = 0;
}
