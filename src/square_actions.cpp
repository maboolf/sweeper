#include "square_actions.h"
#include "square.h"
#include "flood_fill.h"
#include <iostream>

bool squareClicked(std::vector<Square> &board, int index, bool gameRunning, int &numOfHiddenSquares, int WIDTH, int HEIGHT) {

    if (board[index].isMine) {
        std::cout << "\n\t\tGame over!" << std::endl; // temp
        gameRunning = false;
    } else {
        floodFill(board, index, numOfHiddenSquares, WIDTH, HEIGHT);
    }

    return gameRunning;
}

void squareFlagged(std::vector<Square> &board, int index, int &displayNumOfMines) {

    if (board[index].isHidden && !board[index].isFlagged) {

        board[index].isFlagged = true;
        displayNumOfMines--;
    
    } else if (board[index].isFlagged) {
        board[index].isFlagged = false;
        displayNumOfMines++;
    }
}
