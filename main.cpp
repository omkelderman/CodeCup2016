#include <iostream>
#include <stdexcept>
#include "Game6561.h"
#include "MonteCarloAlgorithm.h"
#include "MonteCarloTreeSearchAlgorithm.h"

//void test();

int main() {

//    test();
    try {
        MonteCarloTreeSearchAlgorithm algorithm(100000, 1.4);
        std::cerr << "START" << std::endl;
        Game6561 game(std::cin, std::cout, std::cerr, algorithm);
        game.run();
        std::cerr << "END" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Halp, exception: " << e.what() << std::endl;
    }

    return 0;
}


//#include "Board.h"
//void test() {
//    Board b;
//    b.setPiece(2, 3, GREY, 9);
//    b.setPiece(3, 1, BLUE, 1);
//    b.setPiece(3, 2, GREY, 1);
//    b.setPiece(3, 3, RED, 1);
//    std::cout << b.isSlideValid(SD_DOWN) << std::endl;
//
//}