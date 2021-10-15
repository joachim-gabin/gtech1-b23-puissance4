#include <string.h>
#include <stdio.h>

char table[6][7];

void init_table()
{
	memset(table,'.',7*6);
}
void afficher_table()
{
	printf(table);
}
