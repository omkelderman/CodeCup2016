#include <iostream>
#include "Game6561.h"
#include "MonteCarloTreeSearchAlgorithm.h"

int main() {

    try {
        MonteCarloTreeSearchAlgorithm algorithm(20000, 2);
        std::cerr << "START" << std::endl;
        Game6561 game(std::cin, std::cout, std::cerr, algorithm);
        game.run();
        std::cerr << "END" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Halp, exception: " << e.what() << std::endl;
    }

    return 0;
}
