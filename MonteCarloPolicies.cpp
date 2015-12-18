#include "MonteCarloPolicies.h"

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
    return generateRandomNumber(validMovesCount-1);
}
