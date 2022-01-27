#include <stdio.h> /* Dependencies */
#include <unistd.h> /* sleep() */

#include "../../../view/messages/includes/messages.h"
#include "../includes/primary_functions.h"
#include "../../../view/pagination/includes/show.h"
#include "../../../model/table/includes/table.h"
#include "../../../model/sgr/includes/sgr.h"
#include "../../../model/sgr/includes/variables.h"
#include "../../../model/sgr/includes/data.h"
#include "../includes/stditp.h"
#include "../../../model/table/includes/search.h"
#include "../../../model/sgr/includes/queries_helpers.h"

/* ------- 50 % (insert more commands) */
void * PRIMARY_manual (_ARGS args) {
	/* get <user_data> (a TABLE in this case) */
	TABLE * t = (TABLE *) get_user_data (args);	
	
	table_pagination (t);

	return NULL;
}

/* ------- DONE */
void * PRIMARY_about_project (_ARGS args) {
	print_about_project ();
	return NULL;
}

/* ------- DONE */
void * PRIMARY_contribute (_ARGS args) {
	print_contribute ();		
	return NULL;
}

void * PRIMARY_load_sgr (_ARGS args) {
	char ** argv = get_args (args);
	char * users = argv[0];
	char * business = argv[1];
	char * reviews = argv[2];

	char * var = get_var (args);
	VAR_LIST var_sgr = (VAR_LIST) get_user_data (args);
	SGR sgr;

	if ((users = parsing_string (users,"\"")) == NULL) {print_error (NOT_VAR_SINTAX); set_status (args, ERROR); return NULL;}
	if ((business = parsing_string (business,"\"")) == NULL) {print_error (NOT_VAR_SINTAX); set_status (args, ERROR); return NULL;}
	if ((reviews = parsing_string (reviews,"\"")) == NULL) {print_error (NOT_VAR_SINTAX); set_status (args, ERROR); return NULL;}
	
	if ((sgr = get_var_list_value (var_sgr, var)) == NULL) {
		/* variable does not exist */
		sgr = load_sgr (users, business, reviews);
	} else {
		/* variable exist */
		destroy_sgr (sgr);
		sgr = load_sgr (users, business, reviews);
	}

	if (sgr == NULL) {set_status (args, ERROR);}
	var_list_insert (var_sgr, var, sgr);
	
	return NULL;
}

/* -------- DONE */
void * PRIMARY_businesses_started_by_letter (_ARGS args) {
	
	/* get user_data (contain VAR_LIST) */
	void ** user_data = get_user_data (args);
	VAR_LIST var_list = (VAR_LIST) user_data[0];
	VAR_LIST table_list = (VAR_LIST) user_data[1];

	/* get all args */
	char ** argv = get_args(args);
	
	/* get first arg -> a SGR */
	char * arg_SGR = argv[0];
	
	/* check if variable exists */
	SGR sgr;
	sgr = get_var_list_value (var_list, arg_SGR);
	if (sgr == NULL) {print_error (NOT_VAR); set_status (args, ERROR); return NULL;}

	/* get second arg -> a char */
	char * arg_CHAR = argv[1];

	/* parsing delim */
	arg_CHAR = parsing_string (arg_CHAR, "'");

	/* check parsing */
	if (arg_CHAR == NULL) {print_error (NOT_VAR_SINTAX); set_status (args, ERROR); return NULL;}
	
	/* declaration of TABLE to get <query> result */
	TABLE * t = businesses_started_by_letter (sgr, *arg_CHAR);

	/* get <var> to associate the result */
	char * var = get_var (args);

	/* insert in the VAR_LIST */
	var_list_insert (table_list, var, t);

	return NULL;
}

/* ------- DONE */
void * PRIMARY_business_info (_ARGS args) {

	/* get user_data (contain VAR_LIST) */
	void ** user_data = get_user_data (args);
	VAR_LIST var_list = (VAR_LIST) user_data[0];
	VAR_LIST table_list = (VAR_LIST) user_data[1];

	/* get all args */
	char ** argv = get_args(args);
	
	/* get first arg -> a SGR */
	char * arg_SGR = argv[0];
	
	/* check if variable exists */
	SGR sgr;
	sgr = get_var_list_value (var_list, arg_SGR);
	if (sgr == NULL) {print_error (NOT_VAR); set_status (args, ERROR); return NULL;}

	/* get second arg -> a (char *) */
	char * arg_BUSINESS_ID = argv[1];

	/* parsing delim */
	arg_BUSINESS_ID = parsing_string (arg_BUSINESS_ID, "\"");

	/* check parsing */
	if (arg_BUSINESS_ID == NULL) {print_error (NOT_VAR_SINTAX); set_status (args, ERROR); return NULL;}
	
	/* declaration of TABLE to get <query> result */
	TABLE * t = business_info (sgr, arg_BUSINESS_ID);

	/* get <var> to associate the result */
	char * var = get_var (args);

	/* insert in the VAR_LIST */
	var_list_insert (table_list, var, t);
	
	return NULL;
}

/* ------- DONE */
void * PRIMARY_businesses_reviewed (_ARGS args) {
	
	/* get user_data (contain VAR_LIST) */
	void ** user_data = get_user_data (args);
	VAR_LIST var_list = (VAR_LIST) user_data[0];
	VAR_LIST table_list = (VAR_LIST) user_data[1];

	/* get all args */
	char ** argv = get_args(args);
	
	/* get first arg -> a SGR */
	char * arg_SGR = argv[0];
	
	/* check if variable exists */
	SGR sgr;
	sgr = get_var_list_value (var_list, arg_SGR);
	if (sgr == NULL) {print_error (NOT_VAR); set_status (args, ERROR); return NULL;}

	/* get second arg -> a (char *) */
	char * arg_USER_ID = argv[1];

	/* parsing delim */
	arg_USER_ID = parsing_string (arg_USER_ID, "\"");

	/* check parsing */
	if (arg_USER_ID == NULL) {print_error (NOT_VAR_SINTAX); set_status (args, ERROR); return NULL;}
	
	/* declaration of TABLE to get <query> result */
	TABLE * t = businesses_reviewed (sgr, arg_USER_ID);

	//ak0TdVmGKo4pwqdJSTLwWw
	char * var = get_var (args);

	/* insert in the VAR_LIST */
	var_list_insert (table_list, var, t);
	
	return NULL;
}

/* ------- DONE */
void * PRIMARY_businesses_with_stars_and_city (_ARGS args) {
	
	/* get user_data (contain VAR_LIST) */
	void ** user_data = get_user_data (args);
	VAR_LIST var_list = (VAR_LIST) user_data[0];
	VAR_LIST table_list = (VAR_LIST) user_data[1];

	/* get all args */
	char ** argv = get_args(args);
	
	/* get first arg -> a SGR */
	char * arg_SGR = argv[0];
	
	/* check if variable exists */
	SGR sgr;
	sgr = get_var_list_value (var_list, arg_SGR);
	if (sgr == NULL) {print_error (NOT_VAR); set_status (args, ERROR); return NULL;}

	/* get second arg -> a (char *) # (float) */
	char * arg_stars = argv[1];

	/* parsing stars */
	float stars;
	if (sscanf(arg_stars,"%f", &stars) == EOF) {print_error (NOT_VAR_SINTAX); set_status (args, ERROR); return NULL;}

	/* get third arg -> a (char *) */
	char * arg_CITY = argv[2];

	/* parsing delim */
	arg_CITY = parsing_string (arg_CITY, "\"");

	/* check parsing */
	if (arg_CITY == NULL) {print_error (NOT_VAR_SINTAX); set_status (args, ERROR); return NULL;}

	/* declaration of TABLE to get <query> result */
	TABLE * t = businesses_with_starts_and_city (sgr, stars, arg_CITY);

	// Jamaica Plain 
	char * var = get_var (args);

	/* insert in the VAR_LIST */
	var_list_insert (table_list, var, t);
	
	return NULL;
}

/* ------- DONE */
void * PRIMARY_top_businesses_by_city (_ARGS args) {

	/* get user_data (contain VAR_LIST) */
	void ** user_data = get_user_data (args);
	VAR_LIST var_list = (VAR_LIST) user_data[0];
	VAR_LIST table_list = (VAR_LIST) user_data[1];

	/* get all args */
	char ** argv = get_args(args);
	
	/* get first arg -> a SGR */
	char * arg_SGR = argv[0];
	
	/* check if variable exists */
	SGR sgr;
	sgr = get_var_list_value (var_list, arg_SGR);
	if (sgr == NULL) {print_error (NOT_VAR); set_status (args, ERROR); return NULL;}

	/* get second arg -> a (char *) # (int) */
	char * arg_TOP = argv[1];

	/* parsing stars */
	int top;
	if (sscanf(arg_TOP,"%d", &top) == EOF) {print_error (NOT_VAR_SINTAX); set_status (args, ERROR); return NULL;}

	/* declaration of TABLE to get <query> result */
	TABLE * t = top_businesses_by_city (sgr, top);

	char * var = get_var (args);

	/* insert in the VAR_LIST */
	var_list_insert (table_list, var, t);

	return NULL;
}

/* --------- DONE */
void * PRIMARY_international_users (_ARGS args) {

	/* get user_data (contain VAR_LIST) */
	void ** user_data = get_user_data (args);
	VAR_LIST var_list = (VAR_LIST) user_data[0];
	VAR_LIST table_list = (VAR_LIST) user_data[1];

	/* get all args */
	char ** argv = get_args(args);
	
	/* get first arg -> a SGR */
	char * arg_SGR = argv[0];
	
	/* check if variable exists */
	SGR sgr;
	sgr = get_var_list_value (var_list, arg_SGR);
	if (sgr == NULL) {print_error (NOT_VAR); set_status (args, ERROR); return NULL;}

	TABLE * t = international_users(sgr);
	char * var = get_var (args);

	/* insert in the VAR_LIST */
	var_list_insert (table_list, var, t);

	return NULL;
}

/* --------- DONE */
void * PRIMARY_top_businesses_by_category (_ARGS args) {
	/* get user_data (contain VAR_LIST) */
	void ** user_data = get_user_data (args);
	VAR_LIST var_list = (VAR_LIST) user_data[0];
	VAR_LIST table_list = (VAR_LIST) user_data[1];

	/* get all args */
	char ** argv = get_args(args);
	
	/* get first arg -> a SGR */
	char * arg_SGR = argv[0];
	
	/* check if variable exists */
	SGR sgr;
	sgr = get_var_list_value (var_list, arg_SGR);
	if (sgr == NULL) {print_error (NOT_VAR); set_status (args, ERROR); return NULL;}

	/* get second arg -> a (char *) # (int) */
	char * arg_TOP = argv[1];

	/* parsing top */
	int top;
	if (sscanf(arg_TOP,"%d", &top) == EOF) {print_error (NOT_VAR_SINTAX); set_status (args, ERROR); return NULL;}
	
	/* get second arg -> a char */
	char * arg_CATEGORY = argv[2];

	/* parsing delim */
	arg_CATEGORY = parsing_string (arg_CATEGORY, "\"");

	/* check parsing */
	if (arg_CATEGORY == NULL) {print_error (NOT_VAR_SINTAX); set_status (args, ERROR); return NULL;}

	/* declaration of TABLE to get <query> result */
	TABLE * t = top_businesses_with_category(sgr, top, arg_CATEGORY);

	char * var = get_var (args);

	/* insert in the VAR_LIST */
	var_list_insert (table_list, var, t);

	return NULL;
}

void * PRIMARY_reviews_with_word (_ARGS args) {
	/* get user_data (contain VAR_LIST) */
	void ** user_data = get_user_data (args);
	VAR_LIST var_list = (VAR_LIST) user_data[0];
	VAR_LIST table_list = (VAR_LIST) user_data[1];

	/* get all args */
	char ** argv = get_args(args);
	
	/* get first arg -> a SGR */
	char * arg_SGR = argv[0];
	
	/* check if variable exists */
	SGR sgr;
	sgr = get_var_list_value (var_list, arg_SGR);
	if (sgr == NULL) {print_error (NOT_VAR); set_status (args, ERROR); return NULL;}

	/* get second arg -> a (char *) */
	char * word = argv[1];

	/* parsing delim */
	word = parsing_string (word, "\"");

	/* check parsing */
	if (word == NULL) {print_error (NOT_VAR_SINTAX); set_status (args, ERROR); return NULL;}
	
	/* declaration of TABLE to get <query> result */
	TABLE * t = reviews_with_word (sgr, word);

	char * var = get_var (args);

	/* insert in the VAR_LIST */
	var_list_insert (table_list, var, t);
	
	return NULL;
}

/* ------- DONE */
void * PRIMARY_show (_ARGS args) {
	
	/* get all args */
	char ** argv = get_args(args);
	
	/* get first arg -> a TABLE to print */
	char * arg_table = argv[0];
	
	/* get user_data (contain VAR_LIST) */
	VAR_LIST var_list = (VAR_LIST) get_user_data (args);

	/* declaration of TABLE to print */
	TABLE * t;

	/* TABLE exists */
	if ((t = (TABLE *) get_var_list_value (var_list, arg_table)) != NULL) table_pagination (t);
	else {print_error (NOT_VAR), set_status (args, ERROR);}
	
	return NULL;
}

/* ------- DONE */
void * PRIMARY_toCSV (_ARGS args) {
	
	/* get all args */
	char ** argv = get_args(args);
	
	/* get first arg -> a TABLE to print in a FILE */
	char * arg_table = argv[0];

	/* get second arg -> a delim */
	char * delim = argv[1];

	/* parse delim */
	if ((delim = parsing_string (delim, "'")) == NULL) {print_error (NOT_VAR_SINTAX); set_status(args, ERROR); return NULL;};

	/* get third arg -> a file path */
	char * file_path = argv[2];

	/* parse file path */
	if ((file_path = parsing_string (file_path, "\"")) == NULL) {print_error (NOT_VAR_SINTAX); set_status(args, ERROR); return NULL;};
		
	/* declaration of the FILE pointer */
	FILE * fp;

	/* open FILE pointer and check errors */
	if ((fp = fopen (file_path, "w")) == NULL) {print_error (FILE_OPEN);set_status(args, ERROR); return NULL;};

	/* get user_data (contain VAR_LIST) */
	VAR_LIST var_list = (VAR_LIST) get_user_data (args);

	/* check special case */
	if (!strcmp(delim, "..")) {delim[0] = ';';delim[1] = '\0';}

	/* declaration of TABLE to print in the <file_path> */
	TABLE * t;

	/* TABLE exists */
	if ((t = (TABLE *) get_var_list_value (var_list, arg_table)) != NULL) table_to_file_delim(fp, t, delim);
	/* TABLE does not exist */
	else {print_error (NOT_VAR);set_status(args, ERROR);};
	
	return NULL;
}

/* ------ DONE */
void * PRIMARY_fromCSV (_ARGS args) {
	
	/* get all args */
	char ** argv = get_args(args);
	
	/* get first arg -> a FILE path */
	char * arg_FILE_PATH = argv[0];

	/* get second arg -> a delim */
	char * arg_DELIM = argv[1];

	/* parse delim */
	if ((arg_DELIM = parsing_string (arg_DELIM, "'")) == NULL) {print_error (NOT_VAR_SINTAX); set_status(args, ERROR); return NULL;};

	/* parse file path */
	if ((arg_FILE_PATH = parsing_string (arg_FILE_PATH, "\"")) == NULL) {print_error (NOT_VAR_SINTAX); set_status(args, ERROR); return NULL;};
	
	/* get default path files */
	FILE * file_path_fp = fopen ("mydConfig.cfg", "r");
	char file_path_p[100];
	char * file_path;

	while (fgets (file_path_p, 100, file_path_fp) != NULL) {
		file_path_p[strlen(file_path_p) - 1] = '\0';
		file_path_p[8] = '\0';
		if (!strcmp (file_path_p,"set path")) file_path = &file_path_p[9];
	}

	/* join path to file */
	strcat (file_path, arg_FILE_PATH);

	/* declaration of the FILE pointer */
	FILE * fp;

	/* open FILE pointer and check errors */
	if ((access (file_path, F_OK)) < 0) {print_error (FILE_OPEN);set_status(args, ERROR); return NULL;};

	/* get user_data (contain VAR_LIST) */
	VAR_LIST var_list = (VAR_LIST) get_user_data (args);

	/* declaration of TABLE to load <file_path> */
	TABLE * t;
	
	/* check special case */
	if (!strcmp(arg_DELIM, "..")) {arg_DELIM[0] = ';'; arg_DELIM[1] = '\0';}

	fp = fopen (file_path, "r");

	int fields[1];
	fields[0] = 0;
	char ** headers = parsing_header (fp,arg_DELIM, fields); 
	int * types = malloc (sizeof (int) * fields[0]);

	for (int i = 0; i < fields[0]; i++) types[i] = COL_TYPE_STRING;

	t = table_new_generic(fields[0],0, types, headers);
	fill_table_str (t, fp, fields[0], arg_DELIM);

	char * var = get_var (args);

	/* insert in the VAR_LIST */
	var_list_insert (var_list, var, t);

	return NULL;
}


void * PRIMARY_filter (_ARGS args) {
	
	/* get user_data (contain VAR_LIST) */
	VAR_LIST var_list = (VAR_LIST) get_user_data (args);
	
	/* get all args */
	char ** argv = get_args(args);
	
	/* get first arg -> a variable */
	char * variable = argv[0];

	/* get second arg -> an header */
	char * arg_HEADER = argv[1];
	
	/* get third arg -> an value */
	char * arg_VALUE = argv[2];

	/* get quarter arg -> an operator */
	char * arg_OPERATOR = argv[3];
	
	TABLE * t;
	OPERATOR op;

	/* check args */
	if ((arg_HEADER = parsing_string (arg_HEADER, "\"")) == NULL) {print_error (NOT_VAR_SINTAX); set_status(args, ERROR); return NULL;};
	if ((op = parsing_operator (arg_OPERATOR)) == NONE_OP) {print_error (NOT_VAR_SINTAX); set_status(args, ERROR); return NULL;};
	if ((t = (TABLE *) get_var_list_value (var_list, variable)) == NULL) {print_error (NOT_VAR); set_status (args, ERROR); return NULL;}

	/* check if header exists */
	int fields = get_fields (t);
	HEADER headers = get_headers (t);
	int * types = get_header_types (headers, fields);
	char ** headers_names = get_header_names (headers, fields);
	int check = 0;
	int type;

	for (int i = 0; i < fields; i++) {
		if (!strcmp (arg_HEADER, headers_names[i])) {
			check = 1;
			type = types[i];
		}
	}

	/* header does not exist */
	if (check == 0) {print_error (NOT_VAR); set_status (args, ERROR); return NULL;}
	
	float check_f;
	int check_i;

	/* check if value correspond to the type of header */
	switch (type) {
		case COL_TYPE_INT:
			if (sscanf(arg_VALUE, "%d", &check_i) == EOF) {print_error (NOT_VAR_TYPE); set_status(args, ERROR); return NULL;};
			break;
		case COL_TYPE_FLOAT:
			if (sscanf(arg_VALUE, "%f", &check_f) == EOF) {print_error (NOT_VAR_SINTAX); set_status(args, ERROR); return NULL;};
			break;
		default:
			break;
	}

	/* declaration of <return TABLE> */
	TABLE * return_table = table_new_generic (fields, 0, types, headers_names);
	
	/* declaration of <user_data> for <foreach> */
	FILTER_AUX fa = init_filter_aux ();
	filter_aux_set_return_table (fa, return_table);
	filter_aux_set_operator (fa, op);
	filter_aux_set_cmp_value (fa, arg_VALUE);
	filter_aux_set_header (fa, arg_HEADER);
	filter_aux_set_type (fa, type);
	filter_aux_set_fields (fa, fields);
	filter_aux_set_headers (fa, headers);
	
	table_search_foreach (t, filter_aux, fa);

	/* free headers names and types*/
	for (int i = 0; i < fields; i++) free (headers_names[i]);
	free (headers_names);
	free (types);
	
	char * var = get_var (args);

	/* insert in the VAR_LIST */
	var_list_insert (var_list, var, return_table);

	return NULL;
}

void * PRIMARY_proj (_ARGS args) {
	
	/* get user_data (contain VAR_LIST) */
	VAR_LIST var_list = (VAR_LIST) get_user_data (args);
	
	/* get all args */
	char ** argv = get_args(args);
	
	/* get first arg -> a variable */
	char * variable = argv[0];

	/* get second arg -> an array */
	char * arg_ARRAY = argv[1];

	int num_cols[1];
	num_cols[0] = 0;
	int * cols = parsing_cols (arg_ARRAY, num_cols);

	/* check <parsing_cols> */
	if (cols == NULL) {print_error (NOT_VAR_SINTAX); set_status (args, ERROR); return NULL;}

	/* declaration of TABLE to make the <search> */
	TABLE * t;

	TABLE * return_table = NULL;
	
	if ((t = (TABLE *) get_var_list_value (var_list, variable)) != NULL) {
		
		/* check with columns are less than number of fields */
		for (int i = 0; i < *num_cols; i++) if (cols[i] >= get_fields (t)) {print_error (NOT_VAR_SINTAX); set_status (args,ERROR); return NULL;}

		return_table = table_set_columns(t, cols, *num_cols);
	}
	else {print_error (NOT_VAR); set_status (args, ERROR);}
	
	char * var = get_var (args);

	/* insert in the VAR_LIST */
	var_list_insert (var_list, var, return_table);
	return NULL;
}

/* ------ DONE */
void * PRIMARY_matriz_insp (_ARGS args) {
	
	/* get user_data (contain VAR_LIST) */
	VAR_LIST var_list = (VAR_LIST) get_user_data (args);
	
	/* get all args */
	char ** argv = get_args(args);
	
	/* get first arg -> a variable */
	char * variable = argv[0];

	/* get second arg -> a int */
	char * arg_ROW_NUMBER = argv[1];

	/* get third arg -> a int */
	char * arg_ROW_COLUMN = argv[2];

	int row_number, row_column;
	/* check with args are numbers */
	if (sscanf(arg_ROW_NUMBER, "%d", &row_number) == EOF) {print_error (NOT_VAR_SINTAX); set_status (args, ERROR);return NULL;}
	/* check with args are numbers */
	if (sscanf(arg_ROW_COLUMN, "%d", &row_column) == EOF) {print_error (NOT_VAR_SINTAX); set_status (args, ERROR);return NULL;}

	/* declaration of TABLE to make the <search> */
	TABLE * t;

	/* declaration of <return_table> */
	TABLE * return_table = NULL;

	/* check with TABLE exist */
	if ((t = (TABLE *) get_var_list_value (var_list, variable)) != NULL) {
		
		/* validate args */
		if (row_column >= get_fields (t) || row_number >= table_size (t)) {print_error (NOT_VAR_SINTAX); set_status (args, ERROR);return NULL;};
		return_table = table_search_position(t, row_number, row_column);
	}
	else {print_error (NOT_VAR); set_status (args, ERROR);}
	
	char * var = get_var (args);

	/* insert in the VAR_LIST */
	var_list_insert (var_list, var, return_table);

	return NULL;
}


