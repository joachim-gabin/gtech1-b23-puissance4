#ifndef PUIS4_PUIS4_H
#define PUIS4_PUIS4_H

typedef struct
{
	char* data;
	int num_rows;
	int num_columns;

} table_t;

char get_token_at( table_t* table, int row, int col );

void set_token_at( table_t* table, int row, int col, char token );

#endif // PUIS4_PUIS4_H
