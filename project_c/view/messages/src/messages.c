#include <sys/ioctl.h> /* terminal size */
#include <stdio.h> /* printf() */
#include <unistd.h> /* fork(), execlp(), sleep() */
#include <sys/wait.h> /* wait() */

#include "../includes/messages.h"

void print_intro (void) {
  if (fork() == 0)  execlp("/bin/clear","clear",NULL);
  int exit_status;
  wait(&exit_status);

  printf (ANSI_COLOR_GREEN " ____    ____            " ANSI_COLOR_BLUE "  _________\n"
         ANSI_COLOR_GREEN "|    \\  /    |          " ANSI_COLOR_BLUE "  |         \\" ANSI_COLOR_YELLOW "     Version: " ANSI_COLOR_RESET "1.0\n"
         ANSI_COLOR_GREEN "|     \\/     |          " ANSI_COLOR_BLUE "  |    __    \\" ANSI_COLOR_YELLOW "    Authors: " ANSI_COLOR_RESET "Henrique Costa\n"
         ANSI_COLOR_GREEN "|            | ___    ___ " ANSI_COLOR_BLUE "|   |  \\    |" ANSI_COLOR_RESET "            José Pedro\n"
         ANSI_COLOR_GREEN "|    |\\/|    | \\  \\  /  / " ANSI_COLOR_BLUE "|   |   |   |" ANSI_COLOR_RESET "            Marco Esperança\n"
         ANSI_COLOR_GREEN "|    |  |    |  \\  \\/  /  " ANSI_COLOR_BLUE "|   |__/    |\n"
         ANSI_COLOR_GREEN "|    |  |    |   \\    /   " ANSI_COLOR_BLUE "|          /\n"
         ANSI_COLOR_GREEN "|____|  |____|    \\  /    " ANSI_COLOR_BLUE "|_________/\n"
         ANSI_COLOR_GREEN "                  / /\n                 /_/\n");

}

void print_opts (void) {
  printf (ANSI_COLOR_RESET "[" ANSI_COLOR_YELLOW "?"  ANSI_COLOR_RESET "] Manual\n"
          ANSI_COLOR_RESET "[" ANSI_COLOR_GREEN "#" ANSI_COLOR_RESET "] About project\n"
          ANSI_COLOR_RESET "[" ANSI_COLOR_BLUE "+"  ANSI_COLOR_RESET "] Contribute\n"
          ANSI_COLOR_RESET "[" ANSI_COLOR_RED "-"  ANSI_COLOR_RESET "] Exit\n\n");
}

void print_load_result (int state) {
  switch (state) {
    case 1:
      printf (ANSI_COLOR_GREEN "\r→ "ANSI_COLOR_RESET "Loading users " ANSI_COLOR_GREEN "complete\n" ANSI_COLOR_RESET);
      break;
    case 2:
      printf (ANSI_COLOR_GREEN "\r→ "ANSI_COLOR_RESET "Loading business " ANSI_COLOR_GREEN "complete\n" ANSI_COLOR_RESET);
      break;
    case 3:
      printf (ANSI_COLOR_GREEN "\r→ "ANSI_COLOR_RESET "Loading reviews " ANSI_COLOR_GREEN "complete\n\n" ANSI_COLOR_RESET);
      break;
  }
}

void print_time (_STATUS_PROMPT status, double time_parse, double time_opt) {
  switch (status) {
    case HELP: 
      printf (ANSI_COLOR_RESET "took " ANSI_COLOR_BLUE "%lf" ANSI_COLOR_RESET "s" ANSI_COLOR_BLUE "\n", time_parse + time_opt);
      fflush (stdout);
      break;
    case SUCCESSFUL:
      printf (ANSI_COLOR_RESET "took " ANSI_COLOR_GREEN "%lf" ANSI_COLOR_RESET "s" ANSI_COLOR_GREEN "\n", time_parse + time_opt);
      fflush (stdout);
      break;
    case ERROR:
      printf (ANSI_COLOR_RESET "took " ANSI_COLOR_RED "%lf" ANSI_COLOR_RESET "s" ANSI_COLOR_RED "\n", time_parse);
      fflush (stdout);
      break;
    default:
      break;
  }
}

void print_error (_ERROR_INFO status) {
  switch (status) {
    case 0:
      printf (ANSI_COLOR_CYAN "(ERROR) SYNTAX\n" ANSI_COLOR_RESET);
      break;
    case 1:
      printf (ANSI_COLOR_MAGENTA "(ERROR) FUNCTION NAME\n" ANSI_COLOR_RESET);
      break;
    case 2:
      printf (ANSI_COLOR_BLUE "(ERROR) ARGS\n" ANSI_COLOR_RESET);
      break;
    case 3:
      printf (ANSI_COLOR_YELLOW "(ERROR) VARIABLE DOES NOT EXIST\n" ANSI_COLOR_RESET);
      break;
    case 4:
      printf (ANSI_COLOR_YELLOW "(ERROR) VARIABLE SYNTAX INCORRECT \n" ANSI_COLOR_RESET);
      break;
    case 5:
      printf (ANSI_COLOR_RED "(ERROR) CAN NOT OPEN FILE \n" ANSI_COLOR_RESET);
      break;
    case 6:
      printf (ANSI_COLOR_RED "(ERROR) INVALID COLUMN TYPE \n" ANSI_COLOR_RESET);
    default:  
      break;
  }
}

void print_about_project (void) {
  printf (ANSI_COLOR_YELLOW "\n→" ANSI_COLOR_RESET " Welcome to the " ANSI_COLOR_GREEN "MyD " ANSI_COLOR_RESET "project!\n" ANSI_COLOR_YELLOW "→" ANSI_COLOR_RESET " MyD meaning " ANSI_COLOR_BLUE "My Drawer " ANSI_COLOR_RESET
      "and here is the place that you can make the " ANSI_COLOR_GREEN "fastests searches "ANSI_COLOR_RESET"in the largests CSV files!\n" ANSI_COLOR_YELLOW "→" ANSI_COLOR_RESET " The program have a "ANSI_COLOR_MAGENTA "simple and beautiful " ANSI_COLOR_RESET "command line, where you can make more than " ANSI_COLOR_YELLOW "20 differents " ANSI_COLOR_RESET "searches in your CSV file!\n" ANSI_COLOR_YELLOW "→" ANSI_COLOR_RESET " All of this only is possible because of the work of " ANSI_COLOR_CYAN "Henrique Costa, José Pedro " ANSI_COLOR_RESET "and " ANSI_COLOR_CYAN "Marco Esperança.\n\n");
}

void print_contribute (void) {
  printf (ANSI_COLOR_YELLOW "\n→" ANSI_COLOR_RESET " To contribute to the project: " ANSI_COLOR_BLUE "https://github.com/dium-li3/grupo24/tree/master/project_c\n\n");
}

void print_load (void) {

  printf (ANSI_COLOR_YELLOW "→" ANSI_COLOR_RESET " Loading ");
  fflush (stdout);
  
  while (1) {  
    printf (ANSI_COLOR_YELLOW "." ANSI_COLOR_RESET);
    fflush (stdout);
    sleep (1);
    
    printf (ANSI_COLOR_YELLOW "." ANSI_COLOR_RESET);
    fflush (stdout);
    sleep (1);
    
    fflush (stdout);
    printf (ANSI_COLOR_YELLOW "." ANSI_COLOR_RESET);
    fflush (stdout);
    sleep(1);
    
    printf ("\033[3D");
    fflush (stdout);
    printf ("\033[K");
    fflush (stdout);
    sleep (1);
  }
}

void print_load_sgr_opt (void) {  

  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  int cols = w.ws_col;

  printf ("\n");
  for (int i = 0; i < cols/2 - 9; i++) printf(" ");

  printf (ANSI_COLOR_RESET "Welcome to "ANSI_COLOR_GREEN"My"ANSI_COLOR_BLUE"D"ANSI_COLOR_RESET"! " ANSI_COLOR_YELLOW "\n\n→"ANSI_COLOR_RESET" To start, do you want to load the default files ("ANSI_COLOR_BLUE"reviews"ANSI_COLOR_RESET","ANSI_COLOR_BLUE" businesses "ANSI_COLOR_RESET"and "ANSI_COLOR_BLUE"users"ANSI_COLOR_RESET")? If yes press "ANSI_COLOR_YELLOW"Y"ANSI_COLOR_RESET" (we will assume that they are in the folder indicated in the configuration file) otherwise press "ANSI_COLOR_YELLOW"N"ANSI_COLOR_RESET" ["ANSI_COLOR_GREEN"Y"ANSI_COLOR_RESET"/"ANSI_COLOR_BLUE"N"ANSI_COLOR_RESET"] ");
  
}

void print_load_user_opt (void) {
  printf (ANSI_COLOR_YELLOW "\n→"ANSI_COLOR_RESET" Just one more information: by default, the "ANSI_COLOR_BLUE"friends field"ANSI_COLOR_RESET" of the users file will "ANSI_COLOR_RED"not"ANSI_COLOR_RESET" be read, if you want it to be considered, insert in any line of the configuration file: "ANSI_COLOR_YELLOW"set friends=yes"ANSI_COLOR_RESET "\n\n");
}
