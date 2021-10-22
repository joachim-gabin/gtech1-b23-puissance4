#include "winner.h"

static bool test_win_horizontal( table_t* table, char token, int row )
{
	int i = 0, count = 0;
	while ( i < table->num_columns )
	{
		if ( get_token_at( table, row, i ) == token ) count++;
		else count = 0;

		if ( count == 4 )
			return true;

		i++;
	}
	return false;
}

static bool test_win_vertical( table_t* table, char token, int col )
{
	int i = 0, count = 0;
	while ( i < table->num_rows )
	{
		if ( get_token_at( table, i, col ) == token ) count++;
		else count = 0;

		if ( count == 4 )
			return true;

		i++;
	}
	return false;
}

// Left to right diagonal win test.
static bool test_win_ltor( table_t* table, char token, int row, int col )
{
	int min = row < col ? row : col;

	// Back up to the edge.
	row -= min;
	col -= min;

	int count = 0;
	while ( row < table->num_rows && col < table->num_columns )
	{
		if ( get_token_at( table, row, col ) == token ) count++;
		else count = 0;

		if ( count == 4 )
			return true;

		row++;
		col++;
	}
	return false;
}

// Right to left diagonal win test.
static bool test_win_rtol( table_t* table, char token, int row, int col )
{
	int oneminus_col = (table->num_columns - 1) - col;
	int min = row < oneminus_col ? row : oneminus_col;

	// Back up to the edge.
	row -= min;
	col += min;

	int count = 0;
	while ( row < table->num_rows && col >= 0 )
	{
		if ( get_token_at( table, row, col ) == token ) count++;
		else count = 0;

		if ( count == 4 )
			return true;

		row++;
		col--;
	}
	return false;
}

bool test_win( table_t* table, char token, int row, int col )
{
	if ( test_win_horizontal( table, token, row ) ) return true;
	if ( test_win_vertical( table, token, col ) )   return true;
	if ( test_win_ltor( table, token, row, col ) )  return true;
	if ( test_win_rtol( table, token, row, col ) )  return true;

	return false;
}
