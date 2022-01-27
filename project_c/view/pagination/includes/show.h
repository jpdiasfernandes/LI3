#ifndef SHOW_H
#define SHOW_H

#include "../../../model/table/includes/table.h"

void table_pagination (TABLE * t);
void table_to_file_delim (FILE * fp, TABLE * t, const char * delim);

#endif
