#include "../../table/includes/table.h"
#include "../includes/stats.h"

struct stats {
	TABLE *stats;
	TABLE *stats_2;
};

STATS init_stats() {
	return malloc(sizeof(struct stats));
}

void set_stats(STATS stats, TABLE *t_stats) {
	stats->stats = t_stats;
}

void set_stats_2(STATS stats, TABLE *t_stats) {
	stats->stats_2 = t_stats;
}

TABLE * _get_table_stats (STATS stats) {
	return stats->stats;
}

TABLE * _get_table_stats_2 (STATS stats) {
	return stats->stats_2;
}
