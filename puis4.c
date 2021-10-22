#include "puis4.h"

char get_token_at( table_t* table, int row, int col )
{
	return table->data[row * table->num_columns + col];
}

void set_token_at( table_t* table, int row, int col, char token )
{
	table->data[row * table->num_columns + col] = token;
}
