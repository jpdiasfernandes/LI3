#ifndef __TABLE_P_H_
#define __TABLE_P_H_
#include "table.h"
#include <glib-2.0/glib.h>

/**
 * INFO:
 * @type: type of the content
 * @size: size of the content
 * @header_no: number of the collumn
 * @field_name: name of the collumn
 */
struct info {
	int type;
	int size;
	int header_no; 
	const char *field_name;
};
/**
 * CELL:
 * @cont: pointer to the alloc'ed content
 * @row_ptr: pointer to the row of the cell
 */
struct cell {
	int type;
	int size;
	void *cont;
	ROW row_ptr;
};

/**
 * TABLE:
 * @fields: Number of columns
 * @header: Information of each collumn
 * @gtree: Balanced binary tree to store the content
 */
struct table {
	int fields;
	int index;
	HEADER header;
	GTree **gtree;
};

CELL cell_copy(CELL c);
ROW row_copy_with_headers (int dest_fields_n, ROW orig_r, HEADER orig_header, int orig_fields_n, char ** headers_out);
ROW row_copy(int fields, ROW row, HEADER header);
INFO header_helper_type(HEADER h, int fields, char *col_name);
GTree *header_helper_indexed(TABLE *t, char *header);
gint row_cmp(gconstpointer row1, gconstpointer row2);
int table_insert_internal(TABLE *t, gpointer key, gpointer value);
int table_append_row(TABLE *t, ROW row);
gint gtree_free_row(gpointer key, gpointer value, gpointer data);
int table_indexed_insert(GTree *gt, void *key, GPtrArray *row_array);
int find_column_header(HEADER header, char *header_cmp, int n_fields);

#endif 
