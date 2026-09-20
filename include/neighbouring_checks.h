#ifndef NEIGHBOURING_CHECKS_H
#define NEIGHBOURING_CHECKS_H

#include <vector>
#include "square.h"

int getYCoordinateFromIndex(int index, int HEIGHT);
int getXCoordinateFromIndex(int index, int WIDTH);

int checkForNeighbouringMines(std::vector<Square> board, int index, int WIDTH, int HEIGHT);
bool checkForNeighbouringRevealed(std::vector<Square> board, int index, int WIDTH, int HEIGHT);

#endif