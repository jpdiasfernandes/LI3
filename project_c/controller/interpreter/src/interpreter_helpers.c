#include "../includes/primary_functions.h"
#include "../includes/interpreter_helpers.h"
#include "../../../model/table/includes/table.h"

static TABLE * create_table_manual () {
	TABLE * t = table_new (5, 0, "s s s s s", "COMMAND", "ARGS NUMBER", "ARGS TYPE", "COMMAND TYPE ", "DESCRIPTION");

	char * first[5] = {"?", "0", "NONE", "TEXT", "show manual"};
	table_append (t, &first[0], &first[1], &first[2], &first[3], &first[4]);
	
	char * second[5] = {"#", "0", "NONE", "TEXT", "show project info"};
	table_append (t, &second[0], &second[1], &second[2], &second[3], &second[4]);
	
	char * third[5] = {"load_sgr", "3", "s s s", "VAR", "query 1"};
	table_append (t, &third[0], &third[1], &third[2], &third[3], &third[4]);
	
	char * quarter[5] = {"businesses_started_by_letter", "2", "s c", "VAR", "query 2"};
	table_append (t, &quarter[0], &quarter[1], &quarter[2], &quarter[3], &quarter[4]);
	
	char * five[5] = {"business_info", "2", "s s", "VAR", "query 3"};
	table_append (t, &five[0], &five[1], &five[2], &five[3], &five[4]);
	
	char * six[5] = {"businesses_reviewed", "2", "s s", "VAR", "query 4"};
	table_append (t, &six[0], &six[1], &six[2], &six[3], &six[4]);

	char * seven[5] = {"show", "1", "TABLE", "FUNC", "show a TABLE"};
	table_append (t, &seven[0], &seven[1], &seven[2], &seven[3], &seven[4]);
	
	char * eight[5] = {"toCSV", "3", "s s s", "FUNC", "upload a TABLE to CSV file"};
	table_append (t, &eight[0], &eight[1], &eight[2], &eight[3], &eight[4]);
	
	char * nine[5] = {"fromCSV", "2", "s s", "VAR", "upload CSV file to a TABLE"};
	table_append (t, &nine[0], &nine[1], &nine[2], &nine[3], &nine[4]);

	char * ten[5] = {"+", "0", "NONE", "TEXT", "show github project link"};
	table_append (t, &ten[0], &ten[1], &ten[2], &ten[3], &ten[4]);
	
	return t;
}

_OPTS_TABLE load_opts (VAR_LIST varlist_table, VAR_LIST varlist_sgr) {
	_OPTS_TABLE opts_table = init_opts_table ();

	TABLE * t = create_table_manual ();

	void ** user_data = malloc (sizeof (void *) * 2);
	user_data[0] = varlist_sgr;
	user_data[1] = varlist_table;

	insert_opt (opts_table, "?", PRIMARY_manual, 0 , TEXT , "manual info\n", t);
	insert_opt (opts_table, "#", PRIMARY_about_project, 0 , TEXT , "project info\n", NULL);
	insert_opt (opts_table, "+", PRIMARY_contribute, 0 , TEXT , "contribute info\n", NULL);
	insert_opt (opts_table, "load_sgr", PRIMARY_load_sgr, 3 , VAR , "load_sgr info\n", varlist_sgr);
	insert_opt (opts_table, "businesses_started_by_letter", PRIMARY_businesses_started_by_letter, 2 , VAR , "businesses_started_by_letter info\n", user_data);
	insert_opt (opts_table, "business_info", PRIMARY_business_info, 2 , VAR , "business_info info\n", user_data);
	insert_opt (opts_table, "businesses_reviewed", PRIMARY_businesses_reviewed, 2 , VAR , "businesses_reviewed info\n", user_data);
	insert_opt (opts_table, "businesses_with_stars_and_city", PRIMARY_businesses_with_stars_and_city, 3 , VAR , "businesses_with_stars_and_city info\n", user_data);
	insert_opt (opts_table, "top_businesses_by_city", PRIMARY_top_businesses_by_city, 2 , VAR , "top_businesses_by_city info\n", user_data);
	insert_opt (opts_table, "international_users", PRIMARY_international_users, 1 , VAR , "international_users info\n", user_data);
	insert_opt (opts_table, "top_businesses_with_category", PRIMARY_top_businesses_by_category, 3 , VAR , "top_businesses_by_category info\n", user_data);
	insert_opt (opts_table, "reviews_with_word", PRIMARY_reviews_with_word, 2 , VAR , "reviews_with_word info\n", user_data);
	insert_opt (opts_table, "show", PRIMARY_show, 1 , FUNC , "show info\n", varlist_table);
	insert_opt (opts_table, "toCSV", PRIMARY_toCSV, 3 , FUNC , "toCSV info\n", varlist_table);
	insert_opt (opts_table, "fromCSV", PRIMARY_fromCSV, 2 , VAR , "fromCSV info\n", varlist_table);
	insert_opt (opts_table, "filter", PRIMARY_filter, 4 , VAR , "filter info\n", varlist_table);
	insert_opt (opts_table, "proj", PRIMARY_proj, 2 , VAR , "proj info\n", varlist_table);
	insert_opt (opts_table, "matriz_insp", PRIMARY_matriz_insp, 3 , MATRIZ , "matriz_insp info\n", varlist_table);
	
	return opts_table;
}


