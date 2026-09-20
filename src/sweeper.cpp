#include <vector>
#include "square.h" // TEMP
#include "board.h"
#include "square_actions.h"

#include <iostream> // TEMPORARY

// ----------------------------------------------------------------------------
// WIDTH, HEIGHT, AND DIFFICULTY WILL BE SOMEHOW HANDLED BY GUI WITH BUTTONS.
// ----------------------------------------------------------------------------

int WIDTH = 16;
int HEIGHT = 16;

int getIndexFromYX(int yCoordinate, int xCoordinate) {          // useful for GUI clicks? idk

    int index = yCoordinate * WIDTH + xCoordinate;

    return index;
}

// ################################ TEMP VISUALISATION FUNCTIONS ###################################

char getSquareChar(Square square, bool gameRunning) {

    const char squareChars[] = " 12345678";
    char squareChar;

    if (square.isFlagged) {
        squareChar = 'F';

    } else if (! square.isHidden) {

        if (!square.isMine && square.numOfBorderingMines > 0) {
            squareChar = squareChars[square.numOfBorderingMines];

        } else if (!square.isMine && square.numOfBorderingMines == 0) {
            squareChar = '.';
        }

    } else {
        squareChar = '#';
    }

    if (!gameRunning) {
        if (square.isMine) {
            squareChar = '*';
        }
    }

    return squareChar;
}

void drawBoard(std::vector<Square> board, bool gameRunning, int WIDTH, int HEIGHT) {

    for (int y = 0; y < HEIGHT; y++) {

        std::cout << "\n";

        for (int x = 0; x < WIDTH; x++) {

            char squareChar = getSquareChar(board[getIndexFromYX(y, x)], gameRunning);

            std::cout << "  " << squareChar;
        }

    }

    std::cout << std::endl;
}

// ############################################ MAIN ###############################################

int main() {

    bool gameRunning = true;

    int gameNumOfMines = 0;
    int displayNumOfMines = 0;
    int numOfHiddenSquares = WIDTH * HEIGHT;

    std::vector<Square> board = buildBoard(gameNumOfMines, displayNumOfMines);
    preCalculateBorderingMines(board);

    while (gameRunning) {

        std::cout << "\n\t\tRemaining mines: " << displayNumOfMines << std::endl;

        drawBoard(board, gameRunning, WIDTH, HEIGHT);

        std::cout << "\n\tPlease input what you would like to do."
                  << "\n\t\t'1' to dig, or '2' to flag.\t" << std::endl;

        char userIn;
        std::cin >> userIn;

        int yIn;
        int xIn;

        if (userIn == '1') {

            std::cout << "\n\tWhere would you like to dig?"
                      << "\n\tIf the top left is (0, 0), (y, x), input your y value:\t"
                      << std::endl;
            std::cin >> yIn;
            std::cout << "\n\tNow, please input your x-value:\t"
                      << std::endl;
            std::cin >> xIn;

            gameRunning = squareClicked(board, getIndexFromYX(yIn, xIn), gameRunning, numOfHiddenSquares, WIDTH, HEIGHT);
        
        } else if (userIn == '2') {

            std::cout << "\n\tWhere would you like to flag?"
                      << "\n\tIf the top left is (0, 0), (y, x), input your y value:\t"
                      << std::endl;
            std::cin >> yIn;
            std::cout << "\n\tNow, please input your x-value:\t"
                      << std::endl;
            std::cin >> xIn;

            squareFlagged(board, getIndexFromYX(yIn, xIn), displayNumOfMines);
        }

        if (numOfHiddenSquares == gameNumOfMines) {
            std::cout << "\n\t\tYou win!" << std::endl;
            gameRunning = false;
        }
    }

    drawBoard(board, gameRunning, WIDTH, HEIGHT);

    return 0;
}