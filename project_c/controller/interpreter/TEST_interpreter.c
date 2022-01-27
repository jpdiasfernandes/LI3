#include <stdio.h>
#include <string.h>

#include "includes/interpreter_helpers.h"
#include "includes/messages.h"
#include "../data/includes/variables.h"
#include "../data/includes/data.h"
#include "../queries/includes/queries.h"

int main(){
  print_intro ();

  /* create VAR_LIST */
  VAR_LIST var_list = new_var_list();

  print_load_message (LOADING_START);

  /* load SGR BB files */
  SGR sgr = load_sgr ("/home/jesus/Downloads/users_full.csv","/home/jesus/Downloads/business_full.csv","/home/jesus/Downloads/reviews_1M.csv");

  print_load_message (LOADING_COMPLETE);

  /* insert SGR in the VAR_LIST associated with variable <sgr> */
  var_list_insert (var_list, "sgr", sgr);

  /* load <opts> (insert var_list in the <ipointer> of <show> function) */
  _OPTS_TABLE opts_table = load_opts (var_list); 

  print_time (HELP, 0, 0);
  char *line = NULL;
  line = n_e_readline(line, HELP);

  _ARGS args;
  while(strcmp(line,"-")){
    
    args = parse(line, opts_table);
    if (get_status(args) == ERROR) print_error(get_error(args));
    else do_opt(args);
    
    print_time (get_status(args), get_time_parse(), get_time_opt());
    line = n_e_readline(line, get_status(args));
  }
}
