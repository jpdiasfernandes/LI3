#include <stdio.h>
#include <string.h> /* strcmp() */
#include <unistd.h> /* fork(), kill() */
#include <sys/time.h> /* struct's and gettimeofday() */ 

#include "model/sgr/includes/sgr.h" /* SGR typedef and load_sgr() */
#include "controller/interpreter/includes/interpreter_helpers.h" /* load_opts() */
#include "view/messages/includes/messages.h" /* print_error(), print_time() */
#include "model/sgr/includes/variables.h" /* VAR_LIST, new_var_list() */
#include "controller/interpreter/includes/stditp.h" /* n_e_readline(), parse(), get_status(), do_opt(), get_time's() */

struct timeval start_load;
struct timeval end_load;

int main(){
  print_intro ();

  /* create VAR_LIST's */
  VAR_LIST var_list_sgr = new_var_list (_key_destroy, _sgr_destroy);
  VAR_LIST var_list_tables = new_var_list (_key_destroy, _table_destroy);

  /* check if user want default files */
  print_load_sgr_opt ();
  char opt = getc (stdin);

  if (opt == 'Y') {
    /* user want to load default files */
    print_load_user_opt ();

 //   int load_pid;
 //   if ((load_pid = fork()) == 0) {
 //     /* child process - load() */
 //     print_load ();
 //     _exit (0);
 //   }

    /* load SGR BB files */
    gettimeofday (&start_load, NULL);
    SGR sgr = load_sgr ("users_full.csv","business_full.csv","reviews_1M.csv");
    gettimeofday (&end_load, NULL);
  
    /* stop <print_load> */
 //   kill (load_pid, SIGKILL);
 //   print_load_result (1);

    /* insert SGR in the VAR_LIST associated with variable <sgr> */
    var_list_insert (var_list_sgr, "sgr", sgr);
  }

  /* load <opts> (insert var_list in the <ipointer> of <show> function) */
  _OPTS_TABLE opts_table = load_opts (var_list_tables, var_list_sgr); 

  /* print <opts> */
  print_opts ();

  /* get <load-time> */
  double time = ((double) (end_load.tv_sec - start_load.tv_sec) + (end_load.tv_usec - start_load.tv_usec) / 1000000.0f);
  
  /* get user command */
  print_time (HELP, 0, time);
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

  /* destroy VAR_LIST content (variables) */
  var_list_destroy (var_list_sgr);
  var_list_destroy (var_list_tables);
}
