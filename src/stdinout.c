/*------------ -------------- -------- --- ----- ---   --       -            -
 *  libreblackjack
 *
 *  Copyright (C) 2016 jeremy theler
 *
 *  This file is part of libreblackjack.
 *
 *  libreblackjack is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  libreblackjack is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with libreblackjack.  If not, see <http://www.gnu.org/licenses/>.
 *------------------- ------------  ----    --------  --     -       -         -
 */
#include "libreblackjack.h"
#ifdef HAVE_LIBREADLINE
 #include <readline/readline.h>
 #include <readline/history.h>
#endif

#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int dealer_to_stdout(player_t *player, const char *command) {

  // TODO: choose colors
  if (stdout_opts.isatty) {
    if (player->delay != 0) {
      usleep((useconds_t)(1e6*player->delay));
    }
    
    if (command[strlen(command)-1] != '?') {
      printf("%s<-- %s%s%s\n", stdout_opts.yellow, stdout_opts.green, command, stdout_opts.reset);
    } else {
      printf("%s%s%s", stdout_opts.cyan, command, stdout_opts.reset);
    }
  } else {
    printf("%s\n", command);
  }
  
  return 0;
}


#ifdef HAVE_LIBREADLINE
char *line_read = (char *)NULL;
char prompt[32];
#endif
  
int player_from_stdin(player_t *player, char *buffer) {
  if (stdout_opts.isatty) {
#ifdef HAVE_LIBREADLINE
    if (prompt[0] == '\0') {
      sprintf(prompt,  " %s>%s ", stdout_opts.cyan, stdout_opts.reset);
    }

    if (line_read) {
      free(line_read);
      line_read = (char *)NULL;
    }
    line_read = readline(prompt);
    if (line_read && *line_read) {
      add_history(line_read);
      strncpy(buffer, line_read, BUF_SIZE-1);
    } else {
      buffer[0] = '\0';
    }
  
#else
    char *newline;

    printf(" %s>%s ", stdout_opts.cyan, stdout_opts.reset);
    if (fgets(buffer, BUF_SIZE-1, stdin) == NULL) {
      return -1;
    }
    // strip \n
    newline = strchr(buffer, '\n');
    if (newline != NULL) {
      *newline = '\0';
    }
#endif
  } else {
    char *newline;
    
    if (fgets(buffer, BUF_SIZE-1, stdin) == NULL) {
      return -1;
    }
    // strip \n
    newline = strchr(buffer, '\n');
    if (newline != NULL) {
      *newline = '\0';
    }
  }
  return 0;
}

void free_rl_stdin(void) {
#ifdef HAVE_LIBREADLINE
  if (line_read) {
    free(line_read);
    line_read = (char *)NULL;
  }
#endif
  return;
}
