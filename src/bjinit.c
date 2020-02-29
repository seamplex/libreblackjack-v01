/*------------ -------------- -------- --- ----- ---   --       -            -
 *  Libre Blackjack - initialization
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
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <errno.h>

#ifndef _LIBREBLACKJACK_H_
#include "libreblackjack.h"
#endif

#define CONF_TOKEN_SEPARATORS " \t"
#define MATCH(n) (strcmp(name, n) == 0)

char suitname[4][12] = { "spades", "hearts", "diamonds", "clubs" };
char suitletter[4][8] = { "S", "H", "D", "C" };
char suitcode[4][8] = { "♠", "♥", "♦", "♣" };
char numbername[14][4] =
  { "X", "A", "2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K" };
int cardvalue[14] = { 0, 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 };


void
bj_strip_blanks (char *string)
{
  int i = 0;
  int j = 0;
  char *buff = strdup (string);

  for (i = 0; i < strlen (string); i++)
    {
      if (!isspace ((int) buff[i]))
	{
	  string[j++] = buff[i];
	}
    }

  string[j] = '\0';
  free (buff);

  return;
}

// strip out the blanks of a string (inline)
void
bj_strip_blanks_leading_trailing (char *string)
{
  int i = 0;
  int j = 0;
  char *buff = strdup (string);

  while (isspace (buff[i]))
    {
      i++;
    }

  for (j = strlen (buff) - 1; j > i && isspace (buff[j]); j--)
    {
      buff[j] = '\0';
    }

  snprintf (string, j - i + 2, "%s", &buff[i]);
  free (buff);

  return;
}



int
fbj_conf_handler (const char *name, const char *value)
{

  player_t *player;
  char *tokens;
  char *token;

///va+decks+name decks
///va+decks+desc Number of decks in the shoe.
///va+decks+detail A value of -1 corresponds "infinite" which means
///va+decks+detail sample a random card instead of actually shuffling a
///va+decks+detail real shoe and drawing a card from it  
  if (MATCH ("decks"))
    {
      if (blackjack_conf.decks == 0)
	{
	  blackjack_conf.decks = atoi (value);
	}

    }
///va+hands+name hands
///va+hands+desc Number of hands to play.
///va+hands+detail After the prescribed number of hands have been played,
///va+hands+detail the execution ends. A scientific notation number can
///va+hands+detail be given to avoid issues with too many zeros.
///va+hands+detail So one million hands can be written either
///va+hands+detail as `1000000` or as `1e6`.
  else if (MATCH ("hands"))
    {
      // with atof we can use things like "1e6" instead of 1000000
      if (blackjack_conf.hands == 0)
	{
	  blackjack_conf.hands = (long int) (atof (value));
	}

    }
/*    
  else if (MATCH ("players"))
    {
      tokens = strdup (value);
      token = strtok (tokens, CONF_TOKEN_SEPARATORS);
      while (token != NULL)
	{
	  new_player (token);
	  token = strtok (NULL, CONF_TOKEN_SEPARATORS);
	}
      free (token);

    }
*/
///va+rng_seed+desc Random number generator seed.
///va+rng_seed+detail The seed used by the RNG in charge of shuffling the shoe
///va+rng_seed+detail (or sampling from an infinite deck if `decks`=-1).
///va+rng_seed+detail This can be used to have repeteability in the order
///va+rng_seed+detail of the dealt cards.
  else if (MATCH ("rng_seed"))
    {
      if (blackjack_conf.rng_seed == 0)
	{
	  blackjack_conf.rng_seed = atoi (value);
	}

    }
/*    
  else if (MATCH ("rng_type"))
    {
      // TODO
//        blackjack_conf.rng_type = gsl_rng_mt19937;
      ;
    }
*/
///va+burnt_cards+desc Number of burnt cards when starting a new shoe.
///va+burnt_cards+detail When a new shoe is started, this number of cards
///va+burnt_cards+detail are burned by the dealer.
///va+burnt_cards+detail Statistically this number does not have any effect,
///va+burnt_cards+detail it is provided for the sake of completeness.
///va+burnt_cards+default No cards are burned.
  else if (MATCH ("burnt_cards") || MATCH ("number_of_burnt_cards")
	   || MATCH ("burntcards"))
    {
      if (blackjack_conf.number_of_burnt_cards == -1)
	{
	  blackjack_conf.number_of_burnt_cards = atoi (value);
	}

    }
///va+penetration+desc Fraction of the shoe where the cut card is
///va+penetration+desc (randomnly) placed
///va+penetration+detail This variable controls the percentage of 
///va+penetration+detail the shoe which is used for playing before
///va+penetration+detail re-shuffling. The cut card is placed by the
///va+penetration+detail dealer with a gaussian random distribution 
///va+penetration+detail centered at this fraction $\in [0:1]$ and
///va+penetration+detail standard deviation contrlled by `penetration_sigma`.
///va+penetration+detail The hand in which the cut card appears is
///va+penetration+detail finished and a new show is started.
///va+penetration+detail If the value is zero, the sho is reshuffled after
///va+penetration+detail each hand.
  else if (MATCH ("penetration"))
    {
      if (blackjack_conf.penetration == 0)
	{
	  blackjack_conf.penetration = atof (value);
	}
      if (blackjack_conf.penetration == 0)
	{
	  blackjack_conf.penetration = 1e-6;
	}
      if (blackjack_conf.penetration < 0)
	{
	  blackjack_push_error_message (_
					("penetration has to be positive, not '%s'"),
					value);
	  return -1;
	}
      if (blackjack_conf.penetration > 1)
	{
	  blackjack_push_error_message (_
					("penetration has to be less than one, not '%s'"),
					value);
	  return -1;
	}

    }
///va+penetration_sigma+desc Standard deviation of the distribution of the
///va+penetration_sigma+desc fraction that controls the location of the cut card.
///va+penetration_sigma+detail This variable gives the standard deviation of the
///va+penetration_sigma+detail random distribution used to place the cut card in
///va+penetration_sigma+detail the shoe before re-shuffling. The cut card is placed
///va+penetration_sigma+detail by the dealer with a gaussian random distribution 
///va+penetration_sigma+detail centered at the fraction $\in [0:1]$ given by
///va+penetration_sigma+detail `penetration` and standard deviation given by this
///va+penetration_sigma+detail value.
  else if (MATCH ("penetration_sigma"))
    {
      if (blackjack_conf.penetration_sigma == 0)
	{
	  blackjack_conf.penetration_sigma = atof (value);
	}

    }
///va+blackjack_pays+desc Blackjack payout ratio
///va+blackjack_pays+detail Set how much a blackjack received by the player pays.
///va+blackjack_pays+detail It can be either a textual `3/2` or `6/5` or any
///va+blackjack_pays+detail floating-point number.
  else if (MATCH ("blackjack_pays") || MATCH ("bjpays"))
    {
      if (blackjack_conf.blackjack_pays == -1)
	{
	  if (strcmp (value, "3/2"))
	    {
	      blackjack_conf.blackjack_pays = 3.0 / 2.0;
	    }
	  else if (strcmp (value, "6/5"))
	    {
	      blackjack_conf.blackjack_pays = 6.0 / 5.0;
	    }
	  else
	    {
	      blackjack_conf.blackjack_pays = atof (value);
	    }
	}

      if (blackjack_conf.blackjack_pays <= 0)
	{
	  blackjack_push_error_message (_
					("blackjack_pays has to be positive, not '%s'"),
					value);
	  return -1;
	}

    }
/*    
  else if (MATCH ("no_negative_bankrolls") || MATCH ("bouncer"))
    {
      if (blackjack_conf.no_negative_bankroll == -1)
	{
	  blackjack_conf.no_negative_bankroll = atoi (value);
	}

    }
*/
///va+double_after_split+desc Double after split
///va+double_after_split+detail Set if the player is allowed to double after
///va+double_after_split+detail splitting. A value of zero means not allowed
///va+double_after_split+detail and a non-zero means allowed.
///va+double_after_split+detail This variable can also be shortened as `das`.
  else if (MATCH ("double_after_split") || MATCH ("das"))
    {
      if (blackjack_conf.double_after_split == -1)
	{
	  blackjack_conf.double_after_split = atoi (value);
	}

    }
///va+hit_soft_17+desc Hit soft seventeens
///va+hit_soft_17+detail Set if the dealer must hit on soft 17s or not.
///va+hit_soft_17+detail A value of zero means dealer must stand
///va+hit_soft_17+detail and a non-zero means dealer must hit.
///va+hit_soft_17+detail This variable can also be shortened as `h17`.
  else if (MATCH ("hit_soft_17") || MATCH ("h17"))
    {
      if (blackjack_conf.hit_soft_17 == -1)
	{
	  blackjack_conf.hit_soft_17 = atoi (value);
	}

    }
///va+max_bet+desc Maximum allowed bet
///va+max_bet+detail Integer that limits the player's bet with
///va+max_bet+detail respect to a minimum value of one.
///va+max_bet+detail A value of zero means no limit.
  else if (MATCH ("max_bet"))
    {
      if (blackjack_conf.max_bet == 0)
	{
	  blackjack_conf.max_bet = atoi (value);
	}

    }
  else if (MATCH ("max_incorrect_commands"))
    {
      if (blackjack_conf.max_invalid_commands == -1)
	{
	  blackjack_conf.max_invalid_commands = atoi (value);
	}

    }
  else if (MATCH ("error_standard_deviations"))
    {
      if (blackjack_conf.error_standard_deviations == -1)
	{
	  blackjack_conf.error_standard_deviations = atof (value);
	}

    }
  else if (MATCH ("log"))
    {
      if (blackjack_conf.log == NULL)
	{
	  if ((blackjack_conf.log = fopen (value, "w")) == NULL)
	    {
	      blackjack_push_error_message (_
					    ("cannot open log file '%s': %s\n"),
					    value, strerror (errno));
	      return -1;
	    }
	}

    }
  else if (MATCH ("yaml_report"))
    {
      if (blackjack_conf.yaml_report == NULL)
	{
	  if ((blackjack_conf.yaml_report = fopen (value, "w")) == NULL)
	    {
	      blackjack_push_error_message (_
					    ("cannot open YAML report file '%s': %s\n"),
					    value, strerror (errno));
	      return -1;
	    }
	}

    }
  else if (MATCH ("arranged_cards"))
    {
      if (blackjack_conf.arranged_cards == NULL)
	{
	  card_t *arranged_card;
	  tokens = strdup (value);
	  token = strtok (tokens, CONF_TOKEN_SEPARATORS);
	  while (token != NULL)
	    {
	      arranged_card = calloc (1, sizeof (card_t));
	      arranged_card->tag = atoi (token);
	      append_card (&blackjack_conf.arranged_cards, arranged_card);
	      token = strtok (NULL, CONF_TOKEN_SEPARATORS);
	    }
	  free (tokens);
	}

    }
  else if (MATCH ("shuffle_every_hand"))
    {
      if (blackjack_conf.shuffle_every_hand == -1)
	{
	  blackjack_conf.shuffle_every_hand = atoi (value);
	}

      // stdout      
    }
  else if (MATCH ("no_color"))
    {
      if (stdout_opts.no_color == 0)
	{
	  stdout_opts.no_color = atoi (value);
	}

    }
  else if (MATCH ("no_utf8"))
    {
      if (stdout_opts.no_utf8 == 0)
	{
	  stdout_opts.no_utf8 = atoi (value);
	}

    }
  else if (MATCH ("ascii_art"))
    {
      if (stdout_opts.ascii_art == 0)
	{
	  stdout_opts.ascii_art = atoi (value);
	}

      // player-based options
    }
  else if (strcmp (name, "flat_bet") == 0 || strcmp (name, "flatbet") == 0)
    {
      player = player_from_section (NULL);
      if (strcmp (value, "") == 0)
	{
	  player->flat_bet = 1;
	}
      else
	{
	  player->flat_bet = atoi (value);
	}

    }
  else if (strcmp (name, "no_insurance") == 0
	   || strcmp (name, "noinsurance") == 0)
    {
      player = player_from_section (NULL);
      if (strcmp (value, "") == 0)
	{
	  player->no_insurance = 1;
	}
      else
	{
	  player->no_insurance = atoi (value);
	}

    }
  else if (strcmp (name, "always_insure") == 0
	   || strcmp (name, "insure") == 0)
    {
      player = player_from_section (NULL);
      if (strcmp (value, "") == 0)
	{
	  player->always_insure = 1;
	}
      else
	{
	  player->always_insure = atoi (value);
	}

    }
  else if (strcmp (name, "bankroll") == 0)
    {
      player = player_from_section (NULL);
      player->bankroll = atof (value);
      player->worst_bankroll = player->bankroll;

    }
  else if (strcmp (name, "delay") == 0)
    {
      player = player_from_section (NULL);
      player->delay = atof (value);

    }
  else if (strcmp (name, "card_format") == 0)
    {
      player = player_from_section (NULL);
      if (strcmp (value, "utf8") == 0)
	{
	  player->token_type = card_utf8;
	}
      else if (strcmp (value, "utf8_single") == 0)
	{
	  player->token_type = card_utf8_single;
	}
      else if (strcmp (value, "ascii") == 0)
	{
	  player->token_type = card_ascii;
	}
      else if (strcmp (value, "value") == 0)
	{
	  player->token_type = card_value;
	}
      else if (strcmp (value, "tag") == 0)
	{
	  player->token_type = card_tag;
	}

    }
  else if (strcmp (name, "buffered_fifos") == 0
	   || strcmp (name, "buffered_fifo") == 0
	   || strcmp (name, "bufferedfifo") == 0)
    {
      player = player_from_section (NULL);
      player->dealer2player.buffered = atoi (value);
      player->player2dealer.buffered = atoi (value);

    }
  else if (strcmp (name, "player2dealer") == 0
	   || strcmp (name, "dealer2player") == 0)
    {
      ipc_t *ipc;
      player = player_from_section (NULL);

      if (strcmp (name, "player2dealer") == 0)
	{
	  ipc = &(player->player2dealer);
	}
      else if (strcmp (name, "dealer2player") == 0)
	{
	  ipc = &(player->dealer2player);
	}

      tokens = strdup (value);
      token = strtok (tokens, CONF_TOKEN_SEPARATORS);

      if (strcmp (token, "fifo") == 0)
	{
	  ipc->ipc_type = ipc_fifo;
	}
      else if (strcmp (token, "shmem") == 0)
	{
	  ipc->ipc_type = ipc_shmem;
	}
      else if (strcmp (token, "mq") == 0 || strcmp (token, "mqueue") == 0)
	{
	  ipc->ipc_type = ipc_mqueue;
	}
      else if (strcmp (token, "internal") == 0)
	{
	  ipc->ipc_type = ipc_internal;
	  player->flat_bet = 1;
	  player->no_insurance = 1;
	}
      else
	{
	  blackjack_push_error_message (_("unkown ipc type '%s'"), token);
	  return -1;
	}

      if (ipc->ipc_type == ipc_internal)
	{
	  // at least one internal means the other one is also internal
	  player->player2dealer.ipc_type = ipc_internal;
	  player->dealer2player.ipc_type = ipc_internal;
	}
      else
	{
	  // otherwise we need an object name
	  if ((token = strtok (NULL, CONF_TOKEN_SEPARATORS)) == NULL)
	    {
	      blackjack_push_error_message (_
					    ("expected object name after ipc type"));
	      return -1;
	    }
	  ipc->name = strdup (token);
	}


      free (tokens);

    }
  else
    {
      blackjack_push_error_message (_("unknown keyword '%s'"), name);
      return -1;		/* unknown section/name, error */
    }
  return 0;
}

int
bjinit (char *cmdline_file_path)
{

  char buffer[BUF_SIZE];
  char *keyword;
  char *equal;
  char *value;
  char *comment_colon;
  char *comment_hash;
  char *conf_file_path;
  FILE *conf_file;
  FILE *devrandom;
  int suit, rank, tag;
  int line = 0;
  player_t *player;

  // stuff that can be zero start in minus one
  blackjack_conf.no_negative_bankroll = -1;
  blackjack_conf.max_bet = -1;
  blackjack_conf.double_after_split = -1;
  blackjack_conf.hit_soft_17 = -1;
  blackjack_conf.max_invalid_commands = -1;
  blackjack_conf.shuffle_every_hand = -1;

  // read the conf
  conf_file_path =
    strdup ((cmdline_file_path == NULL) ? CONF_FILE_PATH : cmdline_file_path);
  if ((conf_file = fopen (conf_file_path, "r")) != NULL)
    {
      while (fgets (buffer, BUF_SIZE - 1, conf_file))
	{

	  line++;
	  keyword = NULL;
	  value = NULL;

	  comment_colon = strchr (buffer, ';');
	  comment_hash = strchr (buffer, '#');
	  if (comment_colon != NULL)
	    {
	      *comment_colon = '\0';
	    }
	  if (comment_hash != NULL)
	    {
	      *comment_hash = '\0';
	    }
	  if ((equal = strchr (buffer, '=')) != NULL)
	    {
	      value = equal + 1;
	      *equal = '\0';
	      keyword = buffer;
	    }

	  if (keyword != NULL && value != NULL)
	    {
	      bj_strip_blanks_leading_trailing (keyword);
	      bj_strip_blanks_leading_trailing (value);
	      if (fbj_conf_handler (keyword, value) != 0)
		{
		  blackjack_push_error_message ("%s:%d: ", conf_file_path,
						line);
		  return -1;
		}
	    }
	}

    }
  else if (cmdline_file_path != NULL)
    {
      blackjack_push_error_message (_("cannot open ini file '%s': %s\n"),
				    cmdline_file_path, strerror (errno));
      return -1;
    }
  free (conf_file_path);

  // non-zero defaults
  if (blackjack_conf.decks == 0)
    {
///va+decks+default 6 
      blackjack_conf.decks = 6;
    }
  if (blackjack_conf.hands == 0)
    {
///va+hands+default One million
      blackjack_conf.hands = 1e6;
    }
  if (blackjack_conf.no_negative_bankroll == -1)
    {
      blackjack_conf.no_negative_bankroll = 0;
    }
  if (blackjack_conf.max_bet == -1)
    {
///va+max_bet+default No limit     
      blackjack_conf.max_bet = 0;
    }
  if (blackjack_conf.double_after_split == -1)
    {
///va+double_after_split+default Allowed
      blackjack_conf.double_after_split = 1;
    }
  if (blackjack_conf.hit_soft_17 == -1)
    {
///va+hit_soft_17+default Dealer must hit soft 17s.
      blackjack_conf.hit_soft_17 = 1;
    }
  if (blackjack_conf.blackjack_pays == 0)
    {
///va+blackjack_pays+default `3/2`
      blackjack_conf.blackjack_pays = 3.0 / 2.0;
    }
  if (blackjack_conf.error_standard_deviations == 0)
    {
      blackjack_conf.error_standard_deviations = 2.0;
    }
  if (blackjack_conf.max_invalid_commands == -1)
    {
      blackjack_conf.max_invalid_commands = 100;
    }
  if (blackjack_conf.shuffle_every_hand == -1)
    {
      blackjack_conf.shuffle_every_hand = 0;
    }

//  blackjack_confrng_type = gsl_rng_mt19937;
  if (blackjack_conf.penetration == 0)
    {
///va+penetration+default 0.75
      blackjack_conf.penetration = 0.75;
    }
  if (blackjack_conf.penetration_sigma == 0)
    {
///va+penetration_sigma+default 0.05
      blackjack_conf.penetration_sigma = 0.05;
    }

  // create a player
  if ((blackjack.current_player = blackjack.players) == NULL)
    {
      blackjack.current_player = new_player ("player");
    }

  // the delay is only for tty-stdout
  if (blackjack.current_player->delay == 0)
    {
      blackjack.current_player->delay = 0.4;
    }

  if (blackjack_conf.rng_seed == 0)
    {
///va+rng_seed+default Get seed from `/dev/urandom`. 
      assert ((devrandom = fopen ("/dev/urandom", "r")));
      assert (fread
	      (&blackjack_conf.rng_seed, sizeof (blackjack_conf.rng_seed), 1,
	       devrandom));
      fclose (devrandom);
    }

  if (blackjack.players->dealer2player.ipc_type == ipc_none)
    {
      stdout_opts.isatty = isatty (1);
    }


  if (stdout_opts.isatty && stdout_opts.no_color == 0)
    {
      strncpy (stdout_opts.black,   "\x1B[0m", 8);
      strncpy (stdout_opts.red,     "\x1B[31m", 8);
      strncpy (stdout_opts.green,   "\x1B[32m", 8);
      strncpy (stdout_opts.yellow,  "\x1B[33m", 8);
      strncpy (stdout_opts.blue,    "\x1B[34m", 8);
      strncpy (stdout_opts.magenta, "\x1B[35m", 8);
      strncpy (stdout_opts.cyan,    "\x1B[36m", 8);
      strncpy (stdout_opts.white,   "\x1B[37m", 8);
      strncpy (stdout_opts.reset,   "\033[0m", 8);
    }


  // initialize cards
  for (suit = 0; suit < 4; suit++)
    {
      for (rank = 1; rank <= 13; rank++)
	{

	  tag = 13 * suit + rank;
	  blackjack.card[tag].tag = tag;
	  blackjack.card[tag].value = cardvalue[rank];

	  if (stdout_opts.isatty)
	    {
	      snprintf (blackjack.card[tag].text, 32, "%s%s%s%s",
			(suit == 1
			 || suit == 2) ? stdout_opts.red : stdout_opts.black,
			numbername[rank], suitcode[suit], stdout_opts.reset);
	    }
	  else
	    {
	      snprintf (blackjack.card[tag].text, 32, "%s%s",
			numbername[rank], suitletter[suit]);
	    }

	  snprintf (blackjack.card[tag].token[card_tag], CARD_SIZE, "%d",
		    tag);
	  snprintf (blackjack.card[tag].token[card_ascii], CARD_SIZE, "%s%s",
		    numbername[rank], suitletter[suit]);
	  snprintf (blackjack.card[tag].token[card_utf8], CARD_SIZE, "%s%s",
		    numbername[rank], suitcode[suit]);
	  snprintf (blackjack.card[tag].token[card_value], CARD_SIZE, "%d",
		    cardvalue[rank]);

	  snprintf (blackjack.card[tag].art[0], CARD_SIZE, " _____ ");
	  snprintf (blackjack.card[tag].art[1], CARD_SIZE, "|%s    |",
		    numbername[rank]);
	  snprintf (blackjack.card[tag].art[2], CARD_SIZE, "|     |");
	  snprintf (blackjack.card[tag].art[3], CARD_SIZE, "|  %s  |",
		    suitcode[suit]);
	  snprintf (blackjack.card[tag].art[4], CARD_SIZE, "|     |");
	  snprintf (blackjack.card[tag].art[5], CARD_SIZE, "|____%s|",
		    numbername[rank]);
	}
    }


  // https://en.wikipedia.org/wiki/Playing_cards_in_Unicode
  // yes, I could loop and compute the code for each card and
  // it would be hacky but hard to understand for humans
  // UNIX rule of representation!
  snprintf (blackjack.card[1].token[card_utf8_single], 8, "🂡");
  snprintf (blackjack.card[2].token[card_utf8_single], 8, "🂢");
  snprintf (blackjack.card[3].token[card_utf8_single], 8, "🂣");
  snprintf (blackjack.card[4].token[card_utf8_single], 8, "🂤");
  snprintf (blackjack.card[5].token[card_utf8_single], 8, "🂥");
  snprintf (blackjack.card[6].token[card_utf8_single], 8, "🂦");
  snprintf (blackjack.card[7].token[card_utf8_single], 8, "🂧");
  snprintf (blackjack.card[8].token[card_utf8_single], 8, "🂨");
  snprintf (blackjack.card[9].token[card_utf8_single], 8, "🂩");
  snprintf (blackjack.card[10].token[card_utf8_single], 8, "🂪");
  snprintf (blackjack.card[11].token[card_utf8_single], 8, "🂫");
  snprintf (blackjack.card[12].token[card_utf8_single], 8, "🂭");
  snprintf (blackjack.card[13].token[card_utf8_single], 8, "🂮");

  snprintf (blackjack.card[14].token[card_utf8_single], 8, "🂱");
  snprintf (blackjack.card[15].token[card_utf8_single], 8, "🂲");
  snprintf (blackjack.card[16].token[card_utf8_single], 8, "🂳");
  snprintf (blackjack.card[17].token[card_utf8_single], 8, "🂴");
  snprintf (blackjack.card[18].token[card_utf8_single], 8, "🂵");
  snprintf (blackjack.card[19].token[card_utf8_single], 8, "🂶");
  snprintf (blackjack.card[20].token[card_utf8_single], 8, "🂷");
  snprintf (blackjack.card[21].token[card_utf8_single], 8, "🂸");
  snprintf (blackjack.card[22].token[card_utf8_single], 8, "🂹");
  snprintf (blackjack.card[23].token[card_utf8_single], 8, "🂺");
  snprintf (blackjack.card[24].token[card_utf8_single], 8, "🂻");
  snprintf (blackjack.card[25].token[card_utf8_single], 8, "🂽");
  snprintf (blackjack.card[26].token[card_utf8_single], 8, "🂾");

  snprintf (blackjack.card[27].token[card_utf8_single], 8, "🃁");
  snprintf (blackjack.card[28].token[card_utf8_single], 8, "🃂");
  snprintf (blackjack.card[29].token[card_utf8_single], 8, "🃃");
  snprintf (blackjack.card[30].token[card_utf8_single], 8, "🃄");
  snprintf (blackjack.card[31].token[card_utf8_single], 8, "🃅");
  snprintf (blackjack.card[32].token[card_utf8_single], 8, "🃆");
  snprintf (blackjack.card[33].token[card_utf8_single], 8, "🃇");
  snprintf (blackjack.card[34].token[card_utf8_single], 8, "🃈");
  snprintf (blackjack.card[35].token[card_utf8_single], 8, "🃉");
  snprintf (blackjack.card[36].token[card_utf8_single], 8, "🃊");
  snprintf (blackjack.card[37].token[card_utf8_single], 8, "🃋");
  snprintf (blackjack.card[38].token[card_utf8_single], 8, "🃍");
  snprintf (blackjack.card[39].token[card_utf8_single], 8, "🃍");

  snprintf (blackjack.card[40].token[card_utf8_single], 8, "🃑");
  snprintf (blackjack.card[41].token[card_utf8_single], 8, "🃒");
  snprintf (blackjack.card[42].token[card_utf8_single], 8, "🃓");
  snprintf (blackjack.card[43].token[card_utf8_single], 8, "🃔");
  snprintf (blackjack.card[44].token[card_utf8_single], 8, "🃕");
  snprintf (blackjack.card[45].token[card_utf8_single], 8, "🃖");
  snprintf (blackjack.card[46].token[card_utf8_single], 8, "🃗");
  snprintf (blackjack.card[47].token[card_utf8_single], 8, "🃘");
  snprintf (blackjack.card[48].token[card_utf8_single], 8, "🃙");
  snprintf (blackjack.card[49].token[card_utf8_single], 8, "🃚");
  snprintf (blackjack.card[50].token[card_utf8_single], 8, "🃛");
  snprintf (blackjack.card[51].token[card_utf8_single], 8, "🃝");
  snprintf (blackjack.card[52].token[card_utf8_single], 8, "🃞");


  // function pointers
  for (player = blackjack.players; player != NULL; player = player->next)
    {

      switch (player->dealer2player.ipc_type)
	{
	case ipc_none:
	  player->write = dealer_to_stdout;
	  break;
	case ipc_fifo:
	  player->write = dealer_to_fifo;
	  break;
	case ipc_shmem:
	  player->write = dealer_to_shmem;
	  break;
	case ipc_mqueue:
	  player->write = dealer_to_mqueue;
	  break;
	case ipc_internal:
	  player->write = dealer_to_internal;
	  break;
	}
      switch (player->player2dealer.ipc_type)
	{
	case ipc_none:
	  player->read = player_from_stdin;
	  break;
	case ipc_fifo:
	  player->read = player_from_fifo;
	  break;
	case ipc_shmem:
	  player->read = player_from_shmem;
	  break;
	case ipc_mqueue:
	  player->read = player_from_mqueue;
	  break;
	case ipc_internal:
	  player->read = player_from_internal;
	  break;
	}
    }

  return 0;
}
