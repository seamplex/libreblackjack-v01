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

#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

player_t *new_player(const char *name) {
  player_t *player = calloc(1, sizeof(player_t));
  player->name = strdup(name);
//  player->dealer2player.fd = -1;
//  player->player2dealer.fd = -1;
  // TODO: multi-player
  blackjack.players = player;
//  list_append(blackjack.players, player);
  return player;
}

void destroy_player(player_t *player) {
  
  char buffer[BUF_SIZE];
  
  switch (player->dealer2player.ipc_type) {
    case ipc_fifo:
      if (player->dealer2player.buffered) {
        fclose(player->dealer2player.fp);
      } else {
        close(player->dealer2player.fd);
      }
      unlink(player->dealer2player.name);
    break;
    case ipc_shmem:
      if (player->dealer2player.shmem != NULL) {
        shm_unlink(player->dealer2player.name);
      }
      
      if (player->dealer2player.sem_read != NULL) {
        sem_close(player->dealer2player.sem_read);
        sprintf(buffer, "%s_read", player->dealer2player.name);
        sem_unlink(buffer);
      }
      
      if (player->dealer2player.sem_written != NULL) {
        sem_close(player->dealer2player.sem_written);
        sprintf(buffer, "%s_written", player->dealer2player.name);
        sem_unlink(buffer);
      }
    break;
    case ipc_mqueue:
      mq_close(player->dealer2player.mq);
      mq_unlink(player->dealer2player.name);
    break;
    default:
      ;
    break;
  }

  switch (player->player2dealer.ipc_type) {
    case ipc_fifo:
      if (player->player2dealer.buffered) {
        fclose(player->player2dealer.fp);
      } else {
        close(player->player2dealer.fd);
      }
      unlink(player->player2dealer.name);
    break;
    case ipc_shmem:
      if (player->player2dealer.shmem != NULL) {
        shm_unlink(player->player2dealer.name);
      }
      
      if (player->player2dealer.sem_read != NULL) {
        sem_close(player->player2dealer.sem_read);
        sprintf(buffer, "%s_read", player->player2dealer.name);
        sem_unlink(buffer);
      }
      
      if (player->player2dealer.sem_written != NULL) {
        sem_close(player->player2dealer.sem_written);
        sprintf(buffer, "%s_written", player->player2dealer.name);
        sem_unlink(buffer);
      }
    break;
    case ipc_mqueue:
      mq_close(player->player2dealer.mq);
      mq_unlink(player->player2dealer.name);
    break;
    default:
      ;
    break;
  }
  
  free(player->dealer2player.name);
  free(player->player2dealer.name);
  free(player->name);
  destroy_hands(&player->hands);
  // TODO
  blackjack.players = NULL;
//  LL_DELETE(blackjack.players, player);
  free(player);
  player = NULL;
  return;
}

// it is not wortwhile to have a hash list just for this
player_t *get_player(const char *name) {
  player_t *player;
  
  for (player = blackjack.players; player != NULL; player = player->next) {
    if (strcmp(player->name, name) == 0) {
      return player;
    }
  }
  return NULL;
}

player_t *get_or_define_player(const char *name) {
  player_t *player;
  if ((player = get_player(name)) == NULL) {
    player = new_player("player");
  }
  return player;
}

player_t *player_from_section(const char *section) {
  player_t *player;
  char *name;
  
  if (section == NULL || section[0] == '\0') {
    name = strdup("player");
  } else {
    name = strdup(section);
  }
  
  if (blackjack.players == NULL) {
    player = new_player(name);
  } else {
    player = get_or_define_player(name);
  }
  
  free(name);
  return player;

}
