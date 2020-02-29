/*------------ -------------- -------- --- ----- ---   --       -            -
 *  Libre Blackjack - error handlers
 *
 *  Copyright (C) 2016--2020 jeremy theler
 *
 *  This file is part of Libre Blackjack.
 *
 *  Libre Blackjack is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Libre Blackjack is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Libre Blackjack.  If not, see <http://www.gnu.org/licenses/>.
 *------------------- ------------  ----    --------  --     -       -         -
 */
#include <assert.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/types.h>

#ifndef _LIBREBLACKJACK_H_
#include "libreblackjack.h"
#endif

void
blackjack_push_error_message (const char *fmt, ...)
{

  va_list ap;

  assert (blackjack.error_level < 100);

  blackjack.error =
    realloc (blackjack.error, (++blackjack.error_level) * sizeof (char *));
  blackjack.error[blackjack.error_level - 1] = malloc (BUF_SIZE);

  va_start (ap, fmt);
  vsnprintf (blackjack.error[blackjack.error_level - 1], BUF_SIZE, fmt, ap);
  va_end (ap);
  // TODO: realloc if run out of space

  return;
}

void
blackjack_pop_error_message (void)
{

  if (blackjack.error_level > 0)
    {
      free (blackjack.error[blackjack.error_level - 1]);
      blackjack.error_level--;
    }

  return;
}


void
blackjack_pop_errors (void)
{

  fprintf (stderr, "error: ");
  if (blackjack.error_level == 0)
    {
      fprintf (stderr, _("unspecified error\n"));
    }
  else
    {
      while (blackjack.error_level > 0)
	{
	  fprintf (stderr, "%s%s", blackjack.error[blackjack.error_level - 1],
		   (blackjack.error_level != 1) ? " " : "\n");
	  blackjack_pop_error_message ();
	}
    }

  return;
}


void
blackjack_signal_handler (int sig_num)
{

  fprintf (stderr, _("\npid %d: signal #%d caught, finnishing... "),
	   getpid (), sig_num);
  fflush (stderr);

  blackjack.done = 1;

/*
  if (blackjack.fork_sem != NULL) {
    blackjack_free_semaphore(blackjack.fork_sem, blackjack.fork_sem_name);
  }
*/

  fprintf (stderr, "ok\n");
  exit (1);

}
