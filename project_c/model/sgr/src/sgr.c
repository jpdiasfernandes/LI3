#include <stdio.h> /* FILE type , fopen(), popen() */
#include <unistd.h> /* acess() */

#include "../includes/sgr.h"
#include "../includes/queries_helpers.h"
#include "../../table/includes/table.h"
#include "../../table/includes/search.h"
#include "../includes/data.h"
#include "../../../view/pagination/includes/show.h"
#include "../../../view/messages/includes/messages.h"

#define USERS_DELIM_QUANT 3 
#define BUSINESSES_DELIM_QUANT 5 
#define REVIEWS_DELIM_QUANT 9

struct cat_users {
	TABLE * users;
};

struct cat_businesses {
	TABLE * businesses;
};

struct cat_reviews {
	TABLE * reviews;
};

struct sgr {
	struct cat_users * cat_users;
	struct cat_businesses * cat_businesses;
	struct cat_reviews * cat_reviews;
	STATS stats;
};

SGR init_sgr (void) {
	SGR sgr = malloc (sizeof (struct sgr));

	sgr->cat_users = malloc (sizeof (struct cat_users));
	sgr->cat_businesses = malloc (sizeof (struct cat_businesses));
	sgr->cat_reviews = malloc (sizeof (struct cat_reviews));
	sgr->stats = init_stats();

	return sgr;
}

void fill_sgr (SGR sgr, TABLE * users, TABLE * businesses, TABLE * reviews, TABLE * stats, TABLE * stats_2) {

	sgr->cat_users->users = users;
	sgr->cat_businesses->businesses = businesses;
	sgr->cat_reviews->reviews = reviews;
	set_stats(sgr->stats, stats);
	set_stats_2(sgr->stats, stats_2);

}

void destroy_sgr (SGR sgr) {
	table_destroy (sgr->cat_businesses->businesses);
	table_destroy (sgr->cat_reviews->reviews);
	table_destroy (sgr->cat_users->users);
	table_destroy (get_table_stats (sgr->stats));
	table_destroy (get_table_stats_2 (sgr->stats));
}

CAT_USERS get_users(SGR sgr) {
	return sgr->cat_users;
}
CAT_REVIEWS get_reviews(SGR sgr) {
	return sgr->cat_reviews;
}
CAT_BUSINESSES get_businesses(SGR sgr) {
	return sgr->cat_businesses;
}

STATS get_stats(SGR sgr) {
	return sgr->stats;
}

TABLE *get_table_users(CAT_USERS users) {
	return users->users;
}

TABLE *get_table_reviews(CAT_REVIEWS reviews) {
	return reviews->reviews;
}

TABLE *get_table_business(CAT_BUSINESSES business) {
	return business->businesses;
}

TABLE *get_table_stats(STATS stats) {
	return _get_table_stats(stats);
}

TABLE *get_table_stats_2 (STATS stats) {
	return _get_table_stats_2(stats);
}


SGR load_sgr (char * users, char * businesses, char * reviews) {
	FILE * fp;	
	TABLE *users_t, *businesses_t, *reviews_t;
    
	int load_pid;
  if ((load_pid = fork()) == 0) {
    /* child process - load() */
    print_load ();
    _exit (0);
  }
	
	/* ----------- get <file_path> from <config> file */

	/* find <absolute-path> to  config file */
	FILE * file_path_fd = popen("realpath mydConfig.cfg", "r");
	char file_path_fd_str[100];
	fgets (file_path_fd_str, 100, file_path_fd);
	file_path_fd_str[strlen (file_path_fd_str) - 1] = '\0';
	pclose (file_path_fd);

	/* get <file_path> */
	FILE * file_path_fp = fopen (file_path_fd_str, "r");
	char file_path_p[100];
	char * file_path;

	while (fgets (file_path_p, 100, file_path_fp) != NULL) {
		file_path_p[strlen(file_path_p) - 1] = '\0';
		file_path_p[8] = '\0';
		if (!strcmp (file_path_p,"set path")) file_path = &file_path_p[9];
	}

	int file_path_size = strlen (file_path);

	/* ----------- users parser */
	
	/* get <set's> in config file */
	fp = fopen ("mydConfig.cfg","r");
	int user_friends = parsing_user_friends (fp);

	/* append <users> in the end of <file_path> */
	strcat (file_path, users);
	/* check if file exists */
	if (access (file_path, F_OK) != 0) {print_error (FILE_OPEN);kill(load_pid, SIGKILL); return NULL;}
	/* file exists */
	fp = fopen (file_path,"r");

	if (user_friends == 1) {
		users_t = table_new(USERS_DELIM_QUANT, 0, "s s s", "user_id", "name", "friends");
		fill_table (users_t, fp, USERS_DELIM_QUANT, "s s s",";", NULL, NULL, NULL);
	} else {
		users_t = table_new(USERS_DELIM_QUANT - 1, 0, "s s", "user_id", "name");
		fill_table (users_t, fp, USERS_DELIM_QUANT - 1, "s s",";", NULL, NULL, NULL);
	}

	file_path[file_path_size] = '\0';
  
	/* stop <print_load> */
  kill (load_pid, SIGKILL);
  print_load_result (1);
  if ((load_pid = fork()) == 0) {
    /* child process - load() */
    print_load ();
    _exit (0);
  }
	
	/* ----------- business parser */

	/* append <businesses> in the end of <file_path> */
	strcat (file_path, businesses);
	/* check if file exists */
	if (access (file_path, F_OK) != 0) {print_error (FILE_OPEN); kill(load_pid, SIGKILL);return NULL;}
	/* file exists */
	fp = fopen (file_path,"r");
	businesses_t = table_new(BUSINESSES_DELIM_QUANT, 0, "s s s s s", "business_id", "name", "city", "state", "categories");
	fill_table (businesses_t, fp, BUSINESSES_DELIM_QUANT, "s s s s s",";", NULL, NULL, NULL);
	file_path[file_path_size] = '\0'; 
	
	/* stop <print_load> */
  kill (load_pid, SIGKILL);
  print_load_result (2);
  if ((load_pid = fork()) == 0) {
    /* child process - load() */
    print_load ();
    _exit (0);
  }
	
	/* ----------- reviews parser */

	/* append <reviews> in the end of <file_path> */
	strcat (file_path, reviews);
	/* check if file exists */
	if (access (file_path, F_OK) != 0) {print_error (FILE_OPEN); kill(load_pid, SIGKILL);return NULL;}
	/* file exists */
	fp = fopen(file_path,"r");
	reviews_t = table_new(REVIEWS_DELIM_QUANT, 0, "s s s f d d d s s", "review_id", "user_id", "business_id", "stars", "useful", "funny", "cool", "date", "text");

	/* add indexing to "user_id" */
	table_add_indexing(reviews_t, 1);
	TABLE *t_stats = table_new(3, 0, "s | f | d ", "business_id", "mean_stars", "quantity");
	/* fill <reviews> and <stats_2> */
	fill_table(reviews_t, fp, REVIEWS_DELIM_QUANT, "s s s f d d d s s",";", t_stats, users_t, businesses_t);
	
	/* create <stats_2> */
	TABLE * stats_final;
	char * headers_out[5] = {"name","city","business_id","mean_stars","quantity"};
	int types[5] = { COL_TYPE_STRING, COL_TYPE_STRING, COL_TYPE_STRING, COL_TYPE_FLOAT, COL_TYPE_INT };
	/* fill <stats_2> */
	stats_final = table_join (businesses_t, t_stats,headers_out, 2, 3, types, stats_gk_helper, NULL);

	SGR sgr = init_sgr (); 
	fill_sgr (sgr, users_t, businesses_t, reviews_t, stats_final, t_stats);
	
	/* stop <print_load> */
  kill (load_pid, SIGKILL);
  print_load_result (3);
	return sgr;
}

TABLE * businesses_started_by_letter (SGR sgr, char letter) {
	
	/* declaration of <headers_out> for the <search-function> */
	char * headers_out[1] = {"name"};

	/* get <table business> */
	TABLE * business = get_table_business (get_businesses(sgr));

	/* create <return_table> */
	TABLE * return_table = table_search_letter (business, "name", headers_out, 1, letter);
	
	return return_table;
}

TABLE * business_info (SGR sgr, char * business_id) {
	
	/* declaration of <headers_out> for the <search-function> */
	//char *headers_out[2] = {"review_id", "stars"};

	/* get <table reviews> */
	//TABLE * reviews = get_table_reviews (get_reviews (sgr));

	/* stars = table with 2 columns with the <stars header> and <review_id header> */
	//TABLE * stars = table_search_row (reviews, "business_id", headers_out, 2, &business_id);
	
	/* create <return-table> */
	TABLE * return_table = table_new(5, 0, "s s s f d", "nome", "cidade", "estado", "stars", "n_reviews");	

	/* get <stats_2> table */
	TABLE * stats = get_table_stats_2 (get_stats (sgr));

	/* get <mean-stars> */
	//float mean_stars = table_column_sum (stars, "stars") / table_size (stars);

	ROW row = table_search_row_id (stats, &business_id);

	/* check if ROW exist */
	if (row == NULL) return return_table;

	float mean_stars = * (float * )get_row_content_by_column (row, 1);
	int n_reviews = * (int *) get_row_content_by_column (row, 2);

	/* get <table business> */
	TABLE * business = get_table_business (get_businesses(sgr));

	/* get <row> with <business_id> in <business-table> */
	ROW business_row = table_search_row_id (business, &business_id);
	
	if (business_row != NULL) {
		/* extract information from the row */ 
		char * name = *(char **) get_row_content_by_header(business_row, get_headers (business), "name", get_fields (business));
		char * city = *(char **) get_row_content_by_header(business_row, get_headers (business), "city", get_fields (business));
		char * state = *(char **) get_row_content_by_header(business_row, get_headers (business), "state", get_fields (business));

		/* insert content */ 	
		table_append(return_table, &name, &city, &state, &mean_stars, &n_reviews);

		/* destroy unecessary tables */
		//table_destroy (stars);
	}

	return return_table;
}

TABLE * businesses_reviewed (SGR sgr, char * user_id) {
	
	/* declaration of <headers_out> for the <search-function> */
	char *headers_out[2] = {"review_id", "business_id"};

	/* get <table reviews> */
	TABLE * reviews = get_table_reviews (get_reviews (sgr));

	/* get <table business> */
	TABLE * business = get_table_business (get_businesses (sgr));
	
	/* business_id = table with 2 columns with the <business_id header> and <review_id header> */
	TABLE * business_id = table_search_row (reviews, "user_id", headers_out, 2, &user_id);

	/* create <return_table> */
	TABLE * return_table = table_new (2, 0, "s s", "business_id", "name");

	if (business_id == NULL) return return_table;
	
	/* create <user_data> for the <foreach> */
	Q_4_AUX user_data = init_q_4_aux ();

	/* fill <user_data> */
	q4aux_set_return_table (user_data, return_table);
	q4aux_set_cmp_table (user_data, business);
	q4aux_set_header (user_data, get_headers (business_id));
	q4aux_set_n_fields (user_data, 2);
	q4aux_set_cmp_header_business(user_data, get_headers (business));

	/* fill <return_table> */
	table_search_foreach(business_id, businesses_reviewed_helper, (tpointer) user_data);
	
	return return_table;
}

TABLE * businesses_with_starts_and_city (SGR sgr, float stars, char * city) {
	
	/* declaration of <headers_out> for the <search-function> */
	char *headers_out[2] = {"business_id", "name"};

	/* get <table stats> */
	TABLE * stats = get_table_stats_2 (get_stats(sgr));
		
	/* get <table business> */
	TABLE * business = get_table_business (get_businesses (sgr));
	
	/* business_in_city = table with 2 columns with the <business_id header> and <name header> */
	TABLE * business_in_city = table_search_row (business, "city", headers_out, 2, &city);

	/* create <return_table> */
	TABLE * return_table = table_new (2, 0, "s s", "business_id", "name");
	
	/* create <user_data> for the <foreach> */
	Q_5_AUX user_data = init_q_5_aux ();

	/* fill <user_data> */
	q5aux_set_return_table (user_data, return_table);
	q5aux_set_cmp_table (user_data, stats);
	q5aux_set_header_bussiness_in_city (user_data, get_headers (business_in_city));
	q5aux_set_header_reviews (user_data, get_headers (stats));
	q5aux_set_stars (user_data, stars);

	/* fill <return_table> */
	table_search_foreach(business_in_city, businesses_stars_and_city_helper, (tpointer) user_data);
	
	return return_table;
}

TABLE * top_businesses_by_city (SGR sgr, int top) {

	/* get TABLE stats */
	TABLE * t = get_table_stats (get_stats (sgr));

	/* declaration of <return_table> */
	TABLE * return_table = table_new(4, 1, "s s s f", "name","city","business_id","mean_stars");
	
	/* create <user_data> for the <foreach> */
	Q_6_AUX user_data = init_q_6_aux();

	ROW row = table_last_row (t);
	char * city = * (char **) get_row_content_by_column (row, 1);

	/* fill <user_data> */
	int aux_top[1];
	aux_top[0] = top;
	q6aux_set_top (user_data, aux_top);
	q6aux_set_return_table (user_data, return_table);
	q6aux_set_current_city (user_data, NULL);
	q6aux_set_last_city(user_data, city);
	q6aux_set_fix_top(user_data, top);

	table_search_foreach_inverse (t, top_businesses_by_city_helper, user_data);
	return return_table;
}

TABLE * international_users (SGR sgr) {
	TABLE * reviews = get_table_reviews(get_reviews(sgr));		
	TABLE * businesses = get_table_business(get_businesses(sgr));

	TABLE * users_visited = table_new(2, 0, "s s", "user_id", "state");

	TABLE * return_table = table_new(2, 0, "s d", "user_id", "num_total");
	
	Q_7_AUX aux = init_q_7_aux();
	q7aux_set_visited(aux, users_visited);
	q7aux_set_return_table(aux, return_table);
	q7aux_set_businesses(aux, businesses);

	/* cycles trough the users_id and apply international_users_helpers */
	if (table_search_foreach_indexed(reviews, 1, international_users_helpers, aux) == -1)
		return NULL;

	/* free the auxiliary tables used */
	table_destroy(users_visited);
	
	/* adicionar o número total de entradas da table */
	char * numero = "  número total";
	int size = table_size(return_table);
	table_append(return_table, &numero, &size);

	return return_table;
}

TABLE * top_businesses_with_category (SGR sgr, int top, char * category) {
	
	/* get <business-table> */
	TABLE * business = get_table_business (get_businesses(sgr));

	/* get <STATS_2-table> */
	TABLE * stats = get_table_stats_2 (get_stats (sgr));

	/* declaration of <intermediate-table> - TABLE with all businesses in the <category> in <stars order> */
	TABLE * intermediate = table_new (3, 0, "s s f", "business_id", "name", "mean_stars");

	/* declaration of <user_data> */
	Q_8_AUX aux = init_q_8_aux ();

	/* fill <user_data> */
	q8aux_set_stats_table (aux, stats);
	q8aux_set_intermediate_table (aux, intermediate);
	q8aux_set_category (aux, category);

	table_search_foreach(business, top_businesses_with_category_helper, aux);

	/* we have to select only the <top n> from intermediate */
	TABLE * return_table = table_new (3, 0, "s s f", "business_id", "name", "mean_stars");

	/* recicle <user_data> */
	int top_p[1];
	top_p[0] = top;
	q8aux_set_top (aux, top_p);
	q8aux_set_return_table (aux, return_table);

	/* <foreach> to select only the <top n> from intermediate */
	table_search_foreach_inverse (intermediate, top_businesses_with_category_helper_2, aux);
	
	return return_table;
}

TABLE * reviews_with_word (SGR sgr, char * word) {
	
	TABLE * reviews = get_table_reviews(get_reviews(sgr));

	TABLE * return_table = table_new (1, 0, "s", "reviews_id");
	
	Q_9_AUX aux = init_q_9_aux();
	q9aux_set_return_table(aux, return_table);
	q9aux_set_word(aux, word);

	table_search_foreach(reviews, reviews_with_word_helper, aux);

	return return_table;
}
