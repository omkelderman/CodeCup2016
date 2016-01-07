#include <iostream>
#include "Game6561.h"
#include "MonteCarloTreeSearchAlgorithm.h"
#include "HeuristicAlgorithm.h"

int main() {

    try {
        HeuristicMonteCarloPolicy policy;
        MonteCarloTreeSearchAlgorithm algorithm(20000, 0, 300u, policy);
//        HeuristicAlgorithm algorithm;
        std::cerr << "START" << std::endl;
        Game6561 game(std::cin, std::cout, std::cerr, algorithm);
        game.run();
        std::cerr << "END" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Halp, exception: " << e.what() << std::endl;
    }

    return 0;
}
