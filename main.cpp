#include "Board.h"

#include <iostream>
#include <stdexcept>
#include "Game6561.h"
#include "TestAlgorithm.h"

int main() {
    try {
        TestAlgorithm algorithm;
        std::cerr << "START" << std::endl;
        Game6561 game(std::cin, std::cout, algorithm);
        game.run();
        std::cerr << "END" << std::endl;
    } catch (const std::logic_error& e){
        std::cerr << "Halp, exception kutjes: " << e.what() << std::endl;
    }

    return 0;
}