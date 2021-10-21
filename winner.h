#ifndef PUIS4_WINNER_H
#define PUIS4_WINNER_H

#include "bool.h"

// Tests if player won by placing a token.
// The function expects the game table, the player's token, and the last played position,
// because there is no need to check the entire table.
bool test_win( char* table, char token, int row, int col );

#endif // PUIS4_WINNER_H
