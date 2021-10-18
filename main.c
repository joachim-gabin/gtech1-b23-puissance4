#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// Boolean defines.
#ifndef __cplusplus
#	define bool int
#	define true 1
#	define false 0
#endif

#define NUM_ROWS 6
#define NUM_COLUMNS 7

char table[NUM_ROWS][NUM_COLUMNS];

void init_table();
void display_table();
bool play( int player, int column );

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

		// Prompt the current player for a column index.
		printf( "Player %i (%c), enter column number : ", player + 1, tokens[player]);
		int col = scan_int();
		play( player, col );

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
		printf( "You did not give a number.\nTry again : " );
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
                        printf("%c ", table[z][u]);

                }
                putchar('\n');
        }

        for(int n=0;n<NUM_COLUMNS;n++){
                printf("--");
        }
	putchar( '\n' );

        for(int num=0;num<NUM_COLUMNS;num++){
                printf("%i ",num + 1);
        }
	putchar( '\n' );
}

// Play a token in a column. The function traces down the column to find the first
// empty slot from the bottom.
// "player" is either 0 or 1 (respectively player 1 or 2).
// "column" is the zero-based index of the column to play in.
//
// NOTE : The functin caller must first check if the column index is valid.
bool play( int player, int column )
{
	// Is column full?
	if ( table[0][column] != '.' )
	{
		printf( "Column %i is full! Please select another one : ", column );
		return false;
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
	return true;
}
