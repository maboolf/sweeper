#include <vector>
#include <random>

// ######## TEMP ###########

#include <iostream>

// ######## END TEMP #######

// ----------------------------------------------------------------------------
// WIDTH, HEIGHT, AND DIFFICULTY WILL BE SOMEHOW HANDLED BY GUI WITH BUTTONS.
// ----------------------------------------------------------------------------

#define WIDTH 16            // num of squares vertically, must be > 7
#define HEIGHT 16           // num of squares horizontally, must be > 7

#define DIFFICULTY 8
#define BOTTOMLEFT WIDTH*HEIGHT-WIDTH

std::random_device rnd;
std::mt19937 rng(rnd());
std::uniform_int_distribution<std::mt19937::result_type> dist(0, (WIDTH * HEIGHT - 1));
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ random num gen thing for mines

int width = 16;
int height = 16;

struct Square {                 // template for a square

    bool isHidden;              // state(s)

    int numOfBorderingMines;    // attributes
    bool isMine;
    bool isFlagged;
};


int getYCoordinateFromIndex(int index) {    // divides index by height to see how many times it 
                                            // fits, ignoring any nums past decimal point. this 
                                            // gives the y coord.
    int yCoordinate = index / HEIGHT;

    return yCoordinate;
}

int getXCoordinateFromIndex(int index) {    // pretty self explanatory, I'd have thought

    int xCoordinate = index % WIDTH;

    return xCoordinate;
}

int checkForNeighbouringMines(std::vector<Square> board, int index) {

    int numOfBorderingMines = 0;

    bool hasUp      = false;
    bool hasDown    = false;
    bool hasLeft    = false;
    bool hasRight   = false;

    if (getYCoordinateFromIndex(index) - 1 >= 0) {
        hasUp = true;

        if (board[index - WIDTH].isMine) {
            numOfBorderingMines++;
        }
    }
    if (getYCoordinateFromIndex(index) + 1 <= HEIGHT - 1) {
        hasDown = true;

        if (board[index + WIDTH].isMine) {
            numOfBorderingMines++;
        }
    }
    if (getXCoordinateFromIndex(index) - 1 >= 0) {
        hasLeft = true;

        if (board[index - 1].isMine) {
            numOfBorderingMines++;
        }
    }
    if (getXCoordinateFromIndex(index) + 1 <= WIDTH - 1) {
        hasRight = true;

        if (board[index + 1].isMine) {
            numOfBorderingMines++;
        }
    }

    if (hasUp && hasLeft) {
        if (board[index - WIDTH - 1].isMine) {
            numOfBorderingMines++;
        }
    }
    if (hasUp && hasRight) {
        if (board[index - WIDTH + 1].isMine) {
            numOfBorderingMines++;
        }
    }

    if (hasDown && hasLeft) {
        if (board[index + WIDTH - 1].isMine) {
            numOfBorderingMines++;
        }
    }
    if (hasDown && hasRight) {
        if (board[index + WIDTH + 1].isMine) {
            numOfBorderingMines++;
        }
    }

    return numOfBorderingMines;
}

bool checkForNeighbouringRevealed(std::vector<Square> board, int index) {

    bool neighboursRevealed = false;

    bool hasUp      = false;
    bool hasDown    = false;
    bool hasLeft    = false;
    bool hasRight   = false;

    if (getYCoordinateFromIndex(index) - 1 >= 0) {
        hasUp = true;

        if (!board[index - WIDTH].isHidden) {
            neighboursRevealed = true;
        }
    }
    if (getYCoordinateFromIndex(index) + 1 <= HEIGHT - 1) {
        hasDown = true;

        if (!board[index + WIDTH].isHidden) {
            neighboursRevealed = true;
        }
    }
    if (getXCoordinateFromIndex(index) - 1 >= 0) {
        hasLeft = true;

        if (!board[index - 1].isHidden) {
            neighboursRevealed = true;
        }
    }
    if (getXCoordinateFromIndex(index) + 1 <= WIDTH - 1) {
        hasRight = true;

        if (!board[index + 1].isHidden) {
            neighboursRevealed = true;
        }
    }

    if (hasUp && hasLeft) {
        if (!board[index - WIDTH - 1].isHidden) {
            neighboursRevealed = true;
        }
    }
    if (hasUp && hasRight) {
        if (!board[index - WIDTH + 1].isHidden) {
            neighboursRevealed = true;
        }
    }

    if (hasDown && hasLeft) {
        if (!board[index + WIDTH - 1].isHidden) {
            neighboursRevealed = true;
        }
    }
    if (hasDown && hasRight) {
        if (!board[index + WIDTH + 1].isHidden) {
            neighboursRevealed = true;
        }
    }

    return neighboursRevealed;
}

std::vector<Square> buildBoard(int &gameNumOfMines, int &displayNumOfMines) {  // builds board 
                                                                                    // at start of 
                                                                                    // game
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

void drawBoard(std::vector<Square> board, bool gameRunning) {

    for (int y = 0; y < HEIGHT; y++) {

        std::cout << "\n";

        for (int x = 0; x < WIDTH; x++) {

            char squareChar = getSquareChar(board[getIndexFromYX(y, x)], gameRunning);

            std::cout << "  " << squareChar;
        }

    }

    std::cout << std::endl;
}

// ################################### NORMAL FUNCTIONS ############################################

void floodFill(std::vector<Square> &board, int index, int &numOfHiddenSquares) {

    if (board[index].isFlagged) {
        return;
    }

    std::vector<int> squareStack;       // create square stack for flood fill and add current
    squareStack.push_back(index);       // index to the stack

    if (!board[index].isMine && board[index].numOfBorderingMines > 0) {

        board[index].isHidden = false;
        return;
    }

    while (squareStack.size() > 0) {

        board[index].isHidden = false;
        numOfHiddenSquares--;

        bool hasUp      = false;
        bool hasDown    = false;
        bool hasLeft    = false;
        bool hasRight   = false;

        if (getYCoordinateFromIndex(index) - 1 >= 0) {
            hasUp = true;
        }

        if (getYCoordinateFromIndex(index) + 1 <= HEIGHT - 1) {
            hasDown = true;
        }

        if (getXCoordinateFromIndex(index) - 1 >= 0) {
            hasLeft = true;
        }

        if (getXCoordinateFromIndex(index) + 1 <= WIDTH - 1) {
            hasRight = true;
        }

        if (hasUp) {

            if (!board[index - WIDTH].isMine && board[index - WIDTH].isHidden && !board[index - WIDTH].isFlagged) {

                if (board[index - WIDTH].numOfBorderingMines == 0) {

                    squareStack.push_back(index - WIDTH);

                } else {
                    board[index - WIDTH].isHidden = false;
                    numOfHiddenSquares--;
                }
            }
        }

        if (hasDown) {

            if (!board[index + WIDTH].isMine && board[index + WIDTH].isHidden && !board[index + WIDTH].isFlagged) {

                if (board[index + WIDTH].numOfBorderingMines == 0) {

                    squareStack.push_back(index + WIDTH);

                } else {
                    board[index + WIDTH].isHidden = false;
                    numOfHiddenSquares--;
                }
            }
        }

        if (hasLeft) {

            if (!board[index - 1].isMine && board[index - 1].isHidden && !board[index - 1].isFlagged) {

                if (board[index - 1].numOfBorderingMines == 0) {

                    squareStack.push_back(index - 1);

                } else {
                    board[index - 1].isHidden = false;
                    numOfHiddenSquares--;
                }
            }
        }

        if (hasRight) {

            if (!board[index + 1].isMine && board[index + 1].isHidden && !board[index + 1].isFlagged) {

                if (board[index + 1].numOfBorderingMines == 0) {

                    squareStack.push_back(index + 1);

                } else {
                    board[index + 1].isHidden = false;
                    numOfHiddenSquares--;
                }
            }
        }

        if (hasUp && hasLeft) {

            if (!board[index - WIDTH - 1].isMine && board[index - WIDTH - 1].isHidden && !board[index - WIDTH - 1].isFlagged) {

                if (board[index - WIDTH - 1].numOfBorderingMines == 0) {

                    squareStack.push_back(index - WIDTH - 1);

                } else {
                    board[index - WIDTH - 1].isHidden = false;
                    numOfHiddenSquares--;
                }
            }
        }

        if (hasUp && hasRight) {

            if (!board[index - WIDTH + 1].isMine && board[index - WIDTH + 1].isHidden && !board[index - WIDTH + 1].isFlagged) {

                if (board[index - WIDTH + 1].numOfBorderingMines == 0) {

                    squareStack.push_back(index - WIDTH + 1);

                } else {
                    board[index - WIDTH + 1].isHidden = false;
                    numOfHiddenSquares--;
                }
            }
        }

        if (hasDown && hasLeft) {

            if (!board[index + WIDTH - 1].isMine && board[index + WIDTH - 1].isHidden && !board[index + WIDTH - 1].isFlagged) {

                if (board[index + WIDTH - 1].numOfBorderingMines == 0) {

                    squareStack.push_back(index + WIDTH - 1);

                } else {
                    board[index + WIDTH - 1].isHidden = false;
                    numOfHiddenSquares--;
                }
            }
        }

        if (hasDown && hasRight) {

            if (!board[index + WIDTH + 1].isMine && board[index + WIDTH + 1].isHidden && !board[index + WIDTH + 1].isFlagged) {

                if (board[index + WIDTH + 1].numOfBorderingMines == 0) {

                    squareStack.push_back(index + WIDTH + 1);

                } else {
                    board[index + WIDTH + 1].isHidden = false;
                    numOfHiddenSquares--;
                }
            }
        }

        index = squareStack[squareStack.size() - 1];    // if there's an index in the stack, make 
                                                        // the next index to be checked equal to the 
                                                        // 'last' index ('top' of stack)
        squareStack.erase(squareStack.end() - 1);   // remove first element as it is being checked
                                                    // now
    }
}

bool squareClicked(std::vector<Square> &board, int index, bool gameRunning, int &numOfHiddenSquares) {

    if (board[index].isMine) {
        std::cout << "\n\t\tGame over!" << std::endl;
        gameRunning = false;
    } else {
        floodFill(board, index, numOfHiddenSquares);
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

        drawBoard(board, gameRunning);

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

            gameRunning = squareClicked(board, getIndexFromYX(yIn, xIn), gameRunning, numOfHiddenSquares);
        
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

    drawBoard(board, gameRunning);

    return 0;
}