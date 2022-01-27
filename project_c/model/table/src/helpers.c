#include <stdlib.h>

#include "../includes/table.h"
#include "../includes/table_p.h"

INFO header_helper_type(HEADER h, int fields, char *col_name) {
	INFO r = {0, 0, 0};

	int i;
	for (i = 0; i < fields && strcmp(h[i].field_name, col_name); i++)
		;
	if (i == fields)
		perror(
		    "Could not find the specified header. Expect"
		    "undefined behaviour.");
	else
		r = h[i];

	return r;
}

int belong (char * test, char ** content, int content_n) {
	for (int i = 0; i < content_n; i++)	if (!strcmp(test, content[i])) return 1;
	return 0;
}
