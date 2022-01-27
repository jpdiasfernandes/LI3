#include <ctype.h>

#include "../includes/helpers.h"
#include "../includes/generic.h"
#include "../includes/table.h"
#include "../includes/table_p.h"
#include "../includes/search.h"
#include "../includes/memory.h"

typedef struct aux_info {
	
	TABLE * table;
	TABLE * cmp_table;
	void * content;
	int type;
	HEADER header;
	char * header_cmp;
	int n_fields;

} * AUX_INFO;

typedef struct aux_position {
	int row_number;
	int row_column;
	TABLE * return_table;
	int * node_control;
} * AUX_POSITION;

typedef struct aux_join {
	TABLE * table;
	TABLE * cmp_table;
	HEADER header;
	char * header_cmp;
	char ** headers_out;
	int n_fields;
	int t1_quant;
	int t2_quant;
	tpointer (*func) (tpointer, tpointer, tpointer, tpointer);
	tpointer user_data;
} * AUX_JOIN;

typedef struct aux_foreach_id {
	tpointer user_data;
	void (*func) (tpointer, tpointer);
} * AUX_FOREACH_ID;

ROW table_search_row_id(TABLE *t, void *key) {
	ROW r =  (ROW) g_tree_lookup (t->gtree[t->index], key);
	return r;
}

int traverse_append_row_by_position (tpointer key, tpointer value, tpointer user_data) {
	 
	/* cast <user_data> */
	AUX_POSITION data = (AUX_POSITION) user_data;
	int row_number = data->row_number;
	int row_column = data->row_column;
	TABLE * r = data->return_table;

	/* cast <value> */
	ROW current_row = (ROW) value;

	void * column_value;

	if (*(data->node_control) < row_number) {*(data->node_control) = *(data->node_control) + 1; return 0;}
	if (*(data->node_control) == row_number) {
		
		column_value = get_row_content_by_column(current_row, row_column);
		table_append_generic (r, &column_value);
		
		return 1;
	}
	return 0;
}

TABLE * table_search_position(TABLE * t, int row_number, int row_column) {

	/* get content to create <return_table> */
	char ** header_names = get_header_names (get_headers (t), get_fields (t));
	char * header_name = header_names[row_column];
	int * types = get_header_types (get_headers (t), get_fields (t));
	int type = types[row_column];

	/* declaration of <return_table> */
	TABLE * return_table = NULL;
  switch (type) {
		case COL_TYPE_INT:
			return_table = table_new (1, 0, "d", header_name);
			break;
		case COL_TYPE_FLOAT:
			return_table = table_new (1, 0, "f", header_name);
			break;
		case COL_TYPE_STRING:
			return_table = table_new (1, 0, "s", header_name);
			break;
		default:
			break;
	}	

	/* fill <user_data> for <foreach> */
	struct aux_position user_data;
	user_data.return_table = return_table;
	user_data.row_number = row_number;
	user_data.row_column = row_column;
	int node_control[1];
	node_control[0] = 0;
	user_data.node_control = node_control;
		
	g_tree_foreach (t->gtree[t->index], traverse_append_row_by_position, &user_data);
	return return_table;
}

int traverse_append_row_by_cont(gpointer key, gpointer value, gpointer user_data) {
	
	/* cast user_data */
	AUX_INFO aux_info = (AUX_INFO) user_data;
 
	/* take <user_data> info */
	void * cont = (void *) aux_info->content;
	TABLE * t = (TABLE *) aux_info->table;
	int type = (int) aux_info->type;
	HEADER header = (HEADER) aux_info->header;
	char * header_cmp = (char *) aux_info->header_cmp;
	int n_fields = (int) aux_info->n_fields;

	/* declaration of a row to use in the following function */
	ROW r =(ROW)value;

	void * h_cont;
	/* get <header_content> to compare with <header_cmp> */
	h_cont = get_row_content_by_header(r, header, header_cmp, n_fields);
	
	int cmp = key_generic_cmp(h_cont, cont, &type);

	if(cmp == 0) {
                /* Get headers_out from aux_info->table */
                char **headers_out = malloc(sizeof(char *) * n_fields);
                for(int i = 0; i < n_fields; i++)
                	headers_out[i] = (char *)t->header[i].field_name;
                                                                                          
                ROW tmp = row_copy_with_headers(get_fields(t), value, header, n_fields, headers_out);
                table_append_row(t, tmp);
	}
	return FALSE;
}

int traverse_append_row_by_letter(gpointer key, gpointer value, gpointer user_data) {
	
	/* cast user_data */
	AUX_INFO aux_info = (AUX_INFO) user_data;
 
	/* take <user_data> info */
	void * cont = (void *) aux_info->content;
	TABLE * t = (TABLE *) aux_info->table;
	HEADER header = (HEADER) aux_info->header; /* header of <foreach table> */
	char * header_cmp = (char *) aux_info->header_cmp; /* comparation header */
	int n_fields = (int) aux_info->n_fields; /* number of fields of <foreach table> */

	/* declaration of a row to use in the following function */
	ROW r =(ROW)value;

	void * h_cont;
	/* get <header_content> to compare with <header_cmp> */
	h_cont = (char *) get_row_content_by_header (r, header, header_cmp, n_fields);

	char first_key_letter =	** (char **) h_cont;
	int type_char = COL_TYPE_CHAR;

	int cmp = key_generic_cmp(&first_key_letter, cont, (gpointer) &(type_char));
	if (cmp != 0 && (* (char *) cont < 97)) {
		*(char *)cont = tolower (* (int *)cont);
		cmp = key_generic_cmp(&first_key_letter, cont, (gpointer) &(type_char));
	} else if (cmp != 0 && (* (char *) cont >= 97)) {
		*(char *)cont = toupper (* (int *)cont);
		cmp = key_generic_cmp(&first_key_letter, cont, (gpointer) &(type_char));
	}

	if (cmp > 0)
		return 0;
	else if (cmp < 0)
		return 0;
	else {
        /* Get headers_out from aux_info->table */
				char ** headers_out = get_header_names(get_headers (t), get_fields (t));
        
				ROW tmp = row_copy_with_headers(get_fields (t), value, header, n_fields, headers_out);
        table_append_row(t, tmp);
	}
	return 0;
}

void traverse_indexed_append(gpointer row_ptr, gpointer user_data) {
	AUX_INFO aux_info = (AUX_INFO) user_data;
 
	/* take <user_data> info */
	TABLE * t = (TABLE *) aux_info->table;
	HEADER header = (HEADER) aux_info->header;
	int n_fields = (int) aux_info->n_fields;

	char **headers_out = malloc(sizeof(char *) * n_fields);
                for(int i = 0; i < n_fields; i++)
                	headers_out[i] = (char *)t->header[i].field_name;

        ROW tmp = row_copy_with_headers(t->fields, row_ptr, header, n_fields, headers_out);

	/* append <new_row> in <return-table> */
        table_append_row(t, tmp);
}
TABLE *table_search_row(TABLE *t, char *header_in, char **headers_out, int h_quant, void *cont) {
	int i;

	/* take all <info> informations about <header_in> */
	INFO info = header_helper_type(t->header, t->fields, header_in);
	/* alloc memmory for <new header_out> */
	HEADER tmp = calloc(h_quant, sizeof(INFO));

	/* Check if tmp[i] is null. Headers_out needs to have an unique id */
	for (i = 0; i < h_quant; i++)
		tmp[i] = header_helper_type(t->header, t->fields, headers_out[i]);
	
	/* return table */
	TABLE *r = table_new_header(h_quant, t->index, tmp);

	/* declaration of <aux_info> and fill */
	struct aux_info aux_info;
	aux_info.content = cont;
	aux_info.table = r;
	aux_info.type = info.type;
	aux_info.header = get_headers (t);
	aux_info.header_cmp = header_in;
	aux_info.n_fields = get_fields (t);

	/* declaration of the information that goes to <traverse_append_row_by_cont> */
	gpointer aux = (void *) &aux_info;

	if (t->gtree[info.header_no] == NULL) {
		/* the column isn't indexed */
		
		/* traverse in the tree to select and add in new table the match information */
		g_tree_foreach(t->gtree[t->index], traverse_append_row_by_cont, aux);
	
	} else {
		/* the column is indexed */

		/* get lower bound node that is equal to <content> key */
		GPtrArray *dups = g_tree_lookup(t->gtree[info.header_no], cont);
		/* there wasn't a match key */
		if (dups == NULL) return NULL;
		
		g_ptr_array_foreach(dups, traverse_indexed_append, aux);
	}

	return r;
}

TABLE *table_search_letter(TABLE *t, char *header_in, char **headers_out,
			   int h_quant, char letter) {
	
	int i;
	INFO info = header_helper_type(t->header, t->fields, header_in);
	HEADER tmp = calloc(h_quant, sizeof(INFO));

	// Check if tmp[i] is null
	// headers_out needs to have an unique id
	for (i = 0; i < h_quant; i++)
		tmp[i] =
		    header_helper_type(t->header, t->fields, headers_out[i]);

	TABLE *r = table_new_header(h_quant, t->index, tmp);

	/* declaration of <aux_info> and fill */
	struct aux_info aux_info;
	aux_info.content = &letter;
	aux_info.table = r;
	aux_info.type = info.type;
	aux_info.header = get_headers (t);
	aux_info.header_cmp = header_in;
	aux_info.n_fields = get_fields (t);
	
	/* declaration of the information that goes to <traverse_append_row_by_cont> */
	gpointer aux = (void *) &aux_info;

	if (t->gtree[info.header_no] == NULL) {
		/* traverse in the tree to select and add in new table the match information */
		g_tree_foreach(t->gtree[t->index], traverse_append_row_by_letter, aux);
	
	} else {
		// The collumn is indexed
		char string_letter[1] = {letter};
		GTreeNode *node = g_tree_lower_bound(t->gtree[info.header_no], string_letter);
		if (node == NULL || (*(char **)g_tree_node_key(node))[0] != letter) return NULL;

		GPtrArray *dups;
		int char_type = COL_TYPE_CHAR;
		while(node != NULL && key_generic_cmp( (*(char **)g_tree_node_key(node)), &letter, &char_type) == 0) {
			dups = g_tree_node_value(node);

			/* Inserts the rows associated with key */
			g_ptr_array_foreach(dups, traverse_indexed_append, aux);

			/* Gets next node */
			node = g_tree_node_next(node);
		}
	}

	return r;
}

int sum_traverse_column(gpointer key, gpointer value, gpointer user_data) {
	
	AUX_INFO aux = (AUX_INFO) user_data;
	float *r = (float *) aux->content; 
	int index = (int) aux->type;

	ROW row = (ROW)value;
	*r += *(float *)row[index].cont;
	return FALSE;
}

float table_column_sum(TABLE * t, char *header) {
	float r = 0;
	INFO info = header_helper_type(t->header, t->fields, header);

	/* declaration of <aux_info> and fill for the <g_tree_foreach> */
	struct aux_info aux_info;
	aux_info.content = &r;
	aux_info.table = NULL;
	aux_info.type = info.header_no;

	/* declaration of the information that goes to <traverse_append_row_by_cont> */
	gpointer aux = (void *) &aux_info;
	/* traverse in the tree to select and add in new table the match information */
	g_tree_foreach(t->gtree[t->index], sum_traverse_column, aux);
	
	return r;
}


void table_search_foreach(TABLE * t, int (*func) (tpointer, tpointer, tpointer), tpointer user_data) {

		g_tree_foreach(t->gtree[t->index], func, user_data);

}

int traverse_foreach_indexed(tpointer key, tpointer value, tpointer user_data) {

	GPtrArray *dups = (GPtrArray *) value;

	AUX_FOREACH_ID aux = user_data;
	void (*func) (tpointer, tpointer) = aux->func;
	tpointer aux_data = aux->user_data;
	
	g_ptr_array_foreach(dups, func, aux_data);

	/* to iterate through all the entries */
	return 0;
}

int table_search_foreach_indexed(TABLE * t, int index, void (*func) (tpointer, tpointer), tpointer user_data) {
	
	/* if the column is not indexed return error */
	if (t->gtree[index] == NULL) return -1;

	/* declare aux and fill */
	struct aux_foreach_id aux;
	aux.func = func;
	aux.user_data = user_data;

	/* iterate and apply <traverse_foreach_indexed> */
	g_tree_foreach(t->gtree[index], traverse_foreach_indexed, &aux);

	return 0;
}

ROW row_join (ROW r1, ROW r2, HEADER header_final, int h1, int h2) {
	ROW row = alloc_row(h1 + h2);

	for (int i = 0; i < h1; i++) {
		alloc_cell_cont(&row[i], header_final[i].size);
		cell_generic_insert(&row[i], header_final[i].type, header_final[i].size, r1[i].cont);
		row[i].row_ptr = row;
	}
	
	for (int i = 0; i < h2; i++) {
		alloc_cell_cont(&row[h1 + i], header_final[h1 + i].size);
		cell_generic_insert(&row[h1 + i], header_final[h1 + i].type, header_final[h1 + i].size, r2[i].cont);
		row[h1 + i].row_ptr = row;
	}

	return row;
}

int traverse_join(tpointer key, tpointer value, tpointer user_data) {
	/* casts user_data */
	AUX_JOIN data = (AUX_JOIN) user_data;

	/* get user_data info */
	TABLE *return_table = data->table;
	TABLE *t2 = data->cmp_table;
	HEADER header_t1 = data->header;
	HEADER header_t2 = get_headers(t2);
	char ** headers_out = data->headers_out;
	int n_fields_t1 = data->n_fields;
	int n_fields_t2 = get_fields(t2);
	int h1_quant = data->t1_quant;
	int h2_quant = data->t2_quant;
	tpointer (*func) (tpointer, tpointer, tpointer, tpointer) = data->func;

	/* get current node values */
	ROW node_t1 = (ROW) value;
	void * id_t1 = key;

	/* find ROW in t2 with same id */
	ROW node_t2 = table_search_row_id(t2, id_t1);
	
	/* id does not exist in <t2_table> */
	if (node_t2 == NULL) return 0;
	
	/* declaration of ROW to append in <return_table> */
	ROW new_row_t1 = row_copy_with_headers(h1_quant, node_t1, header_t1, n_fields_t1, headers_out);
	ROW new_row_t2 = row_copy_with_headers(h2_quant, node_t2, header_t2, n_fields_t2, &headers_out[h1_quant]);

	/* join rows */
	ROW new_row = row_join(new_row_t1, new_row_t2, get_headers(return_table), h1_quant, h2_quant);
	
//	free_row(new_row_t1, h1_quant);
//	free_row(new_row_t2, h2_quant);

	//table_append_row(return_table, new_row);
	table_append_row_gk(return_table, new_row, func, node_t1, node_t2, user_data);

	return 0;

}

TABLE * table_join (TABLE * t1, TABLE * t2, char **headers_out, int h1, int h2, int *types, 
										tpointer (*func) (tpointer, tpointer, tpointer, tpointer), tpointer user_data) {

	int index1 = t1->index;
	int index2 = t2->index;
	int h_total = h1 + h2;
	
	if(strcmp(t1->header[index1].field_name, t1->header[index2].field_name) != 0) return NULL;

	/* index set to zero only to  use the function (does not meaning nothing) */
	TABLE *return_table = table_new_generic(h_total, 0, types, headers_out);

	struct aux_join aux;
	aux.header = t1->header;
	aux.table = return_table;
	aux.cmp_table = t2;
	aux.n_fields = get_fields(t1);
	aux.t1_quant = h1;
	aux.t2_quant = h2;
	aux.headers_out = headers_out;
	aux.user_data = user_data;
	aux.func = func;
		
	g_tree_foreach(t1->gtree[index1], traverse_join, &aux);

	return return_table;
}

void table_search_foreach_inverse (TABLE * t, int (*func) (tpointer, tpointer, tpointer), tpointer user_data) {

		GTreeNode * node = g_tree_node_last (t->gtree[t->index]);
		ROW row = g_tree_node_value (node);
		gpointer key = g_tree_node_key ((GTreeNode *) row);
		int result = 0;
	
		while (result == 0 && (node != NULL)) {
			result = func (key, row, user_data);
			node = g_tree_node_previous (node);
			row = g_tree_node_value (node);
		}
}
