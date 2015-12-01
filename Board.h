#ifndef CODECUP_BOARD_H
#define CODECUP_BOARD_H

#include "Piece.h"

typedef unsigned char coord;

struct Coords {
    coord row;
    coord column;

    Coords(coord row, coord column);

    bool operator==(const Coords& coords);
};

enum SlideDirection {
    UP, DOWN, LEFT, RIGHT
};

std::ostream& operator<<(std::ostream& ostream, const Coords& coords);
std::ostream& operator<<(std::ostream& ostream, const SlideDirection& direction);
std::istream& operator>>(std::istream& istream, SlideDirection& direction);

class Board {
public:
    Board();
    Board(const Board& board);

    Board& operator=(const Board& board) = delete;

    Board& setPiece(coord row, coord column, PieceColor color, unsigned short value = 1);

    friend std::ostream& operator<<(std::ostream& ostream, const Board& board);

    void slide(SlideDirection direction);
    void slideUp();
    void slideDown();
    void slideLeft();
    void slideRight();
    const Piece& getPiece(coord row, coord column) const;

    bool isSlideValid(const SlideDirection& slideDirection) const;

    std::uint32_t getBoardScore() const;
private:
    /**
     * pieces[rows][columns]
     */
    Piece pieces[4][4];

    /**
     * Array-size should be 4
     * Slides towards p0
     */
    static void slidePieces(Piece* pieces[]);
    static void removeWhitespace(Piece* pieces[]);
    static void removeDuplicates(Piece* pieces[]);

    bool isSlideUpValid() const;
    bool isSlideDownValid() const;
    bool isSlideLeftValid() const;
    bool isSlideRightValid() const;
};


#endif //CODECUP_BOARD_H
