#include <stdlib.h>
#include <stdio.h>



// Boolean defines.
#ifndef __cplusplus
#	define bool int
#	define true 1
#	define false 0
#endif

int scan_int();



int main( void )
{
	bool player1 = true;

	// Main game loop.
	while ( true )
	{
		// Prompt the current player for a column index.
		printf( "Player %i (%c), enter column number : ", player1 ? 1 : 2, player1 ? 'O' : 'X' );
		int col = scan_int();

		// Toggle player.
		player1 = !player1;
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
