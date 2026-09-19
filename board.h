#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "square.h"

std::vector<Square> buildBoard(int &gameNumOfMines, int &displayNumOfMines);
void preCalculateBorderingMines(std::vector<Square> &board);

#endif