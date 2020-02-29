/*------------ -------------- -------- --- ----- ---   --       -            -
 *  Libre Blackjack - handling of cards
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
#include <wchar.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>

#ifndef _LIBREBLACKJACK_H_
#include "libreblackjack.h"
#endif

void
print_card_art (card_t * card)
{
  int i;
  for (i = 0; i < CARD_ART_LINES; i++)
    {
      printf ("%s\n", card->art[i]);
    }
  printf ("\n");
  return;
}

void
print_hand_art (hand_t * hand)
{
  int i;
  card_t *card;
  for (i = 0; i < CARD_ART_LINES; i++)
    {
      for (card = hand->cards; card != NULL; card = card->next)
	{
	  printf ("%s%c", card->art[i], (card->next != NULL) ? ' ' : '\n');
	}
    }
  printf ("\n");
  return;
}

/*
void print_card_text(card_t *card) {
  printf("%s of %s ", card->numbername, card->suitname);
  return;
}
*/

void
print_card_unicode (card_t * card)
{
  printf ("%s", card->text);
  return;
}


int
compute_count (hand_t * hand)
{

  card_t *card;

  hand->n_cards = 0;
  hand->soft = 0;
  hand->count = 0;
  for (card = hand->cards; card != NULL; card = card->next)
    {
      hand->count += card->value;
      hand->n_cards++;
      hand->soft += (card->value == 11);
      if (hand->count > 21 && hand->soft > 0)
	{
	  hand->count -= 10;
	  hand->soft--;
	}
    }

  if (hand->count == 21 && hand->n_cards == 2)
    {
      hand->blackjack = 1;
    }
  else if (hand->count > 21)
    {
      hand->busted = 1;
    }

  return hand->count;
}

int
deal_card (void)
{
  int dealt_tag = 0;

  if (blackjack_conf.decks == -1)
    {

      // if using infinite decks we take a random suit and rank and that's it
      if (blackjack.rng == NULL)
	{
	  card_t *card;
	  int i;

	  blackjack.n_arranged_cards = 0;
	  for (card = blackjack_conf.arranged_cards; card != NULL;
	       card = card->next)
	    {
	      blackjack.n_arranged_cards++;
	    }
	  if (blackjack.n_arranged_cards != 0)
	    {
	      blackjack.arranged_cards_array =
		calloc (blackjack.n_arranged_cards, sizeof (int));

	      i = 0;
	      for (card = blackjack_conf.arranged_cards; card != NULL;
		   card = card->next)
		{
		  blackjack.arranged_cards_array[i++] = card->tag;
		}
	    }

#ifdef HAVE_LIBGSL
	  blackjack.rng = gsl_rng_alloc (gsl_rng_mt19937);
	  gsl_rng_set (blackjack.rng, blackjack_conf.rng_seed);
#else
	  srandom (blackjack_conf.rng_seed);
#endif
	}

      if (blackjack.infinite_decks_card_number_for_arranged_ones <
	  blackjack.n_arranged_cards)
	{
	  dealt_tag =
	    blackjack.arranged_cards_array[blackjack.
					   infinite_decks_card_number_for_arranged_ones];
	}
      else
	{
#ifdef HAVE_LIBGSL
	  dealt_tag = 1 + gsl_rng_uniform_int (blackjack.rng, 52);
#else
	  dealt_tag = 1 + 52 * random () / RAND_MAX;
#endif
	}
      blackjack.infinite_decks_card_number_for_arranged_ones++;

    }
  else
    {

      if (blackjack.current_card_index >= 52 * blackjack_conf.decks)
	{
	  return 0;
	}
      blackjack.last_pass =
	(blackjack.current_card_index >= blackjack.cut_card_index)
	|| blackjack_conf.shuffle_every_hand;

      dealt_tag = blackjack.shoe[blackjack.current_card_index++];
    }

  return dealt_tag;
}

card_t *
deal_card_to_hand (hand_t * hand)
{
  int dealt_tag;
  card_t *card;

  if ((dealt_tag = deal_card ()) == 0)
    {
      shuffle_shoe ();
      dealt_tag = deal_card ();
    }

  card = calloc (1, sizeof (card_t));
  assert (card != NULL);
  memcpy (card, &blackjack.card[dealt_tag], sizeof (card_t));
  append_card (&hand->cards, card);

  compute_count (hand);

  return card;
}


void
destroy_hands (hand_t ** hands)
{
  hand_t *hand, *tmp;
  card_t *card, *tmp2;

  for (hand = *hands; hand != NULL && (tmp = hand->next) != NULL; hand = tmp)
    {
      for (card = hand->cards; card != NULL && (tmp2 = card->next) != NULL;
	   card = tmp2)
	{
	  delete_card (&hand->cards, card);
	  free (card);
	  card = NULL;
	}
      delete_hand (hands, hand);
      free (hand);
      hand = NULL;
    }
  *hands = NULL;
  return;
}

void
init_shoe (void)
{

  int i;
  int deck;
  int tag;			// an integer between 1 and 52 inclusive

  if (blackjack.shoe == NULL)
    {
      blackjack.shoe = malloc (blackjack_conf.decks * 52 * sizeof (int));
#ifdef HAVE_LIBGSL
      // TODO: choose
      blackjack.rng = gsl_rng_alloc (gsl_rng_mt19937);
      // initialize the RNG only at the beginning then we start
      // start asking for numbers, otherwise we get always the same shoes
      gsl_rng_set (blackjack.rng, blackjack_conf.rng_seed);
#else
      srandom (blackjack_conf.rng_seed);
#endif

    }

  // init the shoe: there can be many decks
  // each deck has 4 suits { 0 = "spades", 1 = "hearts", 2 = "diamonds", 3 = "clubs" }
  // each suit has 13 ranks 1--13
  // the "tag" is 13*suit+rank
  i = 0;
  for (deck = 0; deck < blackjack_conf.decks; deck++)
    {
      for (tag = 1; tag <= 52; tag++)
	{
	  blackjack.shoe[i++] = tag;
	}
    }

  blackjack.current_card_index = 0;

  return;
}


void
shuffle_shoe (void)
{

  int i, j, k;
  card_t *card;

  // if we have decks = 0 (infinite) then it is not needed to shuffle
  // just picka random card each time
  if (blackjack_conf.decks != -1)
    {
      // do we have to initalize the shoe?
      if (blackjack.shoe == NULL)
	{
	  init_shoe ();
	}

      // shuffle
      for (i = 52 * (blackjack_conf.decks) - 1; i > 0; i--)
	{
#ifdef HAVE_LIBGSL
	  j = gsl_rng_uniform_int (blackjack.rng, i);
#else
	  j = i * random () / RAND_MAX;
#endif

	  // this reminds me of the Sinclair CZ1000 manual I read in 1991 when I was 8
	  k = blackjack.shoe[i];
	  blackjack.shoe[i] = blackjack.shoe[j];
	  blackjack.shoe[j] = k;
	}

      // put the cut card according to the penetration with a gaussian distribution
      // (I wanted to do this since 2004 when I was in college)
#ifdef HAVE_LIBGSL
      blackjack.cut_card_index =
	52 * (blackjack_conf.decks) * (blackjack_conf.penetration +
				       gsl_ran_gaussian (blackjack.rng,
							 blackjack_conf.
							 penetration_sigma));
#else
      blackjack.cut_card_index =
	52 * (blackjack_conf.decks) * (blackjack_conf.penetration);
#endif

      // start in the first card (the dealer burns the card)
      blackjack.current_card_index = 0;

      // first the ones that are fixed/set-up
      j = 0;
      for (card = blackjack_conf.arranged_cards; card != NULL;
	   card = card->next)
	{
	  for (i = 52 * (blackjack_conf.decks) - 1; i > 0; i--)
	    {
	      if (blackjack.shoe[i] == card->tag)
		{
		  blackjack.shoe[i] = blackjack.shoe[j];
		  blackjack.shoe[j] = card->tag;
		  break;
		}
	    }
	  j++;
	}

      // count how many shuffles there are (out of curiosity)
      blackjack.shuffles++;
    }

  return;
}
