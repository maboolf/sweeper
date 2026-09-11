#include <vector>
#include <random>

// ######## TEMP ###########

#include <string>
#include <iostream>

// ######## END TEMP #######

// ----------------------------------------------------------------------------
// WIDTH, HEIGHT, AND DIFFICULTY WILL BE SOMEHOW HANDLED BY GUI WITH BUTTONS.
// ----------------------------------------------------------------------------

#define WIDTH 16            // num of squares vertically
#define HEIGHT 16           // num of squares horizontally

#define DIFFICULTY 0        // difficulty, is subtracted from the max range of the rng to make the 
                            // chance of a given square being a mine higher. higher nums are harder.
                            // default chance is 1/10, medium diff is 1/7, hard is 1/4.
#define BOTTOMLEFT WIDTH*HEIGHT-WIDTH

std::random_device rnd;
std::mt19937 rng(rnd());
std::uniform_int_distribution<std::mt19937::result_type> dist(1, (10 - DIFFICULTY));
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ random num gen thing for mines

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

    bool hasUp, hasDown, hasLeft, hasRight = false;

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

    // int checkXCoordStart, checkYCoordStart = -1;
    // int checkXCoordEnd, checkYCoordEnd = 1;

    // if ((getXCoordinateFromIndex(index) - 1) < 0) { // if the x-coord - 1 is less than zero, then
    //     checkXCoordStart = 0;                       // skip checking the left side

    // } else if ((getXCoordinateFromIndex(index) + 1) > (WIDTH - 1)) { // same as last but opposite
    //     checkXCoordEnd = 0;
    // }

    // if ((getYCoordinateFromIndex(index) - 1) < 0) { // if the y-coord - 1 is less than zero, then
    //     checkYCoordStart = 0;                       // skips checking the top side

    // } else if ((getYCoordinateFromIndex(index) + 1) > (HEIGHT - 1)) { // same as last but opposite
    //     checkYCoordEnd = 0;
    // }

    // for (int y = checkXCoordStart; y < checkYCoordEnd; y++) {

    //     if (neighboursRevealed) {
    //         break;
    //     }

    //     for (int x = checkXCoordStart; x < checkYCoordEnd; x++) {

    //         if (y == 0 && x == 0) {
    //             continue;

    //         } else if (! board[index + (y * WIDTH + x)].isHidden) {
    //             neighboursRevealed = true;
    //             break;
    //         }
    //     }
    // }

    bool hasUp      = false;
    bool hasDown    = false;
    bool hasLeft    = false;
    bool hasRight   = false;

    if (getYCoordinateFromIndex(index) - 1 >= 0) {
        hasUp = true;

        if (! board[index - WIDTH].isHidden) {
            neighboursRevealed = true;
        }
    }
    if (getYCoordinateFromIndex(index) + 1 <= HEIGHT - 1) {
        hasDown = true;

        if (! board[index + WIDTH].isHidden) {
            neighboursRevealed = true;
        }
    }
    if (getXCoordinateFromIndex(index) - 1 >= 0) {
        hasLeft = true;

        if (! board[index - 1].isHidden) {
            neighboursRevealed = true;
        }
    }
    if (getXCoordinateFromIndex(index) + 1 <= WIDTH - 1) {
        hasRight = true;

        if (! board[index + 1].isHidden) {
            neighboursRevealed = true;
        }
    }

    if (hasUp && hasLeft) {
        if (! board[index - WIDTH - 1].isHidden) {
            neighboursRevealed = true;
        }
    }

    if (hasUp && hasRight) {
        if (! board[index - WIDTH + 1].isHidden) {
            neighboursRevealed = true;
        }
    }

    if (hasDown && hasLeft) {
        if (! board[index + WIDTH - 1].isHidden) {
            neighboursRevealed = true;
        }
    }

    if (hasDown && hasRight) {
        if (! board[index + WIDTH + 1].isHidden) {
            neighboursRevealed = true;
        }
    }

    return neighboursRevealed;
}

std::vector<Square> buildBoard() {          // builds board at start of game

    std::vector<Square> board;

    for (int y = 0; y < HEIGHT; y++) {

        for (int x = 0; x < WIDTH; x++) {

            if (dist(rng) == 1) {           // if rng = 1, make the square a mine

                board.push_back({true, 0, true, false});

            } else {                        // otherwise the square is not a mine
                board.push_back({true, 0, false, false});
            }
        }
    }

    return board;
}

void preCalculateBorderingMines(std::vector<Square> &board) {    // calculates all squares' bordering
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

char getSquareChar(Square square) {

    const char squareChars[] = " 12345678#F@";

    char squareChar;

    if (! square.isHidden && ! square.isFlagged) {

        if (! square.isMine && square.numOfBorderingMines > 0) {
            squareChar = squareChars[square.numOfBorderingMines];

        } else if (! square.isMine && square.numOfBorderingMines == 0) {
            squareChar = '.';
        
        } else {
            squareChar = '@';
        }

    } else if (square.isFlagged) {
        squareChar = 'F';

    } else {
        squareChar = '#';
    }

    return squareChar;
}

void drawBoard(std::vector<Square> board) {

    for (int y = 0; y < HEIGHT; y++) {

        std::cout << "\n";

        for (int x = 0; x < WIDTH; x++) {

            char squareChar = getSquareChar(board[getIndexFromYX(y, x)]);

            std::cout << "  " << squareChar;
        }

    }

    std::cout << std::endl;
}

// ################################### NORMAL FUNCTIONS ############################################

void floodFill(std::vector<Square> &board, int index) {

    std::vector<int> squareStack;       // create square stack for flood fill and add current
    squareStack.push_back(index);       // index to the stack

    if (! board[index].isMine && board[index].numOfBorderingMines > 0) {

        board[index].isHidden = false;
        return;
    }

    while (squareStack.size() > 0) {

        board[index].isHidden = false;

        bool hasUp      = false;
        bool hasDown    = false;
        bool hasLeft    = false;
        bool hasRight   = false;

        if (getYCoordinateFromIndex(index) - 1 >= 0) {  // if has up neighbour and up-square fits 
                                                        // requirements, add the square to
                                                        // squareStack
            hasUp = true;

            // if (! board[index - WIDTH].isMine && board[index - WIDTH].numOfBorderingMines == 0 && board[index - WIDTH].isHidden) {

            //     squareStack.push_back(index - WIDTH);
            
            // } else if (! board[index - WIDTH].isMine && board[index - WIDTH].numOfBorderingMines > 0) {

            //     board[index - WIDTH].isHidden = false;  // or if bordering square has adj. mines but
            //                                             // is not a mine, just reveal it
            // }
        }

        if (getYCoordinateFromIndex(index) + 1 <= HEIGHT - 1) { // if has down neighbour and 
                                                                // down-square fits requirements, 
                                                                // add the square to squareStack
            hasDown = true;

            // if (! board[index + WIDTH].isMine && board[index + WIDTH].numOfBorderingMines == 0 && board[index + WIDTH].isHidden) {

            //     squareStack.push_back(index + WIDTH);
            
            // } else if (! board[index + WIDTH].isMine && board[index + WIDTH].numOfBorderingMines > 0) {

            //     board[index + WIDTH].isHidden = false;  // or if bordering square has adj. mines but
            //                                             // is not a mine, just reveal it
            // }
        }

        if (getXCoordinateFromIndex(index) - 1 >= 0) {  // if has left neighbour and left-square
                                                        // fits requirements, add the square to
                                                        // squareStack
            hasLeft = true;

            // if (! board[index - 1].isMine && board[index - 1].numOfBorderingMines == 0 && board[index - 1].isHidden) {

            //     squareStack.push_back(index - 1);
            
            // } else if (! board[index - 1].isMine && board[index - 1].numOfBorderingMines > 0) {

            //     board[index - 1].isHidden = false;  // or if bordering square has adj. mines but is
            //                                         // not a mine, just reveal it
            // }
        }

        if (getXCoordinateFromIndex(index) + 1 <= WIDTH - 1) {  // if has right neighbour and
                                                                // right-square fits requirements,
                                                                // add the square to squareStack
            hasRight = true;

            // if (! board[index + 1].isMine && board[index + 1].numOfBorderingMines == 0 && board[index + 1].isHidden) {

            //     squareStack.push_back(index + 1);
            
            // } else if (! board[index + 1].isMine && board[index + 1].numOfBorderingMines > 0) {

            //     board[index + 1].isHidden = false;  // or if bordering square has adj. mines but is
            //                                         // not a mine, just reveal it
            // }
        }

        if (hasUp) {

            if (! board[index - WIDTH].isMine && board[index - WIDTH].isHidden) {

                if (board[index - WIDTH].numOfBorderingMines == 0) {

                    squareStack.push_back(index - WIDTH);

                } else {

                    board[index - WIDTH].isHidden = false;
                }
            }
        }

        if (hasDown) {

            if (! board[index + WIDTH].isMine && board[index + WIDTH].isHidden) {

                if (board[index + WIDTH].numOfBorderingMines == 0) {

                    squareStack.push_back(index + WIDTH);

                } else {

                    board[index + WIDTH].isHidden = false;
                }
            }
        }

        if (hasLeft) {

            if (! board[index - 1].isMine && board[index - 1].isHidden) {

                if (board[index - 1].numOfBorderingMines == 0) {

                    squareStack.push_back(index - 1);

                } else {

                    board[index - 1].isHidden = false;
                }
            }
        }

        if (hasRight) {

            if (! board[index + 1].isMine && board[index + 1].isHidden) {

                if (board[index + 1].numOfBorderingMines == 0) {

                    squareStack.push_back(index + 1);

                } else {

                    board[index + 1].isHidden = false;
                }
            }
        }

        if (hasUp && hasLeft) {

            if (! board[index - WIDTH - 1].isMine && board[index - WIDTH - 1].isHidden) {

                if (board[index - WIDTH - 1].numOfBorderingMines == 0) {

                    squareStack.push_back(index - WIDTH - 1);

                } else {

                    board[index - WIDTH - 1].isHidden = false;
                }
            }
        }

        if (hasUp && hasRight) {

            if (! board[index - WIDTH + 1].isMine && board[index - WIDTH + 1].isHidden) {

                if (board[index - WIDTH + 1].numOfBorderingMines == 0) {

                    squareStack.push_back(index - WIDTH + 1);

                } else {

                    board[index - WIDTH + 1].isHidden = false;
                }
            }
        }

        if (hasDown && hasLeft) {

            if (! board[index + WIDTH - 1].isMine && board[index + WIDTH - 1].isHidden) {

                if (board[index + WIDTH - 1].numOfBorderingMines == 0) {

                    squareStack.push_back(index + WIDTH - 1);

                } else {

                    board[index + WIDTH - 1].isHidden = false;
                }
            }
        }

        if (hasDown && hasRight) {

            if (! board[index + WIDTH + 1].isMine && board[index + WIDTH + 1].isHidden) {

                if (board[index + WIDTH + 1].numOfBorderingMines == 0) {

                    squareStack.push_back(index + WIDTH + 1);

                } else {

                    board[index + WIDTH + 1].isHidden = false;
                }
            }
        }

        index = squareStack[squareStack.size() - 1];    // if there's an index in the stack, make 
                                                        // the next index to be checked equal to the 
                                                        // 'last' index ('top' of stack)
        squareStack.erase(squareStack.end() - 1);   // remove first element as it is being checked
                                                    // now

        drawBoard(board); // DEBUG
    }
}

bool squareClicked(std::vector<Square> &board, int index, bool gameRunning) {

    if (board[index].isMine) {

        std::cout << "Game over!" << std::endl;
        gameRunning = false;

    } else {

        floodFill(board, index);
    }

    return gameRunning;
}

int main() {

    bool gameRunning = true;

    std::vector<Square> board = buildBoard();
    preCalculateBorderingMines(board);

    while (gameRunning) {

        drawBoard(board);

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

            squareClicked(board, getIndexFromYX(yIn, xIn), gameRunning);
        }

    }

    return 0;
}
