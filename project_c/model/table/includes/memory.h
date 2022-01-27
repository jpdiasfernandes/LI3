#ifndef _MEMORY_H_
#define _MEMORY_H_

#include "table.h"
#include "table_p.h"

/* Func prototypes */
int alloc_cell_cont(CELL *c, size_t size);
void free_cell(CELL *c);
ROW alloc_row(int fields);
void free_row(ROW row, int fields);
INFO *alloc_header(int fields);
void free_header(HEADER h, int fields);
TABLE *alloc_table(int fields);
void free_table(TABLE *t);
void free_gtree(GTree **gtree);

#endif 	
