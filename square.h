#ifndef SQUARE_H
#define SQUARE_H

struct Square {                 // template for a square

    bool isHidden;              // state(s)

    int numOfBorderingMines;    // attributes
    bool isMine;
    bool isFlagged;
};

#endif