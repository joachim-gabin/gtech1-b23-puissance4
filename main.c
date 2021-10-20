#include <stdlib.h>
#include <stdio.h>
#include <string.h>



#include "puis4.h"
#include "winner.h"
#include "bool.h"

char table[NUM_ROWS][NUM_COLUMNS];

void init_table();
void display_table();
void display_prompt( int player );
void display_token( char token );
const char* get_token_color( char token );
int play( int player, int column );

char tokens[] = "ox";



int scan_int();
bool win=false;
int tour=0;

int main( void )
{
	printf( "Welcome to Puissance 4 !\n");
	printf( "Game size is %i x %i \n", NUM_ROWS , NUM_COLUMNS);

	int player = 0;
	init_table();



	// Main game loop.
	while ( ! win )
	{
		display_table();

		int col =  0;
		int row = -1;

		// This loops until the player has selected a non-empty column.
		while (row == -1)
		{
			// Prompt the current player for a column index.
			display_prompt( player );

			col = scan_int();

			// This loops until the player has selected a correct column index.
			while (col < 1 || col > NUM_COLUMNS)
			{
				printf("You need to choose a number between 1 and %i\n", NUM_COLUMNS);

				// Re-display prompt.
				display_prompt( player );
				col = scan_int();
			}

			row = play(player, col - 1);
		}

		if ( test_win( (char*) table, tokens[player], row, col - 1 ) )
		{
			display_table();
			printf("WIN!!!11!!1!!\n");
			break;
		}

		tour ++;
		if (tour==42)
			break;

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
		printf( "You did not give a number. Try again : " );
		while ( getchar() != '\n' );
	}
	return r;
}

void init_table()
{
	memset( table, '.' , NUM_ROWS * NUM_COLUMNS );
}

void display_table()
{
        for(int n=0;n<NUM_COLUMNS;n++){
                printf("--");
        }
	putchar( '\n' );

        for(int z=0;z<NUM_ROWS;z++){
                for(int u=0;u<NUM_COLUMNS;u++){
                        display_token( table[z][u] );
			putchar( ' ' );
                }
                putchar('\n');
        }

	// Reset color code.
	printf( "\033[0m" );

        for(int n=0;n<NUM_COLUMNS;n++){
                printf("--");
        }
	putchar( '\n' );

        for(int num=0;num<NUM_COLUMNS;num++){
                printf("%i ",num + 1);
        }
	putchar( '\n' );
}

// Display the prompt for entering the column number.
// This displays a line with the player number (1 or 2), the token they're playing,
// and the column range (between 1 and NUM_COLUMNS).
void display_prompt( int player )
{
	printf( "Player %i (%s%c\033[0m), select column [1; %i] : ", player + 1, get_token_color( tokens[player] ), tokens[player], NUM_COLUMNS );
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
// NOTE : The function caller must first check if the column index is valid.
int play( int player, int column )
{
	// Is column full?
	if ( table[0][column] != '.' )
	{
		printf( "Column %i is full! Please select another one.\n", column + 1 );
		return -1;
	}

	// Find the index of the last empty slot in this column.
	int i = 0;
	while ( i < NUM_ROWS - 1 )
	{
		// Get the tile below.
		if ( table[i + 1][column] != '.' )
		{
			break;
		}
		i++;
	}

	// Set the token corresponding to the player.
	table[i][column] = tokens[player];
	return i;
}

