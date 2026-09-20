#ifndef FLOOD_FILL_H
#define FLOOD_FILL_H

#include "square.h"
#include <vector>

void floodFill(std::vector<Square> &board, int index, int &numOfHiddenSquares, int WIDTH, int HEIGHT);

#endif