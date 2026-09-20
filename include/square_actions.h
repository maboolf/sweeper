#ifndef SQUARE_ACTIONS_H
#define SQUARE_ACTIONS_H

#include <vector>
#include "square.h"

bool squareClicked(std::vector<Square> &board, int index, bool gameRunning, int &numOfHiddenSquares, int WIDTH, int HEIGHT);
void squareFlagged(std::vector<Square> &board, int index, int &displayNumOfMines);

#endif