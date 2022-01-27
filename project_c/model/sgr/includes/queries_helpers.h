#ifndef QUERIES_HELPERS
#define QUERIES_HELPERS

#include "../../table/includes/table.h"
#include "../../sgr/includes/data.h"

/* <user-datas> in order to <foreach> functions */ 
typedef struct filter_aux * FILTER_AUX;
typedef struct q_4_aux * Q_4_AUX;
typedef struct q_5_aux * Q_5_AUX;
typedef struct q_6_aux * Q_6_AUX;
typedef struct q_7_aux * Q_7_AUX;
typedef struct q_8_aux * Q_8_AUX;
typedef struct q_9_aux * Q_9_AUX;

/* <function pointers> in order to <foreach> functions */
int businesses_reviewed_helper (tpointer key, tpointer value, tpointer aux);
int businesses_stars_and_city_helper (tpointer key, tpointer value, tpointer aux);
int top_businesses_by_city_helper (tpointer key, tpointer value, tpointer user_data);
void international_users_helpers(tpointer row, tpointer user_data);
int top_businesses_with_category_helper (tpointer key, tpointer value, tpointer user_data);
int top_businesses_with_category_helper_2 (tpointer key, tpointer value, tpointer user_data);
tpointer stats_gk_helper (tpointer row1, tpointer row2, tpointer new_row, tpointer user_data);
tpointer char_gk_helper(tpointer row1, tpointer row2, tpointer newrow, tpointer user_data);
tpointer q8_gk_helper(tpointer row1, tpointer row2, tpointer newrow, tpointer user_data);
int filter_aux (tpointer key, tpointer value, tpointer aux);
int reviews_with_word_helper (tpointer key, tpointer value, tpointer aux);

/* init's */
FILTER_AUX init_filter_aux ();
Q_4_AUX init_q_4_aux ();
Q_5_AUX init_q_5_aux ();
Q_6_AUX init_q_6_aux ();
Q_7_AUX init_q_7_aux ();
Q_8_AUX init_q_8_aux ();
Q_9_AUX init_q_9_aux ();

/* <filter> setter's */
void filter_aux_set_return_table (FILTER_AUX, TABLE *);
void filter_aux_set_operator (FILTER_AUX, OPERATOR);
void filter_aux_set_cmp_value (FILTER_AUX, char * cmp);
void filter_aux_set_header (FILTER_AUX f, char * header);
void filter_aux_set_headers (FILTER_AUX f, HEADER headers);
void filter_aux_set_fields (FILTER_AUX f, int fields);
void filter_aux_set_type (FILTER_AUX f, int type);

/* <q4aux> setter's */
void q4aux_set_header (Q_4_AUX q, HEADER header); 
void q4aux_set_n_fields (Q_4_AUX q, int n_fields); 
void q4aux_set_return_table (Q_4_AUX q, TABLE * t);
void q4aux_set_cmp_table (Q_4_AUX q, TABLE * t);
void q4aux_set_cmp_header_business (Q_4_AUX q, HEADER header);

/* <q5aux> setter's */
void q5aux_set_return_table (Q_5_AUX q, TABLE * t);
void q5aux_set_cmp_table (Q_5_AUX q, TABLE * t);
void q5aux_set_header_bussiness_in_city (Q_5_AUX q, HEADER header);
void q5aux_set_header_reviews (Q_5_AUX q, HEADER header);
void q5aux_set_stars (Q_5_AUX q, float stars);

/* <q6aux> setter's */
void q6aux_set_return_table (Q_6_AUX q, TABLE * t);
void q6aux_set_last_city (Q_6_AUX q, char * city);
void q6aux_set_current_city (Q_6_AUX q, char * current);
void q6aux_set_top (Q_6_AUX q, int * top);
void q6aux_set_fix_top (Q_6_AUX q, int top);

/* <q7aux> setter's */
void q7aux_set_visited (Q_7_AUX q, TABLE * visited);
void q7aux_set_return_table (Q_7_AUX q, TABLE * return_table);
void q7aux_set_businesses (Q_7_AUX q, TABLE * businesses);

/* <q8aux> setter's */ 
void q8aux_set_intermediate_table (Q_8_AUX q, TABLE * t);
void q8aux_set_stats_table (Q_8_AUX q, TABLE * t);
void q8aux_set_category (Q_8_AUX q, char * category);
void q8aux_set_top (Q_8_AUX q, int * top);
void q8aux_set_return_table (Q_8_AUX q, TABLE * t);

/* <q9aux> setter's */
void q9aux_set_return_table (Q_9_AUX q, TABLE * return_table);
void q9aux_set_word (Q_9_AUX q, char * word);

#endif
