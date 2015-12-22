#include "MonteCarloPolicies.h"
#include "GameException.h"

RandomMonteCarloPolicy::RandomMonteCarloPolicy() {
    // seed the random generator with a (hopefully) non-deterministic random number
#ifdef DEBUG_BUILD
    randomGenerator.seed(69);
#else
#ifdef _WIN32
    randomGenerator.seed((unsigned)time(nullptr));
#else
    std::random_device rd;
    randomGenerator.seed(rd());
#endif
#endif
}

std::size_t RandomMonteCarloPolicy::getNextMove(const Board&, Move*, std::size_t validMovesCount) {
    return generateRandomNumber(validMovesCount - 1);
}

std::size_t HeuristicMonteCarloPolicy::getNextMove(const Board& board, Move* validMoves, std::size_t validMovesCount) {
    if (gameRhythmStateIsSlide(board.getGameRhythmState())) {
        return getNextSlideMove(board, validMoves, validMovesCount);
    } else {
        return getNextCoordsMove(board, validMoves, validMovesCount);
    }
}

std::size_t HeuristicMonteCarloPolicy::getNextSlideMove(const Board& board, Move* validMoves,
                                                        std::size_t validMovesCount) {
    Board boardsAfterSlide[4] = {board, board, board, board};
    for (std::size_t i = 0; i < validMovesCount; ++i) {
        boardsAfterSlide[i].slide(validMoves[i].direction);
    }
    std::size_t theChoosenSlideIndex = 0;
    std::uint32_t maxScore = 0;
    for (std::size_t i = 0; i < validMovesCount; ++i) {
        uint32_t boardScore = boardsAfterSlide[i].getBoardScore();
        if (boardScore > maxScore) {
            maxScore = boardScore;
            theChoosenSlideIndex = i;
        }
    }
    return theChoosenSlideIndex;
}

std::size_t HeuristicMonteCarloPolicy::getNextCoordsMove(const Board& board, Move* validMoves,
                                                         std::size_t validMovesCount) {
    Coords maxPieceCoords;
    const Piece* maxPiece = board.getPieceByMaxValue(maxPieceCoords);
    PieceColor color = maxPiece->empty() ? GREY : maxPiece->color;

    if (gameRhythmStateEqualsColor(board.getGameRhythmState(), color)) {
        // get adjacent piece
        AdjacentPieceInfo adjacentPieces[4];
        std::size_t adjacentPiecesSize = board.findAdjecentPiecesWithSameColor(maxPieceCoords, color, adjacentPieces);

        if (adjacentPiecesSize > 0) {
            // check for values 1
            for (std::size_t i = 0; i < adjacentPiecesSize; ++i) {
                if (adjacentPieces[i].adjacentPieceValue == 1 &&
                    adjacentPieces[i].emptyAdjacentPlacesOfAdjacentPieceSize > 0) {
                    // value correct and has empty adjecent piece
                    return getIndexOfMove(validMoves, validMovesCount, adjacentPieces[i].emptyAdjacentPlacesOfAdjacentPiece[0]);
                }
            }

            // check for values 3
            for (std::size_t i = 0; i < adjacentPiecesSize; ++i) {
                if (adjacentPieces[i].adjacentPieceValue == 3 &&
                    adjacentPieces[i].emptyAdjacentPlacesOfAdjacentPieceSize > 0) {
                    // value correct and has empty adjecent piece
                    return getIndexOfMove(validMoves, validMovesCount, adjacentPieces[i].emptyAdjacentPlacesOfAdjacentPiece[0]);
                }
            }

            // check for empty spot on the walls of the board
            // check left
            if (board.isPieceEmpty(0, maxPieceCoords.row)) {
                return getIndexOfMove(validMoves, validMovesCount, {0, maxPieceCoords.row});
            }
            // check right
            if (board.isPieceEmpty(3, maxPieceCoords.row)) {
                return getIndexOfMove(validMoves, validMovesCount, {3, maxPieceCoords.row});
            }
            // check up
            if (board.isPieceEmpty(maxPieceCoords.column, 0)) {
                return getIndexOfMove(validMoves, validMovesCount, {maxPieceCoords.column, 0});
            }
            // check down
            if (board.isPieceEmpty(maxPieceCoords.column, 3)) {
                return getIndexOfMove(validMoves, validMovesCount, {maxPieceCoords.column, 3});
            }
        }

        Coords blacklist[16];
        std::size_t blacklistSize = 0;
        Coords coords;
        while (board.getPieceByMinValue(coords, blacklist, blacklistSize)) {
            Coords adjacentEmptyPieces[3];
            if (board.findEmptyAdjacentPieces(adjacentEmptyPieces, coords) == 0) {
                blacklist[blacklistSize] = coords;
                ++blacklistSize;
            } else {
                return getIndexOfMove(validMoves, validMovesCount, adjacentEmptyPieces[0]);
            }
        }

        throw GameException(
                "HeuristicMonteCarloPolicy::getNextCoordsMove --> board is full, wtf caia go home ur drunk");
    } else {
        PieceColor otherJunkColor = determineOtherJunkColor(board.getGameRhythmState(), color);
        Coords otherJunkColorPieceCoords;
        const Piece* otherJunkColorPiece = board.getPieceByColorAndValue(otherJunkColor, 1, otherJunkColorPieceCoords);

        // If piece with "otherJunkColor" has been found, try to place piece adjacent to it
        // TODO this is crap
        if (otherJunkColorPiece) {
            if (otherJunkColorPieceCoords.column > 0 &&
                board.isPieceEmpty(otherJunkColorPieceCoords - Coords(0, 1))) {
                return getIndexOfMove(validMoves, validMovesCount, otherJunkColorPieceCoords - Coords(0, 1));
            } else if (otherJunkColorPieceCoords.column < 3 &&
                       board.isPieceEmpty(otherJunkColorPieceCoords + Coords(0, 1))) {
                return getIndexOfMove(validMoves, validMovesCount, otherJunkColorPieceCoords + Coords(0, 1));
            } else if (otherJunkColorPieceCoords.row > 0 &&
                       board.isPieceEmpty(otherJunkColorPieceCoords - Coords(1, 0))) {
                return getIndexOfMove(validMoves, validMovesCount, otherJunkColorPieceCoords - Coords(1, 0));
            } else if (otherJunkColorPieceCoords.row < 3 &&
                       board.isPieceEmpty(otherJunkColorPieceCoords + Coords(1, 0))) {
                return getIndexOfMove(validMoves, validMovesCount, otherJunkColorPieceCoords + Coords(1, 0));
            }
        }

        // No different colored junk tile, or placement failed?
        // Try placing mirrored to highest non-junk tile (cluster core)
        if (!maxPiece->empty()) {
            Coords mirroredCoords = maxPieceCoords.mirror();
            if (board.isPieceEmpty(mirroredCoords)) {
                return getIndexOfMove(validMoves, validMovesCount, mirroredCoords);
            }
        }

        // No cluster core or mirroring failed?
        // try placing in the middle 4 tiles
        for (coord row = 1; row < 3; ++row) {
            for (coord column = 1; column < 3; ++column) {
                if (board.isPieceEmpty(row, column)) {
                    return getIndexOfMove(validMoves, validMovesCount, {row, column});
                }
            }
        }

        // Failed?
        // Place at a free spot.
        for (coord row = 0; row < 4; ++row) {
            for (coord column = 0; column < 4; ++column) {
                if (board.isPieceEmpty(row, column)) {
                    return getIndexOfMove(validMoves, validMovesCount, {row, column});
                }
            }
        }

        throw GameException("HeuristicMonteCarloPolicy::getNextCoordsMove --> no possible move available");
    }
}

std::size_t HeuristicMonteCarloPolicy::getIndexOfMove(Move* validMoves, std::size_t validMovesCount,
                                                      const Coords& coords) {
    for (std::size_t i = 0; i < validMovesCount; ++i) {
        if (validMoves[i].coords == coords) {
            return i;
        }
    }
    throw GameException("the choosen move was not found in the valid moves list.... rip");
}

PieceColor HeuristicMonteCarloPolicy::determineOtherJunkColor(const GameRhythmState& rhythmColor,
                                                              const PieceColor& color) {
    if (rhythmColor == GR_RED) {
        if (color == BLUE) {
            return GREY;
        } else {
            return BLUE;
        }
    } else if (rhythmColor == GR_BLUE) {
        if (color == RED) {
            return GREY;
        } else {
            return RED;
        }
    } else {
        if (color == BLUE) {
            return RED;
        } else {
            return BLUE;
        }
    }
}
