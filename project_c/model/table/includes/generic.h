#ifndef _GENERIC_H_
#define _GENERIC_H_

#include "table.h"
#include <glib-2.0/glib.h>

int fmt_generic_type(int count, int *fields, const char *fmt);
int header_generic_insert(HEADER h, int type, char *header, int col);
void *void_ptr_generic_insert(void *cont, int type, void *arg);
int cell_generic_insert(CELL *c, int type, int size, void *arg);
void free_void_ptr_generic(void *cont, int type);
gint key_generic_cmp(gconstpointer key1, gconstpointer key2, gpointer data);

#endif 
