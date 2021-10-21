#ifndef PUIS4_WINNER_H
#define PUIS4_WINNER_H

#include "bool.h"

// Tests if player won by placing a token.
// The function expects the game table, the player's token, and the last played position.
// It will then check for a sequence horizontally and vertically on the given row / column.
// /!\ Diagonal check isn't implemented yet.
bool test_win( char* table, char token, int row, int col );

#endif // PUIS4_WINNER_H
