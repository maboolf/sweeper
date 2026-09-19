#include "board.h"
#include "neighbouring_checks.h"
#include <random>

std::random_device rnd;
std::mt19937 rng(rnd());
std::uniform_int_distribution<std::mt19937::result_type> dist(0, (WIDTH * HEIGHT - 1));

std::vector<Square> buildBoard(int &gameNumOfMines, int &displayNumOfMines) {   // builds board at
                                                                                // start of game
    std::vector<Square> board;

    for (int y = 0; y < HEIGHT; y++) {

        for (int x = 0; x < WIDTH; x++) {

            board.push_back({true, 0, false, false});
        }
    }

    for (int i = 0; i < (WIDTH * HEIGHT / DIFFICULTY); i++) {

        int index = dist(rng);
        board[index].isMine = true;

        gameNumOfMines++;
        displayNumOfMines++;
    }

    return board;
}

void preCalculateBorderingMines(std::vector<Square> &board) {   // calculates all squares' bordering
                                                                // mines count before game start

    for (int index = 0; index < (WIDTH * HEIGHT - 1); index++) {

        board[index].numOfBorderingMines = checkForNeighbouringMines(board, index);
    }
}