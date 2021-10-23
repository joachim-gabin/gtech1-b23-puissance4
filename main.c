#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "puis4.h"
#include "winner.h"
#include "bool.h"



table_t table;

void init_table( int rows, int cols );
void display_table();
void display_prompt( int player );
void display_token( char token );
const char* get_token_color( char token );

int scan_int();
int play( int player, int column );

char tokens[] = "ox";
int turn = 0;



int main( int argc, char** argv )
{
	// Default size.
	int rows = 6, cols = 7;

	// Parse command line arguments to determine custom game size.
	if ( argc == 3 )
	{
		char* end;
		rows = strtol( argv[1], &end, 10 );
		cols = strtol( argv[2], &end, 10 );

		if ( rows <= 0 || cols <= 0 )
		{
			printf( "Incorrect row or column count specified.\n" );
			return 2;
		}
	}
	else if ( argc != 1 )
	{
		printf( "Incorrect number of arguments. Usage :\n" );
		printf( "- puis4 [<num_rows> <num_columns>] \n" );
		return 1;
	}

	printf( "Welcome to Puissance 4!\n" );
	printf( "Game size is %i x %i\n", rows, cols );

	int player = 0;
	init_table( rows, cols );



	// Main game loop.
	while ( true )
	{
		display_table();

		int col =  0;
		int row = -1;

		// This loops until the player has selected a non-empty column.
		while ( row == -1 )
		{
			// Prompt the current player for a column index.
			display_prompt( player );

			col = scan_int();

			// This loops until the player has selected a correct column index.
			while ( col < 1 || col > table.num_columns )
			{
				printf( "\nYou need to choose a number between 1 and %i\n", table.num_columns );

				// Re-display prompt.
				display_prompt( player );
				col = scan_int();
			}

			row = play( player, col - 1 );
		}

		// Test if current player won by placing their token.
		if ( test_win( &table, tokens[player], row, col - 1 ) )
		{
			display_table();
			printf( "\n-----[ Player %s%i\033[0m wins! ]-----\n\n", get_token_color( tokens[player] ), player + 1 );
			break;
		}

		// If we filled the grid without anyone winning, it's a tie.
		turn++;
		if ( turn == table.num_rows * table.num_columns )
		{
			printf( "\nFinished! It's a tie!\n\n" );
			break;
		}

		// Toggle player.
		player = player ^ 1;
	}
}

// This function asks the user to input an integer, and loops if the user enters something else.
int scan_int()
{
	int r;
	while ( scanf( "%i", &r ) != 1 )
	{
		printf( "\nYou did not give a number. Try again : \n" );
		while ( getchar() != '\n' );
	}
	return r;
}

// Fills the table with empty slots, marked by a '.'
void init_table( int rows, int cols )
{
	table.data = (char*) malloc( rows * cols );
	table.num_rows    = rows;
	table.num_columns = cols;

	memset( table.data, '.' , rows * cols );
}

void display_table_delimiter()
{
	for ( int n = 0; n < table.num_columns; n++ )
	{
                printf( table.num_columns > 10 ? "---" : "--" );
        }
	putchar( '-' );
	putchar( '\n' );
}

// Displays the current state of the table.
void display_table()
{
	// Leave space before the grid.
	putchar( '\n' );

        display_table_delimiter();

        for ( int r = 0; r < table.num_rows; r++ )
	{
		putchar( ' ' );
                for ( int c = 0; c < table.num_columns; c++ )
		{
                        display_token( get_token_at( &table, r, c ) );
			printf( table.num_columns > 10 ? "  " : " " );
                }
                putchar('\n');
        }

	// Reset color code.
	printf( "\033[0m" );

        display_table_delimiter();

	// Display column numbers.
	putchar( ' ' );
        for ( int num = 1; num < table.num_columns + 1; num++ ){
                printf( (table.num_columns > 10 && num < 10) ? "%i  " : "%i ", num );
        }

	putchar( '\n' );
	putchar( '\n' );
}

// Display the prompt for entering the column number.
// This displays a line with the player number (1 or 2), the token they're playing,
// and the column range (between 1 and NUM_COLUMNS).
void display_prompt( int player )
{
	printf( "Player %i (%s%c\033[0m), select column [1; %i] : ", player + 1, get_token_color( tokens[player] ), tokens[player], table.num_columns );
}

// Display the token with its corresponding color.
void display_token( char token )
{
	fputs( get_token_color( token ), stdout );
	putchar( token );
}

const char* get_token_color( char token )
{
	switch ( token )
	{
	case 'o': return "\033[31m";
	case 'x': return "\033[33m";
	default:  return "\033[0m";
	}
}

// Play a token in a column. The function traces down the column to find the first
// empty slot from the bottom.
// "player" is either 0 or 1 (respectively player 1 or 2).
// "column" is the zero-based index of the column to play in.
//
// This function returns the row index where the token landed, or -1 if the column
// was full.
//
// NOTE : The function caller must first check if the column index is valid, as this
// function does not do any checks.
int play( int player, int column )
{
	// Is column full?
	if ( get_token_at( &table, 0, column ) != '.' )
	{
		printf( "Column %i is full! Please select another one.\n", column + 1 );
		return -1;
	}

	// Find the index of the last empty slot in this column.
	int i = 0;
	while ( i < table.num_rows - 1 )
	{
		// Get the tile below.
		if ( get_token_at( &table, i + 1, column ) != '.' )
		{
			break;
		}
		i++;
	}

	// Set the token corresponding to the player.
	set_token_at( &table, i, column, tokens[player] );
	return i;
}
