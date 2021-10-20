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

bool test_win( char* table, char token, int row, int col )
{
	if ( test_win_horizontal( table, token, row ) )
		return true;

	if ( test_win_vertical( table, token, col ) )
		return true;

	return false;
}
