#include <stdio.h> /* Types */
#include <stdlib.h> /* calloc(), free(), realloc() */
#include <string.h> /* strcmp() , strsep(), strlen(), memcpy() */
#include <readline/readline.h> /* readline() */
#include <readline/history.h> /* add_history() */
#include <time.h> /* time(), difftime() */
#include <sys/time.h> /* structs, gettimeofday () */
#include "../includes/stditp.h"

#define DEFAULT_OPTS_NUMBER 20
#define ERROR_SINTAX(A) {A->status = ERROR; A->error_info = SINTAX;}
#define ERROR_FUNC(A) {A->status = ERROR; A->error_info = FUNCTION;}
#define ERROR_ARGS(A) {A->status = ERROR; A->error_info = ARGS;}

struct _opt {
	const char * func_name;
	void * (*func) (_ARGS);
	int n_args;
	_SINTAX_STYLE sintax;
	const char * info;
	ipointer user_data;
};

struct _opts_table {
	_OPT opts_table;
	int size;
	int occupation;
};

struct _args {
	void * (*func) (_ARGS);
	char ** args;
	int argc;
	char * var;
	_STATUS_PROMPT status;
	_ERROR_INFO error_info;
	ipointer user_data;
};

int __opts_number = DEFAULT_OPTS_NUMBER;
char * __init_s_sep;
const char * __delims = "=(,);[";
const char * __delims_args = ",);";
const char * __delims_matriz = "[];";
const char * __delims_var = "=";
//time_t start_parse;
//time_t end_parse;
//time_t start_opt;
//time_t end_opt;
_SINTAX_STYLE __context_sintax;
struct timeval end_parse, start_parse;
struct timeval end_opt, start_opt;

_OPTS_TABLE init_opts_table (void) {
	_OPTS_TABLE opts_table = calloc (sizeof (struct _opts_table), 1);
	
	opts_table->opts_table = calloc (sizeof (struct _opt), __opts_number);
	opts_table->size = __opts_number;

	return opts_table;
}

static _ARGS init_args (void) {
	_ARGS args = calloc (sizeof (struct _args),1);
	return args;
}

char ** get_args (_ARGS args) {
	int argc = get_argc (args);
 	char ** copy = calloc (sizeof (char *), argc);

	for (int i = 0; i < argc; i++)
		copy[i] = (char *) strdup (args->args[i]);

	return copy;
}

int get_argc (_ARGS args) {
	return args->argc;
}

char * get_var (_ARGS args) {
	char * var = NULL;
	if (args->var != NULL) var = (char *) strdup (args->var);
	return var;
}

ipointer get_user_data (_ARGS args) {
	return args->user_data;
}

_STATUS_PROMPT get_status (_ARGS args) {
	return args->status;
}

_ERROR_INFO get_error (_ARGS args) {
	return args->error_info;
}

int get_opts_number (void) {
	return __opts_number;
}

double get_time_parse (void) {
	return ((double) (end_parse.tv_sec - start_parse.tv_sec) + (end_parse.tv_usec - start_parse.tv_usec) / 1000000.0f);
	//return difftime(end_parse, start_parse);
}

double get_time_opt (void) {
	return ((double) (end_opt.tv_sec - start_opt.tv_sec) + (end_opt.tv_usec - start_opt.tv_usec) / 1000000.0f);
}

void set_opts_number (int new_value) {
	__opts_number = new_value;
}

void set_status (_ARGS args, _STATUS_PROMPT status) {
	args->status = status;
}

void * do_opt (_ARGS args) {
	
	//start_opt = time (NULL);
	gettimeofday (&start_opt, NULL);
	args->func(args);
	gettimeofday (&end_opt, NULL);
	//end_opt = time (NULL);

	return NULL;
}

char * n_e_readline (char * line, _STATUS_PROMPT status) {
	if (line) {
		free (line);
		line = (char *) NULL;
	}
  
	switch (status) {
    case HELP:  
  		line = readline (ANSI_COLOR_BLUE "→ " ANSI_COLOR_RESET);
      break;
    case SUCCESSFUL:
  		line = readline (ANSI_COLOR_GREEN "→ " ANSI_COLOR_RESET);
      break;
    case ERROR:
  		line = readline (ANSI_COLOR_RED "→ " ANSI_COLOR_RESET);
      break;
    default:
      break;
  }

	if (line && *line)
		add_history (line);

	return line;
}

void insert_opt (_OPTS_TABLE opts_table, const char * func_name, void * (*func) (_ARGS), int n_args, _SINTAX_STYLE sintax, const char * info, ipointer user_data) {
	int occupation = opts_table->occupation;

	if (opts_table->size == occupation) 
		opts_table->opts_table = realloc (opts_table->opts_table, opts_table->size *= 2);
	
	opts_table->opts_table[occupation].info = (char *) strdup (info);
	opts_table->opts_table[occupation].func_name = (char *) strdup (func_name);
	opts_table->opts_table[occupation].n_args = n_args;
	opts_table->opts_table[occupation].sintax = sintax;
	opts_table->opts_table[occupation].func = func;
	opts_table->opts_table[occupation].user_data = user_data;
	opts_table->occupation++;
}

static int invalid_ssep (char * token, char * copy) {
	return ((!token || *token == '\0' || !copy) ? 1: 0);
}

static _SINTAX_STYLE parse_style (char * line) {
	char * copy = (char *) strdup (line);
	__init_s_sep = copy;

	char * token = strsep (&copy, __delims);

	if (token && (*token == *__init_s_sep) && *token != '\0' && !copy) {__context_sintax = TEXT; return TEXT;}
	else if (invalid_ssep (token, copy)) return NONE;

	char * delim = &line[copy - __init_s_sep - 1];
	if (!delim) return NONE;	
	switch (*delim) {
		case '(' : {__context_sintax = FUNC; return FUNC;}
		case '=':
			token = strsep (&copy, __delims);
			if (invalid_ssep (token, copy)) return NONE;

			delim = &line[copy - __init_s_sep - 1];
			if (!delim) {return NONE;}
			if (*delim == '(') {__context_sintax = VAR; return VAR;}
			if (*delim == '[') {__context_sintax = MATRIZ; return MATRIZ;}
		default: break;
	}
	return NONE;
}

static int parse_args (int n_args, _ARGS  args, char * line, char * copy) {
	char bef_delim[] = ";";
	char *act_delim;
	char * token = strsep (&copy, __delims_args);
	if (copy) act_delim = &line [copy - __init_s_sep - 1];

	int cont = 0;
	int n_comma = 0;

	if (!copy) {ERROR_SINTAX(args); return 0;}

	if (token && *token == '\0' && *act_delim != ' ') {ERROR_ARGS(args); return 0;}

	while (token != NULL && *act_delim != ';' && copy != NULL && *copy != '\0') {
		if ((*token == '\0') && ((*act_delim != ';') || (*bef_delim != ')'))) {ERROR_ARGS(args);return 0;}

		if ((*act_delim == ',') || ((*act_delim == ')') && (cont == n_args - 1))) {
			args->args[cont] = (char *) strdup (token);
			cont++;
		}

		if (*act_delim == ',') n_comma++;
		
		*bef_delim = *act_delim;
		token = strsep (&copy, __delims_args);
		if (token && copy) act_delim = &line[copy - __init_s_sep - 1];
	}

	if (*act_delim != ';') {ERROR_SINTAX(args); return 0;} 
	else if (cont != n_args || n_comma != n_args - 1) {ERROR_ARGS(args); return 0;}
	
	args->status = SUCCESSFUL;
	return 1;
}

static void * func_only (char * line, _OPTS_TABLE opts_table, _ARGS args) {
	char * copy = (char *) strdup (line);
	__init_s_sep = copy;
	
	char * token = strsep (&copy, __delims);
	if (invalid_ssep (token, copy)) ERROR_SINTAX(args);
	

	int opt = opts_table->occupation - 1;
	int args_parse_result = 0;
	int incorrect_name = 1;

	for (; opt >= 0 && !args_parse_result; opt--) {
		if (!strcmp(token, opts_table->opts_table[opt].func_name)
				&& (opts_table->opts_table[opt].sintax == __context_sintax)) {

			incorrect_name = 0;
			args->func = opts_table->opts_table[opt].func;
			args->argc = opts_table->opts_table[opt].n_args;
			args->user_data = opts_table->opts_table[opt].user_data;
			args->args = calloc(sizeof(char *), opts_table->opts_table[opt].n_args);

			args_parse_result = parse_args (opts_table->opts_table[opt].n_args, args, line, copy);
		}
	}

	if (incorrect_name) ERROR_FUNC(args);

	return NULL;
}

static void * matriz_insp (char * line, _OPTS_TABLE opts_table, _ARGS args) {
	char * copy = (char *) strdup (line);
	__init_s_sep = copy;

	char * token = strsep (&copy, __delims_matriz);
	if (invalid_ssep (token, copy) || line[copy - __init_s_sep - 1] != '[') {ERROR_SINTAX(args); return NULL;}
	
	args->args = calloc (sizeof (char *), 3);
	args->args[0] = (char *) strdup (token);
	
	token = strsep (&copy,__delims_matriz);
	if (invalid_ssep (token, copy) || line[copy - __init_s_sep - 1] != ']') {ERROR_SINTAX(args); return NULL;}

	args->args[1] = malloc (sizeof (char *));
	args->args[1] = (char *) strdup (token);

	token = strsep (&copy, __delims_matriz);
	if (!token || * token != '\0' || !copy || line[copy - __init_s_sep - 1] != '[') {ERROR_SINTAX(args); return NULL;}
	
	token = strsep (&copy, __delims_matriz);
	if (invalid_ssep (token, copy) || line[copy - __init_s_sep - 1] != ']') {ERROR_SINTAX(args); return NULL;}

	args->args[2] = malloc (sizeof (char *));
	args->args[2] = (char *) strdup (token);

	token = strsep (&copy, __delims_matriz);
	if (!token || * token != '\0' || !copy || line[copy - __init_s_sep - 1] != ';') {ERROR_SINTAX(args); return NULL;}

	args->argc = 3;
	int occupation = opts_table->occupation;
	for (int i = 0; i < occupation; i++) {
		if (opts_table->opts_table[i].sintax == MATRIZ) {
			args->func = opts_table->opts_table[i].func;
			args->user_data = opts_table->opts_table[i].user_data;
			occupation  = -1;
		}
	}

	args->status = SUCCESSFUL;

	return NULL;
}

static void * var_func (char * line, _OPTS_TABLE opts_table, _ARGS args, void * (*func) (char *, _OPTS_TABLE, _ARGS)){
	char * copy = (char *) strdup (line);
	char * token = strsep (&copy, __delims_var);

	if (invalid_ssep (token, copy)) {ERROR_SINTAX(args); return NULL;}

	args->var = (char *) strdup(token);

	func (copy, opts_table, args);
	return NULL;
}

static void * text (char * line, _OPTS_TABLE opts_table, _ARGS args) {
	int opts_number = opts_table->occupation;
	
	for (int i = 0; i < opts_number; i++) {
		if (!strcmp (line, opts_table->opts_table[i].func_name) && opts_table->opts_table[i].sintax == TEXT) {
			args->argc = 0;
			args->args = NULL;
			args->func = opts_table->opts_table[i].func;
			args->user_data = opts_table->opts_table[i].user_data;
			args->status = SUCCESSFUL;
			return NULL;
		}
	}

	ERROR_SINTAX(args);
	return NULL;
}

_ARGS parse (char * line, _OPTS_TABLE opts_table) {
	gettimeofday (&start_parse, NULL);
	//start_opt = end_opt = 0;
	//start_parse = time (NULL);
	//start_opt.tv_usec = 0; end_opt.tv_usec = 0;
	//start_opt.tv_sec = 0; end_opt.tv_sec = 0;
	_ARGS args = init_args();
	
	_SINTAX_STYLE sintax = parse_style (line);
	if (sintax == NONE) {
		ERROR_SINTAX(args);
	} else {
		switch (sintax) {
			case 1 :
				func_only (line, opts_table, args);
				break;
			case 2 :
				var_func (line, opts_table, args, func_only);
				break;
			case 3 :
				var_func (line, opts_table, args, matriz_insp);
				break;
			case 4:
				text (line, opts_table, args);
			default:
				break;
		}
	}

	gettimeofday (&end_parse, NULL);
	//end_parse = time (NULL);
	return args;
}

