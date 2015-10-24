#include "Board.h"

#include <iostream>
#include "Game6561.h"
#include "TestAlgorithm.h"

int main() {
//    Board board;
//
//    board.setPiece(1, 0, GREY).setPiece(3, 0, RED, 9)
//            .setPiece(0, 1, RED, 3).setPiece(1, 1, BLUE).setPiece(2, 1, BLUE, 9).setPiece(3, 1, GREY, 3)
//            .setPiece(0, 2, RED, 3).setPiece(1, 2, BLUE).setPiece(3, 2, GREY)
//            .setPiece(0, 3, BLUE, 3).setPiece(1, 3, RED).setPiece(2, 3, BLUE, 9).setPiece(3, 3, GREY);
//
//
//    std::cout << board << std::endl;
//    board.slide(UP);
//    std::cout << board << std::endl;
    TestAlgorithm algorithm;
    std::cerr << "START" << std::endl;
    Game6561 game(std::cin, std::cout, algorithm);
    game.run();
    std::cerr << "END" << std::endl;

    return 0;
}