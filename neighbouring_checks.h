#ifndef NEIGHBOURING_CHECKS_H
#define NEIGHBOURING_CHECKS_H

#include <vector>
#include "square.h"

int getYCoordinateFromIndex(int index);
int getXCoordinateFromIndex(int index);

int checkForNeighbouringMines(std::vector<Square> board, int index);
bool checkForNeighbouringRevealed(std::vector<Square> board, int index);

#endif