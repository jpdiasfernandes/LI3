#ifndef _DATA_H_
#define _DATA_H_

#include "../../table/includes/table.h"

typedef enum OPERATOR {
	LT = -1,
	EQ = 0,
	GT = 1,
	NONE_OP = 2
} OPERATOR;

void* fill_table (TABLE *t, FILE *f, int delimiter_quantity, const char *types, char * delim, TABLE * stats, TABLE * usr, TABLE * rvw);
char * parsing_string (char * string, const char * delim);
char ** parsing_line (char* line, const char* delimiter, int delimiter_quantity);
void ** parsing_content(char **content, const char *types, int fields);
int * parsing_cols (char * array, int * num_cols);
int parsing_user_friends (FILE * config);
int parsing_category (char * category, char * categories);
char ** parsing_header (FILE *, char *, int *); 
void ** parsing_str (char ** str, int fields);
void* fill_table_str (TABLE *t, FILE *f, int delimiter_quantity, char * delim);
OPERATOR parsing_operator (char *);
int parsing_word (char * word, char * word_cmp);

#endif
