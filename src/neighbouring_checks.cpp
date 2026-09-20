#include "neighbouring_checks.h"
#include <vector>

int getYCoordinateFromIndex(int index, int HEIGHT) {

    int yCoordinate = index / HEIGHT;

    return yCoordinate;
}

int getXCoordinateFromIndex(int index, int WIDTH) {    // pretty self explanatory, I'd have thought

    int xCoordinate = index % WIDTH;

    return xCoordinate;
}

int checkForNeighbouringMines(std::vector<Square> board, int index, int WIDTH, int HEIGHT) {

    int numOfBorderingMines = 0;

    bool hasUp      = false;
    bool hasDown    = false;
    bool hasLeft    = false;
    bool hasRight   = false;

    if (getYCoordinateFromIndex(index, HEIGHT) - 1 >= 0) {
        hasUp = true;

        if (board[index - WIDTH].isMine) {
            numOfBorderingMines++;
        }
    }
    if (getYCoordinateFromIndex(index, HEIGHT) + 1 <= HEIGHT - 1) {
        hasDown = true;

        if (board[index + WIDTH].isMine) {
            numOfBorderingMines++;
        }
    }
    if (getXCoordinateFromIndex(index, WIDTH) - 1 >= 0) {
        hasLeft = true;

        if (board[index - 1].isMine) {
            numOfBorderingMines++;
        }
    }
    if (getXCoordinateFromIndex(index, WIDTH) + 1 <= WIDTH - 1) {
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

bool checkForNeighbouringRevealed(std::vector<Square> board, int index, int WIDTH, int HEIGHT) {

    bool neighboursRevealed = false;

    bool hasUp      = false;
    bool hasDown    = false;
    bool hasLeft    = false;
    bool hasRight   = false;

    if (getYCoordinateFromIndex(index, HEIGHT) - 1 >= 0) {
        hasUp = true;

        if (!board[index - WIDTH].isHidden) {
            neighboursRevealed = true;
        }
    }
    if (getYCoordinateFromIndex(index, HEIGHT) + 1 <= HEIGHT - 1) {
        hasDown = true;

        if (!board[index + WIDTH].isHidden) {
            neighboursRevealed = true;
        }
    }
    if (getXCoordinateFromIndex(index, WIDTH) - 1 >= 0) {
        hasLeft = true;

        if (!board[index - 1].isHidden) {
            neighboursRevealed = true;
        }
    }
    if (getXCoordinateFromIndex(index, WIDTH) + 1 <= WIDTH - 1) {
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