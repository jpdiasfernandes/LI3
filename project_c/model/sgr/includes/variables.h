#ifndef VARIABLES_H
#define VARIABLES_H

#include <glib-2.0/glib.h>
#include <glib-2.0/gmodule.h>

/* typedef's */
typedef struct var_list * VAR_LIST;
typedef void * var_pointer;

/* init */
VAR_LIST new_var_list (void (*func) (gpointer), void (*func2) (gpointer));

/* functions */
var_pointer get_var_list_value (VAR_LIST, var_pointer key);
void var_list_insert (VAR_LIST, var_pointer key, var_pointer value);
void  _table_destroy (void * data);
void  _sgr_destroy (void * data);
void  _key_destroy (void * data);
void var_list_destroy (VAR_LIST varlist);

#endif
