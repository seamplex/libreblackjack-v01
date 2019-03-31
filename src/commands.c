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
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int send_command_card(player_t *player, char *command, card_t *card) {
  char full_command[BUF_SIZE];
  
  if (player->has_split == 0) {
    snprintf(full_command, BUF_SIZE-1, "%s %s", command, card->token[player->token_type]);
  } else {
    snprintf(full_command, BUF_SIZE-1, "%s %s #%d", command, card->token[player->token_type], player->current_hand->id);
  }
  send_command(player, full_command);
   
  return 0;
}

int send_command(player_t *player, const char *fmt, ...) {
  va_list ap;
  char command[BUF_SIZE];
  
  if (player->delay != 0) {
    usleep((useconds_t)(1e6*player->delay));
  }
  
  va_start(ap, fmt);
  vsnprintf(command, BUF_SIZE, fmt, ap);
  va_end(ap);
  
  switch (player->dealer2player.ipc_type) {
    case ipc_none:
      bjcall(dealer_to_stdout(command));
    break;
    case ipc_fifo:
      bjcall(dealer_to_fifo(player, command));
    break;
    case ipc_shmem:
      bjcall(dealer_to_shmem(player, command));
    break;
    case ipc_mqueue:
      bjcall(dealer_to_mqueue(player, command));
    break;
    case ipc_internal:
      bjcall(dealer_to_internal(player, command));
    break;
  }
  
  if (blackjack_ini.log != NULL) {
    fprintf(blackjack_ini.log, "-> %s\n", command);
    fflush(blackjack_ini.log);
  }
  
  return 0;
}

int receive_command(player_t *player, char *command) {

  
  // TODO: function pointers?
  
  switch (player->player2dealer.ipc_type) {
    case ipc_none:
      bjcall(player_from_stdin(inputbuffer));
    break;
    case ipc_fifo:
      bjcall(player_from_fifo(player, inputbuffer));
    break;
    case ipc_shmem:
      bjcall(player_from_shmem(player, command));
    break;
    case ipc_mqueue:
      bjcall(player_from_mqueue(player, command));
    break;
    case ipc_internal:
      bjcall(player_from_internal(player, command));
    break;
  }
  
  if (blackjack_ini.log != NULL) {
    fprintf(blackjack_ini.log, "<- %s\n", command);
    fflush(blackjack_ini.log);
  }

  return 0;
}
