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
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include <fcntl.h>		/* For O_* constants */
#include <semaphore.h>

#ifndef _LIBREBLACKJACK_H_
#include "libreblackjack.h"
#endif

int
create_shmem (const char *name, char **pointer, sem_t ** sem_written,
	      sem_t ** sem_read)
{

  int fd;
  char *buff;

  // TODO: create a posix name (need to remember the posix name to free it)

  if ((fd = shm_open (name, O_RDWR | O_CREAT, 0666)) == -1)
    {
      blackjack_push_error_message (_
				    ("'%s' opening shared memory object '%s'"),
				    strerror (errno), name);
      return -1;
    }

  if (ftruncate (fd, BUF_SIZE - 1) != 0)
    {
      blackjack_push_error_message (_
				    ("'%s' truncating shared memory object '%s'"),
				    strerror (errno), name);
      return -1;
    }
  if ((*pointer =
       mmap (NULL, BUF_SIZE - 1, PROT_READ | PROT_WRITE, MAP_SHARED, fd,
	     0)) == MAP_FAILED)
    {
      blackjack_push_error_message (_
				    ("'%s' maping shared memory object '%s'"),
				    strerror (errno), name);
      return -1;
    }

  close (fd);

  // sempahores
  buff = malloc (strlen (name) + 16);
  sprintf (buff, "%s_written", name);
  if ((*sem_written = sem_open (buff, O_CREAT, 0666, 0)) == SEM_FAILED)
    {
      blackjack_push_error_message (_("'%s' opening semaphore '%s'"),
				    strerror (errno), name);
      return -1;
    }

  sprintf (buff, "%s_read", name);
  if ((*sem_read = sem_open (buff, O_CREAT, 0666, 0)) == SEM_FAILED)
    {
      blackjack_push_error_message (_("'%s' opening semaphore '%s'"),
				    strerror (errno), name);
      return -1;
    }
  free (buff);

  return 0;
}

int
dealer_to_shmem (player_t * player, const char *command)
{

  static int first = 1;

  if (first)
    {
      if (create_shmem
	  (player->dealer2player.name, &player->dealer2player.shmem,
	   &player->dealer2player.sem_written,
	   &player->dealer2player.sem_read))
	{
	  return -1;
	}
    }

  snprintf (player->dealer2player.shmem, BUF_SIZE - 1, "%s", command);
  sem_post (player->dealer2player.sem_written);

  if (first)
    {
      printf (_("waiting for dealer2player semaphore '%s_read'..."),
	      player->dealer2player.name);
      fflush (stdout);
    }

  sem_wait (player->dealer2player.sem_read);

  if (first)
    {
      printf (_("ok!\n"));
      first = 0;
    }

  return 0;
}


int
player_from_shmem (player_t * player, char *buffer)
{

  static int first = 1;

  if (first)
    {
      if (create_shmem
	  (player->player2dealer.name, &player->player2dealer.shmem,
	   &player->player2dealer.sem_written,
	   &player->player2dealer.sem_read))
	{
	  return -1;
	}
      printf (_("waiting for player2dealer semaphore '%s_written'..."),
	      player->player2dealer.name);
      fflush (stdout);
    }

  sem_wait (player->player2dealer.sem_written);

  if (first)
    {
      printf (_("ok!\n"));
      first = 0;
    }
  memcpy (buffer, player->player2dealer.shmem, BUF_SIZE - 1);
  sem_post (player->player2dealer.sem_read);

  return 0;
}
