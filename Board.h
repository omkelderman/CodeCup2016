//

#ifndef CODECUP_BOARD_H
#define CODECUP_BOARD_H

#include "Piece.h"

typedef unsigned char coord;

enum SlideDirection {
    UP, DOWN, LEFT, RIGHT
};

std::ostream& operator<<(std::ostream& ostream, const SlideDirection& direction);
std::istream& operator>>(std::istream& istream, SlideDirection& direction);

class Board {
public:
    Board();

    Board& setPiece(coord x, coord y, PieceColor color, unsigned short value = 1);

    friend std::ostream& operator<<(std::ostream& ostream, const Board& board);

    void slide(SlideDirection direction);
    const Piece& getPiece(coord x, coord y) const;
private:
    Piece pieces[4][4];
    void slideUp();
    void slideDown();
    void slideLeft();
    void slideRight();

    /**
     * Array-size should be 4
     * Slides towards p0
     */
    static void slidePieces(Piece* pieces[]);
    static void removeWhitespace(Piece* pieces[]);
    static void removeDuplicates(Piece* pieces[]);
};


#endif //CODECUP_BOARD_H
