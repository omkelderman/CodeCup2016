#ifndef CODECUP_BOARD_H
#define CODECUP_BOARD_H

#include "Piece.h"
#include "Move.h"
#include "GameRhythmState.h"
#include "AdjacentPieceInfo.h"

class Board {
public:
    Board();
    Board(const Board& otherBoard);

    Board& operator=(const Board& otherBoard) = delete;
    bool operator<(const Board& otherBoard) const;

    GameRhythmState getGameRhythmState() const;

    friend std::ostream& operator<<(std::ostream& ostream, const Board& board);

    // do move methods
    Board& setPiece(const Coords& coords, PieceColor color, unsigned short value = 1);
    void slide(SlideDirection direction);
    void slideUp();
    void slideDown();
    void slideLeft();
    void slideRight();
    void doMove(const Move& move);

    const Piece& getPiece(const Coords& coords) const;
    const Piece& getPiece(coord row, coord column) const;
    bool isSlideValid(const SlideDirection& slideDirection) const;

    std::size_t getValidMoves(Move validMoves[16]) const;

    std::uint32_t getBoardScore() const;

    /**
     * Get the piece with the max value, if no pieces found, piece on the coords 'Coords' will be returned
     * @param coords A coords object to store the coordinates of the found piece, or the coordinates used if board is empty
     * @return A pointer to the found piece, or a pointer to empty piece on coordinates coords
     */
    const Piece* getPieceByMaxValue(Coords& coords) const;

    /**
     * Get the coords of the piece with the lowest value
     * @param coords A coords object to store the coordinates of the found piece
     * @return true if found, false if not found (so board is empty)
     */
    bool getPieceByMinValue(Coords& coords, Coords* blacklist = nullptr, std::size_t blacklistSize = 0) const;

    /**
     * Search a piece by color and value
     * @param coords A coords object to store the coordinates of the found piece
     * @return the found piece or nullptr if not found
     */
    const Piece* getPieceByColorAndValue(const PieceColor& color, unsigned short value, Coords& coords) const;
    bool isPieceEmpty(coord row, coord column) const;
    bool isPieceEmpty(const Coords& coords) const;

    std::size_t findAdjecentPiecesWithSameColor(const Coords& coords, PieceColor color,
                                                AdjacentPieceInfo adjacentPieces[4]) const;
    size_t findEmptyAdjacentPieces(Coords adjacentEmptyPieces[3], const Coords& coords) const;

private:
    /**
     * pieces[rows][columns]
     */
    Piece pieces[4][4];

    GameRhythmState gameRhythmState;

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
