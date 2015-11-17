#include "Move.h"
Move::Move() { }

Move::Move(const Coords& coords) : coords(coords) {
}

Move::Move(coord row, coord column) : coords(row, column){
}

Move::Move(const SlideDirection& direction) : direction(direction) {
}

