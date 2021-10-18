#include <stdlib.h>
#include <stdio.h>
#include "table.h"


// Boolean defines.
#ifndef __cplusplus
#	define bool int
#	define true 1
#	define false 0
#endif

char tokens[]= "ox";


int scan_int();
bool win=false;
int tour=0;

int main( void )
{
	int player = 0;
	init_table();
	afficher_table();




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
