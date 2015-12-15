#ifndef CODECUP_GAMERHYTHMSTATE_H
#define CODECUP_GAMERHYTHMSTATE_H

/**
 * An enumeration to keep track of the Rhythm, applied in the 6561 game.
 * This "rhythm" decides what to do in the current turn.
 */
enum GameRhythmState {
    GR_BLUE, GR_RED, GR_GREY, GR_SLIDE1, GR_SLIDE2
};

GameRhythmState& operator++(GameRhythmState& gameRhythmState);

GameRhythmState operator++(GameRhythmState& gameRhythmState, int);

#endif //CODECUP_GAMERHYTHMSTATE_H
