#ifndef _STATS_H_
#define _STATS_H_

#include "../../table/includes/table.h"

typedef struct stats *STATS;

/* init */
STATS init_stats();

/* getter's */
TABLE *_get_table_stats(STATS stats);
TABLE *_get_table_stats_2(STATS stats);

/* setter's */
void set_stats(STATS stats, TABLE * t_stats);
void set_stats_2(STATS stats, TABLE * t_stats);

#endif
