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
#include <unistd.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */

#include <errno.h>
#include <string.h>

#ifndef _LIBREBLACKJACK_H_
#include "libreblackjack.h"
#endif

int create_mqueue(const char *name, mqd_t *mq) {

  struct mq_attr attr;
  char *posix_name = malloc(strlen(name)+2);
  snprintf(posix_name, strlen(name)+2, "%s%s", (name[0]=='/')?"":"/", name);

  attr.mq_flags = 0;
  attr.mq_maxmsg = 10;
  attr.mq_msgsize = 128;
  attr.mq_curmsgs = 0;
  
  if (((*mq) = mq_open(posix_name, O_RDWR | O_CREAT, 0666, &attr)) == -1) {
    blackjack_push_error_message(_("'%s' opening message queue '%s'"), strerror(errno), name);
    free(posix_name);
    return -1;
  }
  
  free(posix_name);
  
  return 0;
}

int dealer_to_mqueue(player_t *player, const char *command) {

  static int first = 1;
  
  if (first) {
    if (player->dealer2player.mq == 0) {
      bjcall(create_mqueue(player->dealer2player.name, &player->dealer2player.mq));
    }
    printf(_("writing into player2dealer message queue '%s'... "), player->dealer2player.name);
    fflush(stdout);
  }

  if (mq_send(player->dealer2player.mq, command, strlen(command)+1, 0) == -1) {
    blackjack_push_error_message(_("'%s' writing to message queue '%s'"), strerror(errno), player->dealer2player.name);
    return -1;
  }

  if (first) {
    printf("ok!\n");
    first = 0;
  }
  
  return 0;
}

int player_from_mqueue(player_t *player, char *buffer) {

  static int first = 1;
  
  if (first) {
    if (player->player2dealer.mq == 0) {
      bjcall(create_mqueue(player->player2dealer.name, &player->player2dealer.mq));
    }
    printf(_("waiting for player2dealer message queue '%s'..."), player->player2dealer.name);
    fflush(stdout);
  }

  if (mq_receive(player->player2dealer.mq, buffer, BUF_SIZE-1, NULL) == -1) {
    blackjack_push_error_message(_("'%s' reading from message queue '%s'"), strerror(errno), player->player2dealer.name);
    return -1;
  }

  if (first) {
    printf("ok!\n");
    first = 0;
  }
  
  return 0;
}

