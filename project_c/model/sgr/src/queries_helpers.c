#include "../includes/queries_helpers.h"
#include "../../table/includes/search.h"
#include "../../table/includes/table.h"
#include "../includes/data.h"

struct filter_aux {
	TABLE * return_table;
	OPERATOR op;
	char * cmp;
	char * header;
	int fields;
	HEADER headers;
	int type;
};

struct q_4_aux {
	HEADER header;
	HEADER header_business;
	TABLE * t;
	TABLE * cmp;
	int n_fields;
};

struct q_5_aux {
	TABLE * t;
	TABLE * cmp;
	HEADER header_business_in_city;
	HEADER header_reviews;
	float stars;
};

struct q_6_aux {
	TABLE * return_table;
	char * last_city;
	char * current_city;
	int * top;
	int fix_top;
};

struct q_7_aux {
	TABLE * visited;
	TABLE * return_table;
	TABLE * businesses;
};

struct q_8_aux {
	TABLE * intermediate_table;
	TABLE * stats;
	TABLE * return_table;
	char * category;
	int * top;
};

struct q_9_aux {
	TABLE * return_table;
	char * word;
};

FILTER_AUX init_filter_aux () {
	FILTER_AUX f = malloc (sizeof (struct filter_aux));
	return f;
}

Q_4_AUX init_q_4_aux () {
	Q_4_AUX aux = malloc (sizeof (struct q_4_aux));
	return aux;
}

Q_5_AUX init_q_5_aux () {
	Q_5_AUX aux = malloc (sizeof (struct q_5_aux));
	return aux;
}

Q_6_AUX init_q_6_aux () {
	Q_6_AUX aux = malloc (sizeof (struct q_6_aux));
	return aux;
}

Q_7_AUX init_q_7_aux () {
	Q_7_AUX aux = malloc (sizeof(struct q_7_aux));
	return aux;
}

Q_8_AUX init_q_8_aux () {
	Q_8_AUX aux = malloc (sizeof (struct q_8_aux));
	return aux;
}

Q_9_AUX init_q_9_aux () {
	Q_9_AUX aux = malloc (sizeof (struct q_9_aux));
	return aux;
}
void filter_aux_set_return_table (FILTER_AUX f, TABLE * t) {
	f->return_table = t;
}

void filter_aux_set_operator (FILTER_AUX f, OPERATOR op) {
	f->op = op;
}

void filter_aux_set_cmp_value (FILTER_AUX f, char * cmp) {
	f->cmp = cmp;
}

void filter_aux_set_header (FILTER_AUX f, char * header) {
	f->header = header;
}

void filter_aux_set_headers (FILTER_AUX f, HEADER headers) {
	f->headers = headers;
}

void filter_aux_set_fields (FILTER_AUX f, int fields) {
	f->fields = fields;
}

void filter_aux_set_type (FILTER_AUX f, int type) {
	f->type = type;
}

void q4aux_set_header (Q_4_AUX q, HEADER header) {
	q->header = header;
}

void q4aux_set_n_fields (Q_4_AUX q, int n_fields) {
	q->n_fields = n_fields;
}

void q4aux_set_return_table (Q_4_AUX q, TABLE * t) {
	q->t = t;
}

void q4aux_set_cmp_table (Q_4_AUX q, TABLE * t) {
	q->cmp = t;
}

void q4aux_set_cmp_header_business (Q_4_AUX q, HEADER header) {
	q->header_business = header;
}

void q5aux_set_return_table (Q_5_AUX q, TABLE * t) {
	q->t = t;
}

void q5aux_set_cmp_table (Q_5_AUX q, TABLE * t) {
	q->cmp = t;
}

void q5aux_set_header_bussiness_in_city (Q_5_AUX q, HEADER header) {
	q->header_business_in_city = header;
}

void q5aux_set_header_reviews (Q_5_AUX q, HEADER header) {
	q->header_reviews = header;
}

void q5aux_set_stars (Q_5_AUX q, float stars) {
	q->stars = stars;
}

void q6aux_set_return_table (Q_6_AUX q, TABLE * t) {
	q->return_table = t;
}

void q6aux_set_last_city (Q_6_AUX q, char * city) {
	q->last_city = city;
}

void q6aux_set_current_city (Q_6_AUX q, char * current) {
	q->current_city = current;
}

void q6aux_set_top (Q_6_AUX q, int * top) {
	q->top = top;
}

void q6aux_set_fix_top (Q_6_AUX q, int top) {
	q->fix_top = top;
}

void q8aux_set_intermediate_table (Q_8_AUX q, TABLE * t) {
	q->intermediate_table = t;
}

void q8aux_set_stats_table (Q_8_AUX q, TABLE * t) {
	q->stats = t;
}

void q8aux_set_category (Q_8_AUX q, char * category) {
	q->category = category;
}

void q8aux_set_top (Q_8_AUX q, int * top) {
	q->top = top;
}

void q8aux_set_return_table (Q_8_AUX q, TABLE * t) {
	q->return_table = t;
}

void q7aux_set_visited (Q_7_AUX q, TABLE * visited) {
	q->visited = visited;
}

void q7aux_set_return_table (Q_7_AUX q, TABLE * return_table) {
	q->return_table = return_table;
}

void q7aux_set_businesses (Q_7_AUX q, TABLE * businesses) {
	q->businesses = businesses;
}

void q9aux_set_return_table (Q_9_AUX q, TABLE * return_table) {
	q->return_table = return_table;	
}

void q9aux_set_word (Q_9_AUX q, char * word) {
	q->word = word;
}
tpointer stats_gk_helper (tpointer row1, tpointer row2, tpointer newrow, tpointer user_data) {

	ROW new_row = (ROW) newrow;

	char **gk_r = malloc (sizeof (char *));
	gk_r[0] = malloc (sizeof (char) * 100);
	gk_r[0][0] = '\0';

	/* get city name */
	char * city_s = * (char **) get_row_content_by_column (new_row, 1);
	char * city = strdup (city_s);

	/* get mean_number of stars */
	float mean_stars = * (float *) get_row_content_by_column (new_row, 3);

	/* get <business_id> */
	char * business_id_s = * (char **) get_row_content_by_column (new_row, 2);
	char * business_id = strdup (business_id_s);
	
	/* declaration of buffer in order to have <mean> in <string> version */
	char mean_s[16];
	sprintf(mean_s, "%f", mean_stars);

	/* CREATE gk_lookup só para lembrar isso não é aqui */
	/* concat strings to get: <city#mean#business_id> */
	strcat(gk_r[0],city);
	strcat(gk_r[0],"#");
	strcat(gk_r[0],mean_s);
	strcat(gk_r[0],"#");
	strcat(gk_r[0],business_id);

	return gk_r;
}

tpointer char_gk_helper(tpointer row1, tpointer row2, tpointer newrow, tpointer user_data) {
	/* get index of the new table after join */
	int index = *(int *)user_data;


	ROW new_row = (ROW) newrow;

	/* get the row content of the index */
	char **gk_r = get_row_content_by_column(new_row, index);

	return gk_r;
}

tpointer q8_gk_helper (tpointer row1, tpointer row2, tpointer new_row, tpointer user_data) {
	
	char **gk_r = malloc (sizeof (char *));
	gk_r[0] = malloc (sizeof (char) * 100);
	gk_r[0][0] = '\0';

	void ** user = (void **) user_data; 
	
	/* get business_id */
	char * business_id_s = (char *) user[0];
	char * business_id = strdup (business_id_s);

	/* get mean_number of stars */
	float mean_stars = * (float *) user[1];
	
	/* declaration of buffer in order to have <mean> in <string> version */
	char mean_s[16];
	sprintf(mean_s, "%f", mean_stars);

	/* concat strings to get: <mean#business_id> */
	strcat(gk_r[0],mean_s);
	strcat(gk_r[0],"#");
	strcat(gk_r[0],business_id);
	
	return gk_r;

}

int businesses_reviewed_helper (tpointer key, tpointer value, tpointer user_data) {

	/* cast <user_data> */
	Q_4_AUX aux = (Q_4_AUX) user_data;

	/* get <user_data> infos */
	HEADER header = aux->header;
	HEADER header_business = aux->header_business;
	int n_fields = aux->n_fields;
	TABLE * t = aux->t;
	TABLE * cmp = aux->cmp;

	/* cast node (row) */
	ROW node = (ROW) value;

	/* get <business_id> of actual ROW */
	char * business_id = * (char **) get_row_content_by_header (node, header, "business_id", n_fields);

	/* get ROW with <business_id> index */
	ROW row = (ROW) table_search_row_id (cmp, &business_id);

	/* check if ROW is NULL */
	if (!row) return 0;

	/* get <business-name> from the <business ROW> matched by business_id in the <table_search_row_id> function */
	char * business_name = * (char **) get_row_content_by_header (row, header_business, "name", 5);

	/* insert <business_id> and <business_name> in the table */
	table_append (t, &business_id, &business_name);
	
	return 0;
}

int businesses_stars_and_city_helper (tpointer key, tpointer value, tpointer user_data) {
	
	/* cast <user_data> */
	Q_5_AUX aux = (Q_5_AUX) user_data;

	/* get <user_data> infos */
	TABLE * stats = aux->cmp;
	TABLE * return_table = aux->t;
	HEADER header_business_in_city = aux->header_business_in_city;
	float stars_user_data = aux->stars;
	/* cast node (ROW) */
	ROW node = (ROW) value;

	/* get <business_id> of actual ROW */
	char * business_id = * (char **) get_row_content_by_header (node, header_business_in_city, "business_id", 2);
	
	/* declaration of <headers_out> for the <search-function> */
	//char *headers_out[2] = {"review_id", "stars"};
	
	/* stars = table with 2 columns with the <stars-header> and <review_id-header> */
	//TABLE * table_stars = table_search_row (reviews, "business_id", headers_out, 2, &business_id);


	ROW stats_row = table_search_row_id(stats, &business_id);

	if (stats_row != NULL) {
		float mean_stars = *(float *)get_row_content_by_column(stats_row, 1);

		/* check if the <business_id> have more or equal than <n_stars> */
		if (mean_stars >= stars_user_data) {

			/* get <business_name> of actual ROW */
			char * business_name = * (char **) get_row_content_by_header (node, header_business_in_city , "name", 2);

			/* insert <business_id> and <business_name> in the <return_table> */
			table_append (return_table, &business_id, &business_name);
	
		}
	}

	return 0;
}

int top_businesses_by_city_helper (tpointer key, tpointer value, tpointer user_data) {
	
	/* cast <user_data> */
	Q_6_AUX aux = (Q_6_AUX) user_data;

	/* get <user_data> infos */
	int top = aux->fix_top;
	int * top_cont = aux->top;
	TABLE * return_table = aux->return_table;
	char * last_cit = aux->last_city;
	char * current_city = aux->current_city;

	/* cast node (ROW) */
	ROW node = (ROW) value;

	current_city = * (char **) get_row_content_by_column (node,1);

	if (strcmp (last_cit,current_city)) {*top_cont = top; aux->last_city = current_city; return 0;}

	if (*top_cont > 0) {
		char * name = * (char **) get_row_content_by_column (node,0);
		char * business_id = * (char **)get_row_content_by_column (node, 2);
		float mean_stars = * (float *)get_row_content_by_column (node, 3);
		
		void * args[4];
		args[1] = &current_city;
		args[3] = &mean_stars;
		args[2] = &business_id;
		args[0] = &name;

		int types[4] = {COL_TYPE_STRING, COL_TYPE_STRING, COL_TYPE_STRING, COL_TYPE_FLOAT};
		
		ROW row_append = row_create (args, types, 4);
	
		table_append_row_gk (return_table, row_append, stats_gk_helper, NULL, NULL, NULL);
		//table_append (return_table, &current_city, &business_id, &name, &mean_stars);

		aux->last_city = current_city;
		*top_cont = *top_cont -1;	
		return 0;
	}

	if (*top_cont < 0) {*top_cont = top; aux->last_city = NULL;};

	return 0;
}

int top_businesses_with_category_helper (tpointer key, tpointer value, tpointer user_data) {

	/* cast <user_data> */
	Q_8_AUX aux = (Q_8_AUX) user_data;

	/* get <user_data> info's */
	TABLE * intermediate_table = aux->intermediate_table; 
	TABLE * stats = aux->stats;
	char * category = aux->category;

	/* get <current-row> */
	ROW row = (ROW) value;

	/* get <categories> */
	char * categories = * (char **) get_row_content_by_column (row, 4);

	/* check if the business have the category */
	if (parsing_category (category, categories) == 0) return 0;
	
	/* If I'm here, the business have the category */

	/* get <business_id> in the <current-row> to find your <mean_stars> in the <stats> TABLE */
	char * business_id = * (char **) get_row_content_by_column (row, 0);
	ROW stats_row = table_search_row_id (stats, &business_id);

	if (stats_row == NULL) return 0;

	char * business_name = * (char **) get_row_content_by_column (row, 1);
	float mean_stars = * (float *) get_row_content_by_column (stats_row, 1);

	/* confirm */
	void * args[3];
	args[0] = &business_id;
	args[1] = &business_name;
	args[2] = &mean_stars;

	int types[3] = {COL_TYPE_STRING, COL_TYPE_STRING, COL_TYPE_FLOAT};

	/* create ROW with content */
	ROW append_row = row_create(args, types, 3);

	void * user_data_gk[2];
	user_data_gk[0] = business_id;
	user_data_gk[1] = &mean_stars;

	/* append ROW in intermediate_table with generator key function */
	table_append_row_gk (intermediate_table, append_row, q8_gk_helper , NULL, NULL, user_data_gk);

	return 0;
} 

int top_businesses_with_category_helper_2 (tpointer key, tpointer value, tpointer user_data) {

	/* cast <user_data> */
	Q_8_AUX aux = (Q_8_AUX) user_data;

	/* get <user_data> info's */
	TABLE * return_table = aux->return_table; 
	int * top = aux->top;

	/* get <current-row> */
	ROW row = (ROW) value;

	if (*top > 0)	{
	
		char * business_id = * (char **) get_row_content_by_column (row, 0);
		float mean_stars = * (float *) get_row_content_by_column (row, 2);
	
		void * user_data_gk[2];
		user_data_gk[0] = business_id;
		user_data_gk[1] = &mean_stars;

		/* append ROW in return_table with generator key function */
		table_append_row_gk (return_table, row, q8_gk_helper, NULL, NULL, user_data_gk);
		*top = *top -1;
		return 0;
	}

	return 1;
} 

void international_users_helpers(tpointer row, tpointer user_data) {
	/* get aux content */
	Q_7_AUX aux = (Q_7_AUX) user_data;
	TABLE * visited = aux->visited;
	TABLE * return_table = aux->return_table;
	TABLE * businesses = aux->businesses;

	/* get the present value of the row */
	ROW row_present = (ROW) row; 
	ROW row_cmp;

	/* user_id beeing visited */
	char * user_id = *(char **)get_row_content_by_column(row_present, 1);
	/* business that was reviewed by user_id */
	char * business_id = *(char **)get_row_content_by_column(row_present, 2);

	/* get state of the business */
	ROW business = table_search_row_id(businesses, &business_id);
	if (business == NULL) return;
	char * state = *(char **)get_row_content_by_column(business, 3);

	/* state that maybe visited */
	char * state_cmp; 

	/* if user_id was visited then check if state != state_cmp. if so add 
	 * add to return_table.
	 * if not visited then add to visited table. 
	 */
	if ((row_cmp = table_search_row_id(visited, &user_id)) != NULL ) {
		state_cmp = *(char **)get_row_content_by_column(row_cmp, 1);
		int aux = 0;
		if (strcmp(state_cmp, state) != 0)
			table_append(return_table, &user_id, &aux);
	}
	else table_append(visited, &user_id, &state);
}

int filter_aux (tpointer key, tpointer value, tpointer user_data) {
	
	/* cast <user_dat> */
	FILTER_AUX aux = (FILTER_AUX) user_data;

	/* get <user_data> infos */
	TABLE * return_table = aux->return_table;
	char * cmp = aux->cmp;
	char * header = aux->header;
	OPERATOR op = aux->op;
	int fields = aux->fields;
	HEADER headers = aux->headers;
	int type = aux->type;

	ROW current_row = (ROW) value;
	
	int cont_i = 0;
	float cont_f = 0;
	char * cont_s = NULL;
	int cmp_i = 0;
	float cmp_f = 0;

	switch (type) {
		case COL_TYPE_INT:
			if (sscanf(cmp, "%d", &cmp_i) == EOF) return 0; 
			cont_i = * (int *) get_row_content_by_header (current_row, headers, header, fields);
			break;
		case COL_TYPE_FLOAT:
			if (sscanf(cmp, "%f", &cmp_f) == EOF) return 0; 
			cont_f = * (float *) get_row_content_by_header (current_row, headers, header, fields);
			break;
		case COL_TYPE_STRING:
			cont_s = * (char **) get_row_content_by_header (current_row, headers, header, fields);
			break;
		default:
			break;
	}

	int check = 0;
	switch (op) {
		case LT:
			if (type == COL_TYPE_INT) {if (cont_i < cmp_i) check = 1;};
			if (type == COL_TYPE_FLOAT) {if (cont_f < cmp_f) check = 1;};
			if (type == COL_TYPE_STRING) {if (strcmp (cont_s, cmp) < 0) check = 1;}
			break;
		case EQ:
			if (type == COL_TYPE_INT) {if (cont_i == cmp_i) check = 1;};
			if (type == COL_TYPE_FLOAT) {if (cont_f == cmp_f) check = 1;};
			if (type == COL_TYPE_STRING) {if (!strcmp (cont_s, cmp)) check = 1;}
			break;
		case GT:
			if (type == COL_TYPE_INT) {if (cont_i > cmp_i) check = 1;};
			if (type == COL_TYPE_FLOAT) {if (cont_f > cmp_f) check = 1;};
			if (type == COL_TYPE_STRING) {if (strcmp (cont_s, cmp) > 0) check = 1;}
			break;
		default:
			break;
	}

	if (check == 0) return 0;

	/* all conditions for filter was validade */
	ROW row_cp = row_copy(fields, current_row, headers);
	table_append_row (return_table, row_cp);

	return 0;
}

int reviews_with_word_helper (tpointer key, tpointer value, tpointer aux) {

	Q_9_AUX data = (Q_9_AUX) aux;
	TABLE * return_table = data->return_table;
	char * word = data->word;

	ROW current_row = (ROW) value;
	char * cmp_word = *(char **)get_row_content_by_column(current_row, 8);
	
	int status = parsing_word(word, cmp_word);
	if (status == -1) return 0;

	char * review_id = *(char **) get_row_content_by_column(current_row, 0);
	table_append(return_table, &review_id);

	return 0;

}



