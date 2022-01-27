#ifndef STDITP_H
#define STDITP_H

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

typedef struct _opt * _OPT;
typedef struct _opts_table * _OPTS_TABLE;
typedef struct _args * _ARGS;
typedef void * ipointer;

typedef enum _sintax_style {
	NONE = 0,
	FUNC = 1,
	VAR = 2,
	MATRIZ = 3,
	TEXT = 4
} _SINTAX_STYLE;

typedef enum _status_prompt {
	ERROR = 0,
	SUCCESSFUL = 1,
	HELP = 2
} _STATUS_PROMPT;

typedef enum _error_info {
	SINTAX = 0,
	FUNCTION = 1,
	ARGS = 2,
	NOT_VAR = 3,
	NOT_VAR_SINTAX = 4,
	FILE_OPEN = 5,
	NOT_VAR_TYPE = 6
} _ERROR_INFO;

_OPTS_TABLE init_opts_table ();
void insert_opt (_OPTS_TABLE, const char *, void * (*func) (_ARGS), int, _SINTAX_STYLE, const char *, ipointer);
char ** get_args (_ARGS);
int get_argc (_ARGS);
char * get_var (_ARGS);
ipointer get_user_data (_ARGS);
_STATUS_PROMPT get_status (_ARGS);
_ERROR_INFO get_error (_ARGS);
int get_opts_number (void);
double get_time_parse (void);
double get_time_opt (void);
void set_opts_number (int);
void set_status (_ARGS, _STATUS_PROMPT);
void * do_opt (_ARGS);
char * n_e_readline (char *, _STATUS_PROMPT);
_ARGS parse (char *, _OPTS_TABLE);

#endif
