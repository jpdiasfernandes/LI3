#ifndef _SGR_H_
#define _SGR_H_

#include "../../table/includes/table.h"
#include "stats.h"

/* typedef's */
typedef struct cat_users * CAT_USERS;
typedef struct cat_reviews * CAT_REVIEWS;
typedef struct cat_businesses * CAT_BUSINESSES;
typedef struct sgr * SGR;

/* init */
SGR init_sgr (void);
/* fill */
void fill_sgr (SGR, TABLE *, TABLE *, TABLE *, TABLE *, TABLE *);
/* destroy */
void destroy_sgr (SGR);

/* getter's */
CAT_USERS get_users(SGR sgr);
CAT_REVIEWS get_reviews(SGR sgr);
CAT_BUSINESSES get_businesses(SGR sgr);
STATS get_stats(SGR sgr);
TABLE *get_table_users(CAT_USERS users);
TABLE *get_table_reviews(CAT_REVIEWS reviews);
TABLE *get_table_business(CAT_BUSINESSES business);
TABLE *get_table_stats(STATS stats);
TABLE *get_table_stats_2(STATS stats);

/* queries */
SGR load_sgr (char *, char *, char *);
TABLE * businesses_started_by_letter (SGR, char);
TABLE * business_info (SGR, char *);
TABLE * businesses_reviewed (SGR, char *);
TABLE * businesses_with_starts_and_city (SGR, float, char *);
TABLE * top_businesses_by_city (SGR, int);
TABLE * international_users (SGR);
TABLE * top_businesses_with_category (SGR, int, char *);
TABLE * reviews_with_word (SGR, char *);

#endif
