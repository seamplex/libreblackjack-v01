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
#include <wchar.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include "libreblackjack.h"

void print_card_art(card_t *card) {
  int i;
  for (i = 0; i < CARD_ART_LINES; i++) {
    printf("%s\n", card->art[i]);
  }
  printf("\n");
  return;
}

void print_hand_art(hand_t *hand) {
  int i;
  card_t *card;
  for (i = 0; i < CARD_ART_LINES; i++) {
    for (card = hand->cards; card != NULL; card = card->next) {
      printf("%s%c", card->art[i], (card->next != NULL) ? ' ' : '\n');
    }
  }
  printf("\n");
  return;
}

/*
void print_card_text(card_t *card) {
  printf("%s of %s ", card->numbername, card->suitname);
  return;
}
*/

void print_card_unicode(card_t *card) {
  printf("%s", card->text);
  return;
}


int compute_count(hand_t *hand) {

  card_t *card;

  hand->n_cards = 0;
  hand->soft = 0; 
  hand->count = 0;
  for (card = hand->cards; card != NULL; card = card->next) {
    hand->count += card->value;
    hand->n_cards++;
    hand->soft += (card->value == 11);
    if (hand->count > 21 && hand->soft > 0) {
      hand->count -= 10;
      hand->soft--;
    }
  }
  
  if (hand->count == 21 && hand->n_cards == 2) {
    hand->blackjack = 1;
  } else if (hand->count > 21) {
    hand->busted = 1;
  }
  
  return hand->count;
}

int deal_card(void) {
  int dealt_tag = 0;
  
  if (blackjack_ini.decks == -1) {
    
    // if using infinite decks we take a random suit and rank and that's it
    if (blackjack.rng == NULL) {
      card_t *card;
      int i;
      
      blackjack.n_arranged_cards = 0;
      for (card = blackjack_ini.arranged_cards; card != NULL; card = card->next) {
        blackjack.n_arranged_cards++;
      }
      if (blackjack.n_arranged_cards != 0) {
        blackjack.arranged_cards_array = calloc(blackjack.n_arranged_cards, sizeof(int));
      
        i = 0;
        for (card = blackjack_ini.arranged_cards; card != NULL; card = card->next) {
          blackjack.arranged_cards_array[i++] = card->tag;
        }
      }
      
#ifdef HAVE_LIBGSL
      // TODO: choose
      blackjack.rng = gsl_rng_alloc(gsl_rng_mt19937);
      // inicializamos el rng al principio, despues le seguimos pidiendo
      // randoms sin inicializar sino salen siempre los mismos shoes
      gsl_rng_set(blackjack.rng, blackjack_ini.rng_seed);
#else
      srandom(blackjack_ini.rng_seed);
#endif
      
      
    }
    
    if (blackjack.infinite_decks_card_number_for_arranged_ones < blackjack.n_arranged_cards) {
      dealt_tag = blackjack.arranged_cards_array[blackjack.infinite_decks_card_number_for_arranged_ones];
    } else {
#ifdef HAVE_LIBGSL
      dealt_tag = 1+gsl_rng_uniform_int(blackjack.rng, 52);
#else
      dealt_tag = 1+52*random()/RAND_MAX;
#endif    
    }
    blackjack.infinite_decks_card_number_for_arranged_ones++;
    
  } else {
    
    if (blackjack.current_card_index >= 52*blackjack_ini.decks) {
      return 0;
    }
    blackjack.last_pass = (blackjack.current_card_index >= blackjack.cut_card_index) || blackjack_ini.shuffle_every_hand;

    dealt_tag = blackjack.shoe[blackjack.current_card_index++];
  }
  
  return dealt_tag;
}

card_t *deal_card_to_hand(hand_t *hand) {
  int dealt_tag;
  card_t *card;
  
  if ((dealt_tag = deal_card()) == 0) {
    shuffle_shoe();
    dealt_tag = deal_card();
  }

  card = calloc(1, sizeof(card_t));
  assert(card != NULL);
  memcpy(card, &blackjack.card[dealt_tag], sizeof(card_t));
  append_card(&hand->cards, card);

  compute_count(hand);
  
  return card;
}



/*
hand_t *new_hand(hand_t **hands, int id, int bet) {
  hand_t *hand = calloc(1, sizeof(hand_t));
  hand->id = id;
  hand->bet = bet;
  LL_APPEND(*hands, hand);
  return hand;  
}
*/

void destroy_hands(hand_t **hands) {
  hand_t *hand, *tmp;
  card_t *card, *tmp2;

  for (hand = *hands; hand != NULL && (tmp = hand->next) != NULL; hand = tmp) { 
    for (card = hand->cards; card != NULL && (tmp2 = card->next) != NULL; card = tmp2) {   
      delete_card(&hand->cards, card);
      free(card);
      card = NULL;
    }
    delete_hand(hands, hand);
    free(hand);
    hand = NULL;
  }
  *hands = NULL;
  return;
}

void init_shoe(void)  {

  int i;
  int deck;
  int tag;  // an integer between 1 and 52 inclusive

  if (blackjack.shoe == NULL) {
    blackjack.shoe = malloc(blackjack_ini.decks * 52 * sizeof(int));
#ifdef HAVE_LIBGSL
    // TODO: choose
    blackjack.rng = gsl_rng_alloc(gsl_rng_mt19937);
    // inicializamos el rng al principio, despues le seguimos pidiendo
    // randoms sin inicializar sino salen siempre los mismos shoes
    gsl_rng_set(blackjack.rng, blackjack_ini.rng_seed);
#else
    srandom(blackjack_ini.rng_seed);
#endif
    
  }

  // init the shoe: there can be many decks
  // each deck has 4 suits { 0 = "spades", 1 = "hearts", 2 = "diamonds", 3 = "clubs" }
  // each suit has 13 ranks 1--13
  // the "tag" is 13*suit+rank
  i = 0;
  for (deck = 0; deck < blackjack_ini.decks; deck++) {
    for (tag = 1; tag <= 52; tag++) {
      blackjack.shoe[i++] = tag;
    }
  }  
  
  blackjack.current_card_index = 0;

  return;
}


void shuffle_shoe(void) {

  int i, j, k;
  card_t *card;

  // si tenemos decks = 0 (infinitos) entonces no hace
  // falta mezclar, sorteamos una carta cada vez que nos piden
  if (blackjack_ini.decks != -1) {
    // vemos si hay que inicializar el shoe
    if (blackjack.shoe == NULL) {
      init_shoe();
    }
  
    // mezclamos
    for (i = 52*(blackjack_ini.decks)-1; i > 0; i--) {
#ifdef HAVE_LIBGSL      
      j = gsl_rng_uniform_int(blackjack.rng, i);
#else
      j = i*random()/RAND_MAX;
#endif

      // manual de la CZ1000
      k = blackjack.shoe[i];
      blackjack.shoe[i] = blackjack.shoe[j];
      blackjack.shoe[j] = k;
    }

    // ponemos la cut card segun la penetracion (hace desde el 2004 que quiero hacer esto)
#ifdef HAVE_LIBGSL    
    blackjack.cut_card_index = 52*(blackjack_ini.decks) * (blackjack_ini.penetration + gsl_ran_gaussian(blackjack.rng, blackjack_ini.penetration_sigma));
#else
    blackjack.cut_card_index = 52*(blackjack_ini.decks) * (blackjack_ini.penetration);
#endif    

    // empezamos en la primera (el dealer es que el que tiene que quemar)  
    blackjack.current_card_index = 0;

    // ponemos primero las que estan arregladas
    j = 0;
    for (card = blackjack_ini.arranged_cards; card != NULL; card = card->next) {
      for (i = 52*(blackjack_ini.decks)-1; i > 0; i--) {
        if (blackjack.shoe[i] == card->tag) {
          blackjack.shoe[i] = blackjack.shoe[j];
          blackjack.shoe[j] = card->tag;
          break;
        }
      }
      j++;
    }

    // contamos cuantos shuffles hubo (de curiosos)  
    blackjack.shuffles++;
  }
    
  return;
}
