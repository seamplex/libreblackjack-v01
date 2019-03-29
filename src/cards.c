/*------------ -------------- -------- --- ----- ---   --       -            -
 *  libreblackjack
 *
 *  Copyright (C) 2016,2019 jeremy theler
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
#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "libreblackjack.h"



char suitname[4][12]  = {"spades", "hearts", "diamonds", "clubs"};
char suitletter[4][8] = {"S",      "H",      "D",        "C"};
char suitcode[4][8]   = {"♠", "♥", "♦", "♣"};
//char suitcode[4][8]   = {"\u2660", "\u2665", "\u2666", "\u2663"};
char numbername[14][4] = {"X", "A", "2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K"};
int value[14] = {0, 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};




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
    LL_FOREACH(hand->cards, card) {
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
  LL_FOREACH(hand->cards, card) {
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
    
    if (blackjack.card == NULL) {
      card_t *card;
      int suit, number, i;
      blackjack.card = calloc(52+1, sizeof(card_t));

      for (suit = 0; suit < 4; suit++) {
        for (number = 1; number <= 13; number++) {
          init_card(13*suit + number, number, suit);
        }
      }
      
      blackjack.n_arranged_cards = 0;
      LL_FOREACH(blackjack_ini.arranged_cards, card) {
        blackjack.n_arranged_cards++;
      }
      blackjack.arranged_cards_array = calloc(blackjack.n_arranged_cards, sizeof(int));
      
      i = 0;
      LL_FOREACH(blackjack_ini.arranged_cards, card) {
        blackjack.arranged_cards_array[i++] = card->tag;
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
  LL_APPEND(hand->cards, card);

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
  
  LL_FOREACH_SAFE(*hands, hand, tmp) {
    LL_FOREACH_SAFE(hand->cards, card, tmp2) {
      LL_DELETE(hand->cards, card);
      free(card);
      card = NULL;
    }
    LL_DELETE(*hands, hand);
    free(hand);
    hand = NULL;
  }
  *hands = NULL;
  return;
}

void init_shoe(void)  {

  int i;
  int deck, suit, rank;
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
    
    blackjack.card = calloc(52+1, sizeof(card_t));
  }

  // init the shoe: there can be many decks
  // each deck has 4 suits { 0 = "spades", 1 = "hearts", 2 = "diamonds", 3 = "clubs" }
  // each suit has 13 ranks 1--13
  // the "tag" is 13*suit+rank
  i = 0;
  for (deck = 0; deck < blackjack_ini.decks; deck++) {
    for (suit = 0; suit < 4; suit++) {
      for (rank = 1; rank <= 13; rank++) {
        tag = 13*suit + rank;
        if (deck == 0) {
          init_card(tag, rank, suit);
        }
        blackjack.shoe[i++] = tag;
      }
    }
  }  
  
  blackjack.current_card_index = 0;

  // https://en.wikipedia.org/wiki/Playing_cards_in_Unicode
  // yes, I could loop and compute the code for each card and
  // it would be hacky but hard to understand for humans
  // UNIX rule of representation!
  sprintf(blackjack.card[1].token[card_utf8_single], "🂡");
  sprintf(blackjack.card[2].token[card_utf8_single], "🂢");
  sprintf(blackjack.card[3].token[card_utf8_single], "🂣");
  sprintf(blackjack.card[4].token[card_utf8_single], "🂤");
  sprintf(blackjack.card[5].token[card_utf8_single], "🂥");
  sprintf(blackjack.card[6].token[card_utf8_single], "🂦");
  sprintf(blackjack.card[7].token[card_utf8_single], "🂧");
  sprintf(blackjack.card[8].token[card_utf8_single], "🂨");
  sprintf(blackjack.card[9].token[card_utf8_single], "🂩");
  sprintf(blackjack.card[10].token[card_utf8_single], "🂪");
  sprintf(blackjack.card[11].token[card_utf8_single], "🂫");
  sprintf(blackjack.card[12].token[card_utf8_single], "🂭");
  sprintf(blackjack.card[13].token[card_utf8_single], "🂮");
  
  sprintf(blackjack.card[14].token[card_utf8_single], "🂱");
  sprintf(blackjack.card[15].token[card_utf8_single], "🂲");
  sprintf(blackjack.card[16].token[card_utf8_single], "🂳");
  sprintf(blackjack.card[17].token[card_utf8_single], "🂴");
  sprintf(blackjack.card[18].token[card_utf8_single], "🂵");
  sprintf(blackjack.card[19].token[card_utf8_single], "🂶");
  sprintf(blackjack.card[20].token[card_utf8_single], "🂷");
  sprintf(blackjack.card[21].token[card_utf8_single], "🂸");
  sprintf(blackjack.card[22].token[card_utf8_single], "🂹");
  sprintf(blackjack.card[23].token[card_utf8_single], "🂺");
  sprintf(blackjack.card[24].token[card_utf8_single], "🂻");
  sprintf(blackjack.card[25].token[card_utf8_single], "🂽");
  sprintf(blackjack.card[26].token[card_utf8_single], "🂾");
  
  sprintf(blackjack.card[27].token[card_utf8_single], "🃁");
  sprintf(blackjack.card[28].token[card_utf8_single], "🃂");
  sprintf(blackjack.card[29].token[card_utf8_single], "🃃");
  sprintf(blackjack.card[30].token[card_utf8_single], "🃄");
  sprintf(blackjack.card[31].token[card_utf8_single], "🃅");
  sprintf(blackjack.card[32].token[card_utf8_single], "🃆");
  sprintf(blackjack.card[33].token[card_utf8_single], "🃇");
  sprintf(blackjack.card[34].token[card_utf8_single], "🃈");
  sprintf(blackjack.card[35].token[card_utf8_single], "🃉");
  sprintf(blackjack.card[36].token[card_utf8_single], "🃊");
  sprintf(blackjack.card[37].token[card_utf8_single], "🃋");
  sprintf(blackjack.card[38].token[card_utf8_single], "🃍");
  sprintf(blackjack.card[39].token[card_utf8_single], "🃍");
  
  sprintf(blackjack.card[40].token[card_utf8_single], "🃑");
  sprintf(blackjack.card[41].token[card_utf8_single], "🃒");
  sprintf(blackjack.card[42].token[card_utf8_single], "🃓");
  sprintf(blackjack.card[43].token[card_utf8_single], "🃔");
  sprintf(blackjack.card[44].token[card_utf8_single], "🃕");
  sprintf(blackjack.card[45].token[card_utf8_single], "🃖");
  sprintf(blackjack.card[46].token[card_utf8_single], "🃗");
  sprintf(blackjack.card[47].token[card_utf8_single], "🃘");
  sprintf(blackjack.card[48].token[card_utf8_single], "🃙");
  sprintf(blackjack.card[49].token[card_utf8_single], "🃚");
  sprintf(blackjack.card[50].token[card_utf8_single], "🃛");
  sprintf(blackjack.card[51].token[card_utf8_single], "🃝");
  sprintf(blackjack.card[52].token[card_utf8_single], "🃞");

  return;
}

void init_card(int tag, int rank, int suit) {
    
  blackjack.card[tag].tag = tag;
  blackjack.card[tag].value = value[rank];
  
  if (stdout_opts.isatty) {
    sprintf(blackjack.card[tag].text, "%s%s%s%s", (suit == 1 || suit == 2) ? stdout_opts.red : stdout_opts.black,
            numbername[rank], suitcode[suit], stdout_opts.reset);
  } else {
    sprintf(blackjack.card[tag].text, "%s%s", numbername[rank], suitletter[suit]);
  }

  sprintf(blackjack.card[tag].token[card_tag],             "%d", tag);
  sprintf(blackjack.card[tag].token[card_ascii], "%s%s", numbername[rank], suitletter[suit]);
  sprintf(blackjack.card[tag].token[card_utf8],  "%s%s", numbername[rank], suitcode[suit]);
  sprintf(blackjack.card[tag].token[card_value],           "%d", value[rank]);

  sprintf(blackjack.card[tag].art[0], " _____ ");
  sprintf(blackjack.card[tag].art[1], "|%s    |", numbername[rank]);
  sprintf(blackjack.card[tag].art[2], "|     |");
  sprintf(blackjack.card[tag].art[3], "|  %s  |", suitcode[suit]);
  sprintf(blackjack.card[tag].art[4], "|     |");
  sprintf(blackjack.card[tag].art[5], "|____%s|", numbername[rank]);

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
    LL_FOREACH(blackjack_ini.arranged_cards, card) {
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
