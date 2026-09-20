#include "flood_fill.h"
#include "neighbouring_checks.h"

void floodFill(std::vector<Square> &board, int index, int &numOfHiddenSquares, int WIDTH, int HEIGHT) {

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