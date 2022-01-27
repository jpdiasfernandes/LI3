#ifndef _TABLE_
#define _TABLE_
#include <stdio.h>
#include <glib-2.0/glib.h>

#define COL_TYPE_INT     0 
#define COL_TYPE_DOUBLE  1 
#define COL_TYPE_FLOAT   2
#define COL_TYPE_STRING  3
#define COL_TYPE_CHAR    4
#define COL_TYPE_DEFAULT 5

typedef struct info INFO;
typedef struct cell CELL;
typedef CELL *ROW;
typedef INFO *HEADER;
typedef struct table TABLE;
typedef void * tpointer;

TABLE *table_new(int fields, int index, const char *fmt, ...);
int table_append(TABLE *t, ...);
char *table_to_file(FILE *fp, TABLE *t);
void table_destroy(TABLE *t);
int table_add_indexing(TABLE *t, int index);
TABLE * table_search_row(TABLE *t, char *header_in, char ** headers_out, int h_quant, void * cont);
int table_size(TABLE *t);
TABLE *table_new_header(int fields, int index, HEADER header);
int table_append_generic(TABLE *t, void **args);
TABLE *table_new_generic(int fields, int index, int *types, char **headers);
void * get_row_content_by_column (ROW row, int column);
void * get_row_content_by_header (ROW row, HEADER header, char * header_cmp, int n_fields);
HEADER get_headers (TABLE * t);
char ** get_header_names (HEADER header, int n__fields);
int get_fields (TABLE * t);
int * get_header_types (HEADER header, int n__fields);
int table_append_row_gk (TABLE * t, ROW row, tpointer (* func) (tpointer, tpointer, tpointer, tpointer), tpointer r1, tpointer r2, tpointer user_data);
ROW table_last_row (TABLE * t);
TABLE * table_set_columns (TABLE * t, int * cols, int num_cols);
ROW row_create (void ** args, int * types, int size);
ROW row_copy (int fields, ROW row, HEADER header);
int table_append_row(TABLE *t, ROW row);

#endif 
