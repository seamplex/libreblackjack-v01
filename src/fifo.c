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
#include <string.h>
#include <errno.h>

#include <sys/select.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <fcntl.h>

int create_fifo(const char *name) {
  if (mkfifo(name, 0666) != 0) {
    if (errno != EEXIST)  {
      blackjack_push_error_message("'%s' creating fifo '%s'", strerror(errno), name);
      return -1;
    }
  }
  
  return 0;
}

int write_to_fifo(player_t *player, const char *command) {
  
  if (player->dealer2player.buffered) {
    if (player->dealer2player.fp == NULL) {
      // TODO: elegir RO o WR
      if (create_fifo(player->dealer2player.name) != 0) {
        return -1;
      }

      printf("waiting for dealer2player buffered fifo '%s'...", player->dealer2player.name);
      fflush(stdout);
      if ((player->dealer2player.fp = fopen(player->dealer2player.name, "w")) == NULL) {
        blackjack_push_error_message("opening buffered fifo '%s' for writing: %s", player->dealer2player.name, strerror(errno));
        return -1;
      }
      printf("ok!\n");
    }
    
    fputs(command, player->dealer2player.fp);
    fputs("\n", player->dealer2player.fp);
    fflush(player->dealer2player.fp);
    
  } else {
    if (player->dealer2player.fd == 0) {
      // TODO: elegir RO o WR
      if (create_fifo(player->dealer2player.name) != 0) {
        return -1;
      }
      printf("waiting for dealer2player unbuffered fifo '%s'...", player->dealer2player.name);
      fflush(stdout);
      if ((player->dealer2player.fd = open(player->dealer2player.name, O_WRONLY)) == -1) {
        blackjack_push_error_message("opening unbuffered fifo '%s' for writing: %s", player->dealer2player.name, strerror(errno));
        return -1;
      }
      printf("ok!\n");
    }
  
    write(player->dealer2player.fd, command, strlen(command));
    write(player->dealer2player.fd, "\n", 1);
    
  }
  
  return 0;
  
}

int read_from_fifo(player_t *player, char *buffer) {

  int error;
  char *newline;
  fd_set fds;
  
  if (player->player2dealer.buffered) {
    if (player->player2dealer.fp == NULL) {
      // TODO: elegir RO o WR
      if (create_fifo(player->player2dealer.name) != 0) {
        return -1;
      }
      printf("waiting for player2dealer buffered fifo '%s'...", player->player2dealer.name);
      fflush(stdout);
      if ((player->player2dealer.fp = fopen(player->player2dealer.name, "r")) == NULL) {
        blackjack_push_error_message("reading buffered fifo '%s': %s", player->player2dealer.name, strerror(errno));
        return -1;
      }
      printf("ok!\n");
      fflush(stdout);
    }
    fgets(buffer, BUF_SIZE-1, player->player2dealer.fp);
        
  } else {
    if (player->player2dealer.fd == 0) {
      // TODO: elegir RO o WR
      if (create_fifo(player->player2dealer.name) != 0) {
        return -1;
      }
      printf("waiting for player2dealer unbuffered fifo '%s'...", player->player2dealer.name);
      fflush(stdout);
      if ((player->player2dealer.fd = open(player->player2dealer.name, O_RDONLY)) == -1) {
        blackjack_push_error_message("reading unbuffered fifo '%s': %s", player->player2dealer.name, strerror(errno));
        return -1;
      }
      printf("ok!\n");
      fflush(stdout);
    }

    // TODO: timeout
    FD_ZERO(&fds);
    FD_SET(player->player2dealer.fd, &fds);
    error = select(player->player2dealer.fd+1, &fds, NULL, NULL, NULL);
    if (error == -1) {
      blackjack_push_error_message("selecting unbuffered fifo '%s'", player->player2dealer.name);
    }
    read(player->player2dealer.fd, buffer, BUF_SIZE-1);
  }

  // strip \n
  newline = strchr(buffer, '\n');
  if (newline != NULL) {
    *newline = '\0';
  }
  return 0;  
  
}
