#include "winner.h"

#include "puis4.h"

static bool test_win_horizontal( char* table, char token, int row )
{
	int i = 0, count = 0;
	while ( i < NUM_COLUMNS )
	{
		if ( table[row * NUM_COLUMNS + i] == token ) count++;
		else count = 0;

		if ( count == 4 )
			return true;

		i++;
	}
	return false;
}

static bool test_win_vertical( char* table, char token, int col )
{
	int i = 0, count = 0;
	while ( i < NUM_ROWS )
	{
		if ( table[i * NUM_COLUMNS + col] == token ) count++;
		else count = 0;

		if ( count == 4 )
			return true;

		i++;
	}
	return false;
}

// Left to right diagonal win test.
static bool test_win_ltor( char* table, char token, int row, int col )
{
	int min = row < col ? row : col;

	// Back up to the edge.
	row -= min;
	col -= min;

	int count = 0;
	while ( row < NUM_ROWS && col < NUM_COLUMNS )
	{
		if ( table[row * NUM_COLUMNS + col] == token ) count++;
		else count = 0;

		if ( count == 4 )
			return true;

		row++;
		col++;
	}
	return false;
}

// Right to left diagonal win test.
static bool test_win_rtol( char* table, char token, int row, int col )
{
	int oneminus_col = (NUM_COLUMNS - 1) - col;
	int min = row < oneminus_col ? row : oneminus_col;

	// Back up to the edge.
	row -= min;
	col += min;

	int count = 0;
	while ( row < NUM_ROWS && col >= 0 )
	{
		if ( table[row * NUM_COLUMNS + col] == token ) count++;
		else count = 0;

		if ( count == 4 )
			return true;

		row++;
		col--;
	}
	return false;
}

bool test_win( char* table, char token, int row, int col )
{
	if ( test_win_horizontal( table, token, row ) ) return true;
	if ( test_win_vertical( table, token, col ) )   return true;
	if ( test_win_ltor( table, token, row, col ) )  return true;
	if ( test_win_rtol( table, token, row, col ) )  return true;

	return false;
}
