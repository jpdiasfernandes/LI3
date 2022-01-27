#ifndef MESSAGES_H
#define MESSAGES_H

#include "../../../controller/interpreter/includes/stditp.h"

#define LOADING_START 1
#define LOADING_COMPLETE 0

void print_intro (void);
void print_time (_STATUS_PROMPT, double time_parse, double time_opt);
void print_error (_ERROR_INFO);
void print_about_project (void);
void print_contribute (void);
void print_load_result (int);
void print_load (void);
void print_load_sgr_opt (void);
void print_load_user_opt (void);
void print_opts (void);

#endif

