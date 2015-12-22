#include "GameRhythmState.h"

bool gameRhythmStateIsSlide(const GameRhythmState& gameRhythmState) {
    return gameRhythmState == GR_SLIDE1 || gameRhythmState == GR_SLIDE2;
}

bool gameRhythmStateEqualsColor(const GameRhythmState& gameRhythmState, PieceColor color) {
    switch (gameRhythmState) {

        case GR_BLUE:
            return color == BLUE;
        case GR_RED:
            return color == RED;
        case GR_GREY:
            return color == GREY;
        default:
            return false;
    }
}

GameRhythmState& operator++(GameRhythmState& gameRhythmState) {
    switch (gameRhythmState) {
        case GR_BLUE:
            gameRhythmState = GR_RED;
            break;
        case GR_RED:
            gameRhythmState = GR_GREY;
            break;
        case GR_GREY:
            gameRhythmState = GR_SLIDE1;
            break;
        case GR_SLIDE1:
            gameRhythmState = GR_SLIDE2;
            break;
        case GR_SLIDE2:
            gameRhythmState = GR_BLUE;
            break;
    }
    return gameRhythmState;
}

GameRhythmState operator++(GameRhythmState& gameRhythmState, int) {
    GameRhythmState tmp(gameRhythmState);
    ++gameRhythmState;
    return tmp;
}
