#include "GameRhythmState.h"

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