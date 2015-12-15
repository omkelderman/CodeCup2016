#ifndef CODECUP_BOARD_H
#define CODECUP_BOARD_H

#include "Piece.h"
#include "Move.h"
#include "GameRhythmState.h"

class Board {
public:
    Board();
    Board(const Board& otherBoard);

    Board& operator=(const Board& otherBoard) = delete;

    GameRhythmState getGameRhythmState() const;

    Coords getLastMoveAsCoords() const;
    SlideDirection getLastMoveAsSlideDirection() const;

    Coords getSecondLastMoveAsCoords() const;
    SlideDirection getSecondLastMoveAsSlideDirection() const;

    friend std::ostream& operator<<(std::ostream& ostream, const Board& board);

    // do move methods
    Board& setPiece(const Coords& coords, PieceColor color, unsigned short value = 1);
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

    GameRhythmState gameRhythmState;

    Move lastTwoMoves[2];

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

    void addLastMove(const Move& move);
};


#endif //CODECUP_BOARD_H
