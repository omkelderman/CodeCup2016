#include "Move.h"
Move::Move() { }

Move::Move(const Coords& coords) : coords(coords) {
}

Move::Move(coord row, coord column) : coords(row, column){
}

Move::Move(const SlideDirection& direction) : direction(direction) {
}

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
        case SD_UP:
            ostream << 'U';
            break;
        case SD_DOWN:
            ostream << 'D';
            break;
        case SD_LEFT:
            ostream << 'L';
            break;
        case SD_RIGHT:
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
            direction = SD_UP;
            break;
        case 'D':
            direction = SD_DOWN;
            break;
        case 'L':
            direction = SD_LEFT;
            break;
        case 'R':
            direction = SD_RIGHT;
            break;
        default:
            // I don't f*cking know
            break;
    }
    return istream;
}