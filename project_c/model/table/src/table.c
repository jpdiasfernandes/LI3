/* The reason I'm creating this data abstraction is because GRelation (glib
 * API) was deprecated and limited to only two atributes.
 * This got me thinking and decided to apply a dataset (glib API) instead. The
 * problem? You can't add indexing to it and you couldn't sort the elements by
 * collumn. And we needed it for a school assignment. So I came up with the
 * boring job to create a copy of the famous SQL Table and add the ability to
 * perform indexing to make it somewhat more efficient.
 */
#include "../includes/table.h"

#include <glib-2.0/glib.h>
#include <stdarg.h> /* va_list, va_start, va_arg, va_end */
#include <stdio.h>  /* perror */
#include <stdlib.h> /* malloc */
#include <string.h>

/* Private declarations */
#include "../includes/generic.h"
#include "../includes/helpers.h"
#include "../includes/memory.h"
#include "../includes/search.h"
#include "../includes/table_p.h"
#include "../../../view/pagination/includes/show.h"

typedef struct print_table {
	int width;
	int fields;
	HEADER header;
} * PRINT_TABLE;

typedef struct set_aux {
	TABLE * return_table;
	int * columns;
} * SET_AUX;

/**
 * @title: Table
 * @short_description: data strucure for data storing and querying.
 * 	otimizations are also implemented
 *
 * This tables are supposed to emulate the typical database tables. You can
 * choose to index some collumns to make it more eficient for queries using that
 * atribute.
 *
 * You can create indexing but don't overuse it :) The more indexing the more
 * over-head for management. And thus efficiency is lost...
 *
 * To create a new table with a printf like arguments, use table_new().
 * If you want a more generic aproach tou can use table_new_generic(). This last
 * version is good if you want to automate.
 *
 * To append content use table_append(). For a more generic aproach use
 * table_new_generic(). (If you want to automate things :) ).
 *
 * To explain how it works, if you create a new table then you have to specify
 * an atribute as an index. The table created will only be optimized to the
 * index column. This way the average case for searching the index column will
 * be O(log n). For searchs using other non-indexed columns will be O(n).
 *
 * Don't forget to destroy the table after using it. Otherwise you'll
 * have a lot of information not freed.
 *
 * Still to add: destroy function
 */

int table_size(TABLE *t) { return g_tree_nnodes(t->gtree[t->index]); }

HEADER get_headers(TABLE *t) { return t->header; }

int get_fields(TABLE *t) { return t->fields; }

char **get_header_names(HEADER header, int n_fields) {
	char **headers = malloc((sizeof(char *)) * n_fields);
	for (int i = 0; i < n_fields; i++) {
		headers[i] = strdup(header[i].field_name);
	}
	return headers;
}

int *get_header_types(HEADER header, int n_fields) {
	int *types = malloc((sizeof(int)) * n_fields);
	for (int i = 0; i < n_fields; i++) {
		types[i] = header[i].type;
	}

	return types;
}

void *get_row_content_by_column(ROW r, int column) {
	// void *content = r[column].cont;
	//// Needs to be freed
	// void *content_copy = malloc(sizeof(r[column].size));

	// void_ptr_generic_insert(content_copy, r[column].type, content);

	return r[column].cont;
}

int find_column_header(HEADER header, char *header_cmp, int n_fields) {
	for (int i = 0; i < n_fields; i++) {
		if (!strcmp(header[i].field_name, header_cmp)) return i;
	}
	return -1;
}

void *get_row_content_by_header(ROW r, HEADER header, char *header_cmp,
				int n_fields) {
	int column = find_column_header(header, header_cmp, n_fields);

	void *content_copy = get_row_content_by_column(r, column);

	return (void *)content_copy;
}

ROW row_copy_with_headers(int dest_fields_n, ROW r_orig, HEADER orig_header,
			  int orig_fields_n, char **headers_out) {
	ROW aux = alloc_row(dest_fields_n);
	HEADER h_dest = alloc_header(dest_fields_n);
	ROW r_dest;

	for (int orig_cont = 0, dest_cont = 0; orig_cont < orig_fields_n;
	     orig_cont++) {
		if (belong(orig_header[orig_cont].field_name, headers_out,
			   dest_fields_n)) {
			aux[dest_cont] = r_orig[orig_cont];
			h_dest[dest_cont] = orig_header[orig_cont];
			
			//	alloc_cell_cont(&r_dest[dest_cont],
			//			orig_header[orig_cont].size);
			//	cell_generic_insert(
			//	    &r_dest[dest_cont], r_orig[orig_cont].type,
			//	    r_orig[orig_cont].size,
			//	    get_row_content_by_column(r_orig,
			// orig_cont));
			dest_cont++;
		}
	}
	r_dest = row_copy(dest_fields_n, aux, h_dest);
	free(aux);
	free(h_dest);
	return r_dest;
}

ROW row_copy(int fields, ROW row, HEADER header) {
	int i;
	ROW r = alloc_row(fields);

	for (i = 0; i < fields; i++) {
		alloc_cell_cont(&r[i], header[i].size);
		cell_generic_insert(&r[i], header[i].type, header[i].size,row[i].cont);
		r[i].row_ptr = r;
	}
	return r;
}

/**
 * row_cmp:
 * @row1: Row to be compared
 * @row2: Row to be compared
 *
 * Compares to rows
 *
 * Returns: Result of the comparison
 */

gint row_cmp(gconstpointer row1, gconstpointer row2) {
	return strcmp(*(char **)row1, *(char **)row2);
}

/**
 * table_new_generic:
 * @fields: number of fields of the desired table
 * @types: Array of types
 * @headers: Array of strings for the headers name
 *
 * Creates a new TABLE and prepares all the resources needed for it management
 *
 * Returns: A pointer to the table
 */
TABLE *table_new_generic(int fields, int index, int *types, char **headers) {
	TABLE *t = alloc_table(fields);
	t->fields = fields;
	t->index = index;
	// t->gtree[index] = g_tree_new(row_cmp);
	int i = 0;
	while (i < fields) {
		header_generic_insert(&t->header[i], types[i], headers[i], i);
		i++;
	}
	int *type_data = &t->header[t->index].type;
	t->gtree[index] =
	    g_tree_new_full(key_generic_cmp, type_data, NULL, NULL);
	return t;
}
/**
 * table_new:
 * @fields: number of fields to be inserted
 * @fmt: The desired format of the column
 * 	Example: The format "s s" would mean the first and second column are of
 * 	type string.
 * @...: The name of the headers.
 *
 * Parses the arguments and calls table_new_generic
 *
 * Returns: The pointer to the new table
 */
TABLE *table_new(int fields, int index, const char *fmt, ...) {
	TABLE *t;
	va_list ap;
	va_start(ap, fmt);
	int i = 0;
	int types[fields];
	char *headers[fields];

	for (i = 0; i < fields; i++) {
		headers[i] = va_arg(ap, char *);
		fmt_generic_type(fields, types, fmt);
	}

	va_end(ap);
	t = table_new_generic(fields, index, types, headers);

	return t;
}

/**
 * table_append_generic:
 * @t: Pointer to the table
 * @args: Array of pointers to content
 *
 * Allocs the arguments received to the cell and assigns the cells to a row.
 * 	Inserts the row to the binary tree.
 *
 * Returns: The exit status
 */
int table_append_generic(TABLE *t, void **args) {
	if (t == NULL) {
		perror("TABLE was not correctly initiated");
		return -1;
	}
	int i;
	ROW r = alloc_row(t->fields);

	// Repeated code from/row_copy possibly changes might apply
	for (i = 0; i < t->fields; i++) {
		// Can't forget to free in delete function
		alloc_cell_cont(&r[i], t->header[i].size);
		cell_generic_insert(&r[i], t->header[i].type, t->header[i].size,
				    args[i]);
		r[i].row_ptr = r;
	}

	table_insert_internal(t, r[t->index].cont, r);

	for (i = 0; i < t->fields; i++) {
		GTree *tmp = t->gtree[i];
		//gpointer value;
		GPtrArray *dups;
		if (tmp && i != t->index) {
		//	GTreeNode *node;
			// Check if key is duplicate
			// If it is not then create a new array
			if ((dups = g_tree_lookup(tmp, r[i].cont)) == NULL)
				dups = g_ptr_array_new();

			// Append the row value to the array
			ROW val = r;
			g_ptr_array_add(dups,val);

			// Insert the now appended row to the tree
			table_indexed_insert(tmp, r[i].cont, dups);
			
		}
	}
	return 0;
}
/**
 * table_append:
 * @t: Pointer to the table
 *
 * Parses the arguments and calls table_append_generic().
 *
 * Returns: The exit status
 */
int table_append(TABLE *t, ...) {
	if (t == NULL) {
		perror("TABLE was not correctly initiated");
		return -1;
	}
	// Creates an instance of type va_list object type
	va_list ap;
	va_start(ap, t);
	void *args[t->fields];

	for (int i = 0; i < t->fields; i++) {
		// int type = t->header->type;
		switch (t->header[i].type) {
			case COL_TYPE_STRING:
				args[i] = (void *)va_arg(ap, char *);
				break;
			case COL_TYPE_INT:
				args[i] = (void *)va_arg(ap, int *);
				break;
			case COL_TYPE_CHAR:
				args[i] = (void *)va_arg(ap, char *);
				break;
			case COL_TYPE_FLOAT:
				args[i] = (void *)va_arg(ap, float *);
				break;
			case COL_TYPE_DOUBLE:
				args[i] = (void *)va_arg(ap, double *);
				break;
			default:
				break;
		}
	}

	va_end(ap);
	table_append_generic(t, args);

	// TODO: create error defines
	return 0;
}
/**
 * table_destroy:
 * @t: Pointer to the table
 *
 * Frees all the content from the table
 */
void table_destroy(TABLE *t) {
	free_header(t->header, t->fields);
	g_tree_foreach(t->gtree[t->index], gtree_free_row, &t->fields);
	g_tree_destroy(t->gtree[t->index]);
	free_gtree(t->gtree);
	free(t);
}

gint gtree_free_row(gpointer key, gpointer value, gpointer data) {
	int fields = *(int *)data;
	ROW row = (ROW)value;
	free_row(row, fields);
	return FALSE;
}

TABLE *table_new_header(int fields, int index, HEADER header) {
	int types[fields];
	char *headers[fields];
	int i;

	for (i = 0; i < fields; i++) {
		types[i] = header[i].type;
		headers[i] = strdup(header[i].field_name);
	}

	TABLE *r = table_new_generic(fields, index, types, headers);

	for (i = 0; i < fields; i++) free(headers[i]);

	return r;
}

int table_insert_internal(TABLE *t, gpointer key, gpointer value) {
	g_tree_replace(t->gtree[t->index], key, value);
	return 0;
}

int table_append_row(TABLE *t, ROW row) {
	void **args = malloc(t->fields * sizeof(void *));
	for (int i = 0; i < t->fields; i++)
		args[i] = get_row_content_by_column(row, i);
	table_append_generic(t, args);
	return 0;
}

/* Indexing */
/**
 * table_add_indexing:
 * @t: pointer to the table
 * @index: index for indexing
 *
 * If there isn't a indexing tree associated with the collumn index, then
 * creates a new one.
 *
 * Returns: If successful returns 0, otherwise -1
 */
int table_add_indexing(TABLE *t, int index) {
	// int i;

	if (t->gtree[index] != NULL) return -1;
	t->gtree[index] = g_tree_new_full(key_generic_cmp,
					  &(t->header[index].type), NULL, NULL);
	return 0;
}

int table_indexed_insert(GTree *gt, void *key, GPtrArray *row_array) {
	g_tree_insert(gt, key, row_array);
	return 0;
}

/* End of Indexing */

/* String and File functions */
/* Needs cleaning and critical thinking */
/* Used only for testing not ready for being used */
GString *string_line(GString *g, int width) {
	int i;
	g_string_append_c(g, '+');
	for (i = 0; i < width; i++) g_string_append_c(g, '-');
	g_string_append(g, "+\n");
	return g;
}

int header_to_string(TABLE *t, GString *g) {
	int i;
	int width = 0;
	for (i = 0; i < t->fields; i++)
		width += strlen(t->header[i].field_name);
	// Padding
	width += ((t->fields) * 2) + 8;
	string_line(g, width);
	g_string_append_printf(g, "| ");
	for (i = 0; i < t->fields; i++)
		g_string_append_printf(g, "%s | ", t->header[i].field_name);
	g_string_append_printf(g, "\n");
	string_line(g, width);
	return width;
}

GString *row_to_string(TABLE *t, ROW r, GString *g, int width) {
	int col_len = (width / t->fields) - 4;
	string_line(g, width);
	putchar('|');
	for (int i = 0; i < t->fields; i++) {
		g_string_append_printf(g, "%.*s |", col_len, (char *)r[i].cont);
	}
	g_string_append_c(g, '\n');
	string_line(g, width);
	return g;
}

void print_content(void *content, int type) {
	switch (type) {
		case COL_TYPE_INT:
			printf("%d |", *(int *)content);
			break;
		case COL_TYPE_CHAR:
			printf("%c |", *(char *)content);
			break;
		case COL_TYPE_FLOAT:
			printf("%f |", *(float *)content);
			break;
		case COL_TYPE_STRING:
			printf("%s |", *(char **)content);
			break;
		case COL_TYPE_DOUBLE:
			printf("%f |", *(double *)content);
			break;
		default:
			break;
	}
}

static gint print_row(gpointer key, gpointer value, gpointer data) {
	PRINT_TABLE args = (PRINT_TABLE)data;
	ROW row = (ROW)value;

	printf("| ");
	for (int i = 0; i < args->fields; i++) {
		print_content(row[i].cont, row[i].type);
	}

	putchar('\n');

	return FALSE;
}

char *table_to_file(FILE *fp, TABLE *t) {
	GString *g = g_string_new("");
	int width = header_to_string(t, g);

	PRINT_TABLE args = malloc(sizeof(struct print_table));

	args->width = width;
	args->fields = t->fields;
	args->header = t->header;

	printf("%s", g->str);
	g_tree_foreach(t->gtree[t->index], print_row, args);

	return NULL;
}

int table_append_generic_gk(TABLE * t, void ** args, tpointer (* func) (tpointer, tpointer, tpointer, tpointer), tpointer user_data, tpointer row1, tpointer row2, tpointer new_row) {

	if (t == NULL) {
		perror("TABLE was not correctly initiated");
		return -1;
	}
	int i;
	ROW r = alloc_row(t->fields);

	// Repeated code from row_copy possibly changes might apply
	for (i = 0; i < t->fields; i++) {
		// Can't forget to free in delete function
		alloc_cell_cont(&r[i], t->header[i].size);
		cell_generic_insert(&r[i], t->header[i].type, t->header[i].size, args[i]);
		r[i].row_ptr = r;
	}

	table_insert_internal(t, func(row1, row2 ,new_row ,user_data), r);

	return 0;
}

int table_append_row_gk (TABLE * t, ROW row, tpointer (* func) (tpointer, tpointer, tpointer, tpointer), tpointer r1, tpointer r2, tpointer user_data) {
	
	void **args = malloc(t->fields * sizeof(void *));
	for (int i = 0; i < t->fields; i++)
		args[i] = get_row_content_by_column(row, i);

	table_append_generic_gk(t, args, func, user_data, r1, r2, row);
	
	return 0;
}

ROW table_last_row (TABLE * t) {
	return (g_tree_node_value (g_tree_node_last (t->gtree[t->index])));
}


ROW row_create (void ** args, int * types, int size) {
	ROW r = alloc_row (size);

	for (int i = 0; i < size; i++) {
		switch (types[i]) {
			case COL_TYPE_STRING:
				alloc_cell_cont(&r[i], sizeof (char **));
				cell_generic_insert(&r[i], types[i], sizeof (char *), args[i]);
				break;
			case COL_TYPE_FLOAT:
				alloc_cell_cont(&r[i], sizeof (float *));
				cell_generic_insert(&r[i], types[i], sizeof (float), args[i]);
				break;
			case COL_TYPE_INT:
				alloc_cell_cont(&r[i],sizeof (int *));
				cell_generic_insert(&r[i], types[i], sizeof (int), args[i]);
				break;
		}
		r[i].row_ptr = r;
	}
	return r;
}


int table_set_columns_helper (tpointer key, tpointer value, tpointer user_data) {

	struct set_aux * aux = user_data;
	TABLE * return_table = aux->return_table;
	void ** args = malloc (sizeof (get_fields (return_table)));
	//ROW row = (ROW) value;
	int * columns = aux->columns;

	for (int i = 0; i < get_fields (return_table); i++)
		args[i] = get_row_content_by_column (value, columns[i]);	

	table_append_generic (return_table, args);
	return 0;
}

TABLE * table_set_columns (TABLE * t, int * cols, int num_cols) {
	
	HEADER header_t = get_headers (t);
	char ** header_names = get_header_names (header_t, get_fields (t));
	int * header_types = get_header_types (header_t, get_fields (t));

	char ** header_names_return = malloc (sizeof (char *) * num_cols);
	int * header_types_return = malloc (sizeof (int) * num_cols);

	int i;
	for (i = 0; i < num_cols; i++) {
		header_names_return[i] = header_names[cols[i]];
		header_types_return[i] = header_types[cols[i]];
	}

	TABLE * return_table = table_new_generic (num_cols, 0, header_types_return, header_names_return);
	
	struct set_aux aux;
	aux.return_table = return_table;
	aux.columns = cols;

	g_tree_foreach(t->gtree[t->index], table_set_columns_helper, &aux);

	return return_table;
}
