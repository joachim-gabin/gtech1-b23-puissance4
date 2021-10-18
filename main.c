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
-
void init_table();
void display_table();

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
	display_table();




	// Main game loop.
	while ( ! win )
	{
		// Prompt the current player for a column index.
		printf( "Player %i (%c), enter column number : ", player + 1, tokens[player]);
		int col = scan_int();

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
	printf( table );
}
