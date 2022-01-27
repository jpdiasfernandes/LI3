#include "../includes/variables.h"
#include "../../table/includes/table.h"
#include "../includes/sgr.h"

#include <glib-2.0/glib.h>
#include <glib-2.0/gmodule.h>

struct var_list {
	GHashTable * hash_table;
};

gboolean h_strcmp (gconstpointer str1, gconstpointer str2) {
	if (!strcmp(str1, str2)) return TRUE;
	else return FALSE;
}

VAR_LIST new_var_list (void (*key_destroy_func) (gpointer), void (*value_destroy_func) (gpointer)) {
	/* create HASHTABLE */
	GHashTable * hash_table = g_hash_table_new_full (g_str_hash, h_strcmp, key_destroy_func, value_destroy_func);
	
	/* declaration of VAR_LIST */
	VAR_LIST varlist = malloc (sizeof (struct var_list));

	/* fill VARLIST */
	varlist->hash_table = hash_table;

	return varlist;
}

var_pointer get_var_list_value (VAR_LIST varlist, var_pointer key) {
	return g_hash_table_lookup (varlist->hash_table, key);
}

void var_list_insert (VAR_LIST varlist, var_pointer key, var_pointer value) {
	g_hash_table_insert (varlist->hash_table, key, value);
}

void var_list_destroy (VAR_LIST varlist) {
//	g_hash_table_remove_all (varlist->hash_table);
	g_hash_table_destroy (varlist->hash_table);
};

void _table_destroy (void * data) {
	table_destroy (data);
}

void _sgr_destroy (void * data) {
	destroy_sgr (data);
}

void _key_destroy (void * data) {
	//free (data);
}
