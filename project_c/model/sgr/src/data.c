#include <stdio.h>
#include <stdlib.h> /* malloc() */
#include <string.h> /* strsep(), strdup() */

#include "../includes/data.h"
#include "../../table/includes/search.h"

#define DEFAULT_LINE_SIZE 1024
#define REVIEWS 9

void * fill_table (TABLE *t, FILE *f, int delimiter_quantity, const char *types, char * delim, TABLE * stats, TABLE * usr, TABLE * bsn) {

	/* declaration of buffer for getline() */
	char * buffer = malloc (sizeof (char) * DEFAULT_LINE_SIZE);
	size_t size = DEFAULT_LINE_SIZE;

	/* declaration of matrix for the <lines fields> */
	char ** content;
	void **parsed_content;
	int fields = get_fields(t);
	int reviews_validate = 0;
	
	while(getline(&buffer, &size, f) > 0) {
		reviews_validate = 0;

		buffer[strlen(buffer)-1] = '\0';
		content = parsing_line(buffer, delim, delimiter_quantity);		
		
		if (content) parsed_content = parsing_content(content, types, fields);
		
		if (content){
			if (delimiter_quantity == REVIEWS &&
					table_search_row_id (usr, parsed_content[1]) != NULL &&
					table_search_row_id (bsn, parsed_content[2]) != NULL) {
				
				table_append_generic(t, parsed_content);
				reviews_validate = 1;
			}
			else if (delimiter_quantity != REVIEWS) table_append_generic(t, parsed_content);
			
			/* append stats table (stars)*/
			if(delimiter_quantity == REVIEWS && reviews_validate) {
			char **headers = get_header_names(get_headers(t), 9);
				
				if(strcmp(headers[0], "review_id") == 0)  {
					
					char * business_id = *(char **)parsed_content[2];
					float stars = *(float *)parsed_content[3];
					int quant = 1;
					float mean_stars = stars; /* for first insert */
					
					ROW tmp = table_search_row_id(stats, &business_id);
					
					if (tmp != NULL) {
						
						stars += *(float *)get_row_content_by_column(tmp, 1);
						quant += *(int *)get_row_content_by_column(tmp, 2);
						mean_stars = stars / quant;
					
					}
					
					table_append(stats,  &business_id, &mean_stars, &quant);
				}
			
				for (int i = 0; i < get_fields (t); i++)
					free (headers[i]);
			}
			
			int * types = get_header_types (get_headers (t), get_fields (t)); 

			for (int i = 0 ; i < delimiter_quantity; i++) {
				free (content[i]);
			}

			free (content);
				
			for (int i = 0; i < delimiter_quantity; i++) {
					if (types[i] == COL_TYPE_STRING) {
						char * string = *(char **) parsed_content[i];
						free (string);
					}
					free (parsed_content[i]);
			}
			free (parsed_content);
		
			free(types);

		}
	}
	
	free (buffer);
	return NULL;
}

int * parsing_cols (char * array, int * num_cols) {

	char * copy = strdup (array);
	char * init_s_sep = copy;
	char * token = strsep (&copy, "{");

	/* string does not start by delim */
	if (!token || * token != '\0') return NULL;
	
	int array_size = 10;
	int * return_array = malloc (sizeof (int) * array_size);
	int array_element;
	
	for (int i = 0; token != NULL && copy && array[copy - init_s_sep - 1] != '}';) {
		token = strsep (&copy, ":}");
		if (token && *token == '\0') return NULL;
		
		if (array[copy - init_s_sep - 1] != '}') {
			if (i > array_size) {
				array_size*=2;
				return_array = realloc (return_array, array_size);
			}
			if (sscanf (token, "%d", &array_element) != EOF) {return_array[i++] = array_element; *num_cols = *num_cols + 1;}
			else return NULL;
		}
	}

	if (copy && array[copy - init_s_sep - 1] == '}' && (sscanf (token, "%d", &array_element) != EOF)) {return_array[*num_cols] = array_element; *num_cols = *num_cols + 1; return return_array;}

	return NULL;
}

char * parsing_string (char * string, const char * delim) {
	char * copy = strdup (string);
	char * token = strsep (&copy, delim);
	char * final_token;

	/* string does not start by delim */
	if (!token || * token != '\0') return NULL;
	
	token = strsep (&copy, delim);
	
	/* string does not have content */
	if (!token || * token == '\0') return NULL;

	final_token = strsep (&copy, delim);
	
	/* don´t find last delim or string have something after last delim */
	if ((copy != NULL) || * final_token != '\0') return NULL;

	return token;
}

char ** parsing_line(char* line, const char* delimiter, int delimiter_quantity) {
	
	int i = 0;
	char ** content = malloc(sizeof(char*)*(delimiter_quantity ));
	char * copy = strdup(line);
	char * init_copy = copy;
	char * token = copy;
	
	token = strsep(&copy, ";");
	while(i < delimiter_quantity && token != NULL) {

		/* for <reviews> and <business> that can be empty if is the last field */
		if (*token == '\0' && i != delimiter_quantity - 1) return NULL;

		/* for <users> without last field -> can't have empty fields in all postions*/
		if (*token == '\0' && delimiter_quantity == 2) return NULL;
		
		content[i] = (void *) strdup(token);
		i++;
		
		/* special case in order to don't accept +1 field */
		if (delimiter_quantity != 2 && (i == delimiter_quantity) && copy != NULL) return NULL;
	
		/* special case for <users> without last field -> -1 fiel accept fail */
		if ((delimiter_quantity == 2) && (i == 2) && (copy == NULL)) return NULL;

		token = strsep(&copy, ";");
	}

	if(i == delimiter_quantity && copy == NULL) {free (init_copy); return content;}
	else {free (init_copy); return NULL;}
}

void ** parsing_content(char **content, const char *types, int fields) {
	int i = 0;
	void **r = malloc(sizeof(void *) * fields);
	while(i < fields) {
		switch(*types++) {
			case 's':
				r[i] = malloc(sizeof(char *));
				*(char **)r[i] = strdup(content[i]);
				i++;
				break;
			case 'd':
				r[i] = malloc(sizeof(int));
				sscanf(content[i], "%d", (int *)r[i]);
				i++;
				break;
			case 'c':
				r[i] = malloc(sizeof(char));
				sscanf(content[i], "%c", (char *)r[i]);
				i++;
				break;
			case 'f':
				r[i] = malloc(sizeof(float));
				sscanf(content[i], "%f" , (float *)r[i]);
				i++;
				break;
			case 'b':
				r[i] = malloc(sizeof(double));
				sscanf(content[i], "%lf" , (double *)r[i]);
				i++;
				break;
			default:
				break;
		}
	}

	for (i = 0; i < fields; i++)
		if(r[i] == NULL) return NULL;

	return r;
}

int parsing_user_friends (FILE * fp) {
	char buff[100];
	while (fgets (buff, 100, fp)) {
		buff[strlen (buff) - 1] = '\0';
		if (!strcmp(buff, "set friends=yes")) return 1;
	}

	return 0;
}

int parsing_category (char * category, char * categories) {
	char * copy = strdup (categories);
	char * init_copy = copy;
	
	/* get <token> before first "," */
	char * token = strsep (&copy, ",");

	while (token != NULL) {
		if (!strcmp (token, category)) return 1;
		token = strsep (&copy, ",");
	}

	/* free <strdup> allocated memmory */
	free (init_copy);

	return 0;
}

char ** parsing_header (FILE * fp, char * delim, int * fields) {
	char * buff = malloc (sizeof (char) * 256);
	size_t size = 256;
	getline (&buff, &size, fp);
	char * token = buff;
	int cont = 0;

	int header_size = 10;
	char ** headers = malloc (sizeof (char *) * header_size);
	while (token != NULL && buff != NULL) {

		if (*fields == header_size) {
			header_size*=2;
			headers = realloc (headers, header_size);
		}

		token = strsep (&buff, delim);
		headers[cont++] = strdup (token);
		*fields = *fields + 1;
	}

	return headers;
}

void * fill_table_str (TABLE *t, FILE *f, int delimiter_quantity, char * delim) {

	/* declaration of buffer for getline() */
	char * buffer = malloc (sizeof (char) * DEFAULT_LINE_SIZE);
	size_t size = DEFAULT_LINE_SIZE;

	/* declaration of matrix for the <lines fields> */
	char ** content;
	void **parsed_content;
	int fields = get_fields(t);
	
	while(getline(&buffer, &size, f) > 0) {

		buffer[strlen(buffer)-1] = '\0';
		content = parsing_line(buffer, delim, delimiter_quantity);		
	
		if (content) parsed_content = parsing_str(content,fields);
		
		if (content){
			table_append_generic(t, parsed_content);
			
			
			int * types = get_header_types (get_headers (t), get_fields (t)); 

			for (int i = 0 ; i < delimiter_quantity; i++) {
				free (content[i]);
			}

			free (content);
				
			for (int i = 0; i < delimiter_quantity; i++) {
					if (types[i] == COL_TYPE_STRING) {
						char * string = *(char **) parsed_content[i];
						free (string);
					}
					free (parsed_content[i]);
			}
			free (parsed_content);
		
			free(types);

		}
	}
	
	free (buffer);
	return NULL;
}

void ** parsing_str(char **content, int fields) {
	int i = 0;
	void **r = malloc(sizeof(void *) * fields);
	while(i < fields) {
				r[i] = malloc(sizeof(char *));
				*(char **)r[i] = strdup(content[i]);
				i++;
	}

	for (i = 0; i < fields; i++)
		if(r[i] == NULL) return NULL;

	return r;
}

OPERATOR parsing_operator (char * str) {
	if (!strcmp (str, "LT")) return LT;
	if (!strcmp (str, "EQ")) return EQ;
	if (!strcmp (str, "GT")) return GT;
	return NONE_OP;
}

int parsing_word(char *word, char *word_cmp) {
	const char * delim = " !\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
	char * copy = strdup(word_cmp);

	char * init_copy = copy;

	char * token = strsep(&copy, delim);

	while(token != NULL) {
		if (strcmp(token, word) == 0) return 1;
		token = strsep(&copy, delim);
	}

	return -1;

	free(init_copy);
}
