#ifndef _SEARCH_H_
#define _SEARCH_H_

#include "table.h"

ROW table_search_row_id(TABLE *t, void *key);
TABLE *table_search_row(TABLE *t, char *header_in, char **headers_out, int h_quant, void *cont);
TABLE *table_search_letter (TABLE * t, char * header_in, char ** headers_out, int h_quant, char letter);
float table_column_sum(TABLE *T, char * header);
void table_search_foreach(TABLE * t, int (*func) (tpointer, tpointer, tpointer), tpointer user_data);
TABLE * table_search_position(TABLE * t, int row_number, int row_column);
TABLE * table_join (TABLE * t1, TABLE * t2, char ** headers_out, int h1, int h2, int *types, tpointer (*func) (tpointer, tpointer, tpointer, tpointer), tpointer user_data);
void table_search_foreach_inverse (TABLE * t, int (*func) (tpointer, tpointer, tpointer), tpointer user_data);
int table_search_foreach_indexed(TABLE *t, int index, void (*func) (tpointer, tpointer), tpointer user_data);
#endif 
