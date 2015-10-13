//

#ifndef CODECUP_PIECE_H
#define CODECUP_PIECE_H

#include <ostream>

enum PieceColor {
    BLUE, RED, GREY
};

std::ostream& operator<<(std::ostream& ostream, const PieceColor& color);

class Piece {
public:
    Piece();
    Piece(const PieceColor& color, unsigned short value);

    friend std::ostream& operator<<(std::ostream& ostream, const Piece& piece);

    /**
     * Sets the color and value of this piece with the color and value of otherPiece AND clears otherPiece.
     */
    void replaceWith(Piece& otherPiece);

    bool empty() const;
    void clear();

    PieceColor color;
    unsigned short value;
};

#endif //CODECUP_PIECE_H
