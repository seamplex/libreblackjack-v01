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
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/time.h>

#ifndef _LIBREBLACKJACK_H_
#include "libreblackjack.h"
#endif


int
main (int argc, char **argv)
{

  int i, optc;
  int option_index = 0;
  int show_help = 0;
  int show_version = 0;
  int show_bar = 0;
  int bar_already_alloced = 0;
  int hands_per_char = 0;
  unsigned long int last_hand_per_char = 0;
  int current_invalid_command = 0;
  char *argument_for_conf;
  char *equal_sign;


  player_t *player;
  player_t *tmp;		// for the cleanup

  const struct option longopts[] = {
    {"help", no_argument, NULL, 'h'},
    {"version", no_argument, NULL, 'v'},
    {"decks", required_argument, NULL, 'd'},
    {"hands", required_argument, NULL, 'n'},
    {"internal", no_argument, NULL, 'i'},
    {"flatbet", optional_argument, NULL, 'f'},
    {NULL, 0, NULL, 0}
  };

  setlocale (LC_ALL, "");
  bindtextdomain (PACKAGE, "/usr/share/locale/");
  textdomain (PACKAGE);

  opterr = 0;
  while ((optc =
	  getopt_long_only (argc, argv, "hvd:n:if:", longopts,
			    &option_index)) != -1)
    {
      switch (optc)
	{
	case 'h':
	  show_help = 1;
	  break;
	case 'v':
	  show_version = 1;
	  break;
	case 'd':
	  bjcallpop (fbj_conf_handler ("decks", optarg));
	  break;
	case 'n':
	  bjcallpop (fbj_conf_handler ("hands", optarg));
	  break;
	case 'i':
	  bjcallpop (fbj_conf_handler ("player2dealer", "internal"));
	  bjcallpop (fbj_conf_handler ("dealer2player", "internal"));
	  bjcallpop (fbj_conf_handler ("flat_bet", "1"));
	  bjcallpop (fbj_conf_handler ("no_insurance", "1"));
	  break;
	case 'f':
	  if (optarg != NULL)
	    {
	      bjcallpop (fbj_conf_handler ("flat_bet", optarg));
	    }
	  else
	    {
	      bjcallpop (fbj_conf_handler ("flat_bet", "1"));
	    }
	  break;
	case '?':
	  argument_for_conf = strdup (argv[optind - 1]);
	  if ((equal_sign = strchr (argument_for_conf, '=')) == NULL)
	    {
	      if (fbj_conf_handler (argument_for_conf + 2, "") != 0)
		{
		  fprintf (stderr, _("Unkown option '%s'.\n"),
			   argument_for_conf);
		  fprintf (stderr,
			   _("Try '%s --help' for more information.\n)"),
			   argv[0]);
		  return 1;
		}
	    }
	  else
	    {
	      *equal_sign = '\0';
	      if (fbj_conf_handler (argument_for_conf + 2, equal_sign + 1) <=
		  0)
		{
		  fprintf (stderr, _("Unkown option '%s'.\n"),
			   argument_for_conf);
		  fprintf (stderr,
			   _("Try '%s --help' for more information.\n"),
			   argv[0]);
		  return 1;
		}
	    }
	  free (argument_for_conf);
	  break;
	default:
	  break;
	}
    }

  if (show_version)
    {
      libreblackjack_shortversion ();
      libreblackjack_copyright ();
    }
  if (show_help)
    {
      libreblackjack_help (argv[0]);
    }

  if (show_version || show_help)
    {
      return 0;
    }

  // measure wall time, ask fot the initial time
  gettimeofday (&blackjack.wall_time_initial, NULL);

  // if we still have arguments, it is the path to the conf file
  if (optind == argc)
    {
      if (bjinit (NULL) != 0)
	{
	  blackjack_pop_errors ();
	  return 1;
	}
    }
  else
    {
      if (bjinit (argv[optind]) != 0)
	{
	  blackjack_pop_errors ();
	  return 1;
	}
    }

  if (stdout_opts.isatty)
    {
      libreblackjack_shortversion ();
      libreblackjack_copyright ();
    }

  blackjack.next_dealer_action = START_NEW_HAND;
  blackjack.last_pass = 1;

  // TODO: check and/or choose in the conf
//  setvbuf(stdout, NULL, _IONBF, 0);
  setlinebuf (stdout);

  // TODO: check, add options --quiet and --verbose
  if (blackjack.players->dealer2player.ipc_type != ipc_none)
    {
      if (blackjack_conf.hands != 0)
	{
	  show_bar = 1;
	  hands_per_char = blackjack_conf.hands / 50;
	}
    }

  while (!blackjack.done)
    {

      // assume no feedback from the player is needed
      // if none is needed, in dealer_action we set next_action
      // if feedback is needed, in process_player_input we set next_action
      // this way we can check that the feedback we get is valid
      blackjack.players_input_needed = NONE;

      // clean the output buffer (this is used to re-ask when the input is invalid)
      outputbuffer[0] = '\0';
      current_invalid_command = 0;

      if (dealer_action () != 0)
	{
	  blackjack_pop_errors ();
	  return 1;
	}

      if (show_bar != 0)
	{
	  if (blackjack.hand == 2 && bar_already_alloced == 0)
	    {
	      printf ("\n");
	      for (i = 0; i < 50; i++)
		{
		  printf ("-");
		}
	      for (i = 0; i < 50; i++)
		{
		  printf ("\b");
		}
	      bar_already_alloced = 1;
	      fflush (stdout);
	    }
	  if ((blackjack.hand - last_hand_per_char) > hands_per_char)
	    {
	      printf ("=");
	      fflush (stdout);
	      last_hand_per_char = blackjack.hand;
	    }
	}

      if (blackjack.players_input_needed != NONE)
	{
	  do
	    {

	      if (outputbuffer[0] != '\0')
		{
		  if (blackjack.current_player->
		      write (blackjack.current_player, outputbuffer) != 0)
		    {
		      blackjack_pop_errors ();
		      return 1;
		    }

		  if (blackjack_conf.log != NULL)
		    {
		      fprintf (blackjack_conf.log, "-> %s\n", outputbuffer);
		      fflush (blackjack_conf.log);
		    }
		}

	      if (blackjack.current_player->
		  read (blackjack.current_player, inputbuffer) != 0)
		{
		  blackjack_pop_errors ();
		  return 1;
		}
	      if (blackjack_conf.log != NULL)
		{
		  fprintf (blackjack_conf.log, "<- %s\n", inputbuffer);
		  fflush (blackjack_conf.log);
		}

	      if (blackjack_conf.max_invalid_commands != 0
		  && current_invalid_command++ >
		  blackjack_conf.max_invalid_commands)
		{
		  blackjack.current_player->write (blackjack.current_player,
						   "max_incorrect_commands");
		  blackjack_push_error_message (_
						("reached the maximum number of allowed incorrect commands (%d)"),
						blackjack_conf.
						max_invalid_commands);
		  blackjack_pop_errors ();
		  blackjack.current_player->write (blackjack.current_player,
						   "bye");
		  exit (1);
		}
	    }
	  while (dealer_process_input (blackjack.current_player, inputbuffer)
		 <= 0);
	}
    }

  if (show_bar)
    {
      printf ("=\n\n");
    }

  // cleanup
  for ((player) = (blackjack.players); (player) && (tmp = (player)->next, 1);
       (player) = tmp)
    {
      blackjack.current_player->write (player, "bye");
      write_yaml_report (blackjack.players);
      destroy_player (player);
    }
  destroy_hands (&blackjack.dealer_hand);
  free_rl_stdin ();
  free (blackjack.shoe);
  if (blackjack_conf.log != NULL)
    {
      fclose (blackjack_conf.log);
    }
#ifdef HAVE_LIBGSL
  gsl_rng_free (blackjack.rng);
#endif



  return (EXIT_SUCCESS);
}
