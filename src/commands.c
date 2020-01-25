/*------------ -------------- -------- --- ----- ---   --       -            -
 *  libreblackjack
 *
 *  Copyright (C) 2016--2020 jeremy theler
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

int write_formatted_card(player_t *player, int dealer, char *command, card_t *card) {
  char full_command[BUF_SIZE];
  
  if (player->has_split == 0 || dealer != 0) {
    snprintf(full_command, BUF_SIZE-1, "%s %s", command, card->token[player->token_type]);
  } else {
    snprintf(full_command, BUF_SIZE-1, "%s %s #%d", command, card->token[player->token_type], player->current_hand->id);
  }
  player->write(player, full_command);
   
  return 0;
}

int write_formatted(player_t *player, const char *fmt, ...) {
  va_list ap;
  char command[BUF_SIZE];
  
  va_start(ap, fmt);
  vsnprintf(command, BUF_SIZE, fmt, ap);
  va_end(ap);
  
  bjcall(blackjack.current_player->write(player, command));
  
  if (blackjack_ini.log != NULL) {
    fprintf(blackjack_ini.log, "-> %s\n", command);
    fflush(blackjack_ini.log);
  }
  
  return 0;
}
