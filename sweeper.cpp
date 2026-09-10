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

#define DIFFICULTY 8        // difficulty, is subtracted from the max range of the rng to make the 
                            // chance of a given square being a mine higher. higher nums are harder.
                            // default chance is 1/15, medium diff is 1/12, hard is 1/8.
#define BOTTOMLEFT WIDTH*HEIGHT-WIDTH

std::random_device rnd;
std::mt19937 rng(rnd());
std::uniform_int_distribution<std::mt19937::result_type> dist(1, (15 - DIFFICULTY));
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

/*
(relating to function below)

this one's a bit hard to explain. the X and Y start coordinates are where the for-loops will
start looking for mines, which (when no sides are occluded) the defualt values are (-1, -1),
relative to the index of the square we're checking from. imagine placing a 3*3 square on top of
the centre square, where the centre of the 3*3 lines up with the square we're checking around
for mines in the first place. the top left square is (-1, -1), the middle square is (0, 0), and
the bottom right square is (1, 1).

like this:
           0  ---> X
          | +-----+-----+-----+
          | |-1,-1|-1,0 |-1,1 |
         \/ +-----+-----+-----+
          Y | 0,-1| MID | 0,1 | where MID is the square we're checking from.
            +-----+-----+-----+
            | 1,-1| 1,0 | 1,1 |
            +-----+-----+-----+

the way the for-loops actually check the 1-dimensional arrray as if it's 2-dimensional is by
having the X value increase by 1, and the Y value increase by WIDTH. for example, let's take a
5*6 (WIDTH*HEIGHT) square as the size of our board. (I know I use both (y, x) and (x, y) in
this project, uhhhh idk, get used to it) the board looks like this:

            0 ------------------------------> X
            | +-----+-----+-----+-----+-----+
            | |  0  |  1  |  2  |  3  |  4  |
            | +-----+-----+-----+-----+-----+
            | |  5  |  6  |  7  |  8  | ... |
            | +-----+-----+-----+-----+-----+
            | |     |     |     |     |     |
            | +-----+-----+-----+-----+-----+
            | |     |     |     |     |     |
            | +-----+-----+-----+-----+-----+
            | |     |     |     |     |     |
            | +-----+-----+-----+-----+-----+
            | | ... | 26  | 27  | 28  | 29  |
           \/ +-----+-----+-----+-----+-----+
            Y

but, to the program, all the squares are actually stored in a 1-dimensional array as follows:

               0 ---------------------------------------.........-------> INDEX
            +-----+-----+-----+-----+-----+-----+-----+-...   ...-+-----+
            |  0  |  1  |  2  |  3  |  4  |  5  |  6  | ...   ... | 29  |
            +-----+-----+-----+-----+-----+-----+-----+-...   ...-+-----+

to access the item below square 1 on the 2D board, you would just add WIDTH to the index of the
square you're going from. now, notice that the INDEX and the COORDINATES are completely
separate. I've made a function to convert from index to coordinates, but this is more for the
ease of not having to do the conversions in my head manually, for logic purposes. I can't do any 
operations with the X and Y coordinates of the square. since they are stored in the array, I 
have to access them via their index.

using the method explained earlier, if we take square[6] as the MID square, then to access the
top left square relative to MID, we'd subtract WIDTH from the index, (putting us at square[1]),
and then subtract 1, to get square[0]. this is the top left square relative to MID, in a 3*3
square around MID. graphical representation:

    (the square brackets represents which square we are on at this point in time)

                -1     0     1
            +-----+-----+-----+-...
         -1 |  0  |  1  |  2  |
            +-----+-----+-----+-...
          0 |  5  | [6] |  7  |
            +-----+-----+-----+-...
          1 | 10  | 11  | 12  |
            +-----+-----+-----+-...
            .     .     .     .
            .     .     .     .
            .     .     .     .

    the starting index--or index of MID--whichever you prefer, is 6.

    subtracting WIDTH from the index moves us up one square (in the 2D representation):

                -1     0     1
            +-----+-----+-----+-...
         -1 |  0  | [1] |  2  |
            +-----+-----+-----+-...
          0 |  5  |  6  |  7  |
            +-----+-----+-----+-...
          1 | 10  | 11  | 12  |
            +-----+-----+-----+-...
            .     .     .     .
            .     .     .     .
            .     .     .     .

    then, subtracting 1 from the index moves us one square to the left:

                -1     0     1
            +-----+-----+-----+-...
         -1 | [0] |  1  |  2  |
            +-----+-----+-----+-...
          0 |  5  |  6  |  7  |
            +-----+-----+-----+-...
          1 | 10  | 11  | 12  |
            +-----+-----+-----+-...
            .     .     .     .
            .     .     .     .
            .     .     .     .

    yay! that's how the indexing works, at least. the X/YCoordStart/End variables represent the
    desired starting and ending coordinates relative to MID, as if the square is on the border
    or in a corner, we can't check the full 3*3 square around it. I'm sure you can figure that
    out. this is already incredibly long.
*/

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

    bool hasUp, hasDown, hasLeft, hasRight = false;

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

int getIndexFromXY(int yCoordinate, int xCoordinate) {          // useful for GUI clicks? idk

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

            char squareChar = getSquareChar(board[getIndexFromXY(y, x)]);

            std::cout << "  " << squareChar;
        }

    }

    std::cout << std::endl;
}

void floodFill(std::vector<Square> &board, int index) {

    std::vector<int> squareStack;       // create square stack for flood fill and add current
    squareStack.push_back(index);       // index to the stack

    if (! board[index].isMine && board[index].numOfBorderingMines == 0) {

        board[index].isHidden = false;      // make the clicked square empty

    } else {

        board[index].isHidden = false;
        return;
    }

    while (squareStack.size() > 0) {

        board[index].isHidden = false;

        bool hasUp, hasDown, hasLeft, hasRight = false; // not being used currently, was thinking
                                                        // of using for corner checks

        if (getYCoordinateFromIndex(index) - 1 >= 0) {  // if has up neighbour and up-square fits 
                                                        // requirements, add the square to
                                                        // squareStack
            hasUp = true;

            if (! board[index - WIDTH].isMine && board[index - WIDTH].numOfBorderingMines == 0 && board[index - WIDTH].isHidden) {

                squareStack.push_back(index - WIDTH);
            
            } else if (! board[index - WIDTH].isMine && board[index - WIDTH].numOfBorderingMines > 0) {

                board[index - WIDTH].isHidden = false;  // or if bordering square has adj. mines but
                                                        // is not a mine, just reveal it
            }
        }

        if (getYCoordinateFromIndex(index) + 1 <= HEIGHT - 1) { // if has down neighbour and 
                                                                // down-square fits requirements, 
                                                                // add the square to squareStack
            hasDown = true;

            if (! board[index + WIDTH].isMine && board[index + WIDTH].numOfBorderingMines == 0 && board[index + WIDTH].isHidden) {

                squareStack.push_back(index + WIDTH);
            
            } else if (! board[index + WIDTH].isMine && board[index + WIDTH].numOfBorderingMines > 0) {

                board[index + WIDTH].isHidden = false;  // or if bordering square has adj. mines but
                                                        // is not a mine, just reveal it
            }
        }

        if (getXCoordinateFromIndex(index) - 1 >= 0) {  // if has left neighbour and left-square
                                                        // fits requirements, add the square to
                                                        // squareStack
            hasLeft = true;

            if (! board[index - 1].isMine && board[index - 1].numOfBorderingMines == 0 && board[index - 1].isHidden) {

                squareStack.push_back(index - 1);
            
            } else if (! board[index - 1].isMine && board[index - 1].numOfBorderingMines > 0) {

                board[index - 1].isHidden = false;  // or if bordering square has adj. mines but is
                                                    // not a mine, just reveal it
            }
        }

        if (getXCoordinateFromIndex(index) + 1 <= WIDTH - 1) {  // if has right neighbour and
                                                                // right-square fits requirements,
                                                                // add the square to squareStack
            hasRight = true;

            if (! board[index + 1].isMine && board[index + 1].numOfBorderingMines == 0 && board[index + 1].isHidden) {

                squareStack.push_back(index + 1);
            
            } else if (! board[index + 1].isMine && board[index + 1].numOfBorderingMines > 0) {

                board[index + 1].isHidden = false;  // or if bordering square has adj. mines but is
                                                    // not a mine, just reveal it
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

            squareClicked(board, getIndexFromXY(yIn, xIn), gameRunning);
        }

    }

    return 0;
}