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

#ifndef _LIBREBLACKJACK_H_
#include "libreblackjack.h"
#endif

int dealer_action(void) {
  player_t *player;
  card_t *card;
  hand_t *hand;
  double delta;
  int i;

  player = blackjack.players;
  // dealer_action
  switch (blackjack.next_dealer_action) {
    case START_NEW_HAND:
      if (blackjack_conf.hands > 0 && blackjack.hand >= blackjack_conf.hands) {
        blackjack.done = 1;
        return 0;
      }

      // update the uncertainty (knuth citing welford)
      // The Art of Computer Programming, volume 2: Seminumerical Algorithms, 3rd edn., p. 232
      delta = player->current_result - player->mean;
      if (blackjack.hand != 0) {
        player->mean += delta / (double)(blackjack.hand);
        player->M2 += delta * (player->current_result - player->mean);
        player->variance = player->M2 / (double)(blackjack.hand);
      }
      
      blackjack.infinite_decks_card_number_for_arranged_ones = 0;
      blackjack.hand++;
      
      // delete dealer's hand and create a new one
      destroy_hands(&blackjack.dealer_hand);
      hand = calloc(1, sizeof(hand_t));
      append_hand(&blackjack.dealer_hand, hand);
      
      // mark that the hole card was not seen
      blackjack.holecard_shown = 0;
        
      // erase all the player's hand
      destroy_hands(&player->hands);
      
      
      // set that nobody won anythin nor splitted nor doubled down
      player->current_result = 0;
      player->has_split = 0;
      player->doubled = 0;
      
      if (blackjack.last_pass) {
        
        bjcall(blackjack.current_player->write(player, "shuffling"));
        shuffle_shoe();  // shuffle the cards
        // TODO: reset card counting systems
        // burn as many cards as asked
        for (i = 0; i < blackjack_conf.number_of_burnt_cards; i++) {
          deal_card();
        }
        blackjack.last_pass = 0;
      }

      // create the main hand
      hand = calloc(1, sizeof(hand_t));
      append_hand(&player->hands, hand);
      player->current_hand = player->hands;   // current hand is the first one
      
      if (player->flat_bet != 0) {
        player->current_hand->bet = player->flat_bet;
        blackjack.next_dealer_action = DEAL_PLAYERS_FIRST_CARD;
      } else {
        blackjack.next_dealer_action = ASK_FOR_BETS;
      }

      bjcall(blackjack.current_player->write(player, "new_hand"));
    break;

    case ASK_FOR_BETS:
      // step 1. ask for bets
      snprintf(outputbuffer, BUF_SIZE-1, "bet?");   // this is so we can re-ask in case no number comes back
      blackjack.players_input_needed = BET;
      
    break;

    case DEAL_PLAYERS_FIRST_CARD:
      // step 3. deal the first card to each player
      player = blackjack.players;
      player->number_of_hands++;   // splits are counted as a single hand
      player->total_money_waged += player->current_hand->bet;
      
      // each player has a single hand here
      card = deal_card_to_hand(player->current_hand);
      bjcall(write_formatted_card(player, 0,  "card_player_first", card));
      
      // step 4. show dealer's upcard
      card = deal_card_to_hand(blackjack.dealer_hand);
      bjcall(write_formatted_card(player, 0,  "card_dealer_up", card));
      if (stdout_opts.isatty) { print_card_art(card); }
      
      // step 5. deal the second card to each player
      card = deal_card_to_hand(player->current_hand);
      bjcall(write_formatted_card(player, 0,  "card_player_second", card));
      if (stdout_opts.isatty) { print_hand_art(player->current_hand); }

      // TODO: ENHC
      blackjack.next_dealer_action = DEAL_DEALERS_HOLE_CARD;
    break;

    case DEAL_DEALERS_HOLE_CARD:
      // step 6. deal the dealer's hole card 
      deal_card_to_hand(blackjack.dealer_hand);

      // pointer to the hole card
      blackjack.dealer_holecard = blackjack.dealer_hand->cards->next;

      if (blackjack.dealer_hand->cards->value == 11) {
        if (player->no_insurance == 0 && player->always_insure == 0) {
          blackjack.next_dealer_action = ASK_FOR_INSURANCE;
        } else if (player->always_insure) {
          player->hands->insured = 1;
          player->current_result -= 0.5*player->hands->bet;
          player->bankroll -= 0.5*player->hands->bet;
          player->insured_hands++;
        }
        blackjack.next_dealer_action = CHECK_FOR_BLACKJACKS;
      } else if (blackjack.dealer_hand->cards->value == 10 || blackjack.dealer_hand->cards->value == 11) {
        blackjack.next_dealer_action = CHECK_FOR_BLACKJACKS;
      } else if (player->current_hand->count == 21) {
        blackjack.next_dealer_action = CHECK_FOR_BLACKJACKS;
      } else {
        blackjack.next_dealer_action = ASK_FOR_PLAY;
      }
              
    break;

    case ASK_FOR_INSURANCE:
      snprintf(outputbuffer, BUF_SIZE-1, "insurance?");
      blackjack.players_input_needed = INSURANCE;
    break;

    case CHECK_FOR_BLACKJACKS:
      // step 7. check if there are any blackjack
      if (blackjack.dealer_hand->blackjack) {
        bjcall(write_formatted_card(player, 0,  "card_dealer_hole", blackjack.dealer_holecard));
        bjcall(blackjack.current_player->write(player, "blackjack_dealer"));
        player->dealer_blackjacks++;
        if (stdout_opts.isatty) { print_hand_art(blackjack.dealer_hand); }
        
        if (player->current_hand->insured) {
          bjcall(write_formatted(player, "player_wins_insurance %d", player->current_hand->bet));
          player->current_result += player->current_hand->bet;
          player->bankroll += player->current_hand->bet;
          player->insured_wins++;
        }
        
        if (player->current_hand->blackjack) {
          bjcall(blackjack.current_player->write(player, "blackjack_player_also"));
          player->player_blackjacks++;
          if (player->has_split) {
            bjcall(write_formatted(player, "player_pushes %d #%d", player->current_hand->bet, player->current_hand->id));
          } else {
            bjcall(write_formatted(player, "player_pushes %d", player->current_hand->bet));
          }
          player->pushes++;
          if (stdout_opts.isatty) { print_hand_art(player->current_hand); }
        } else {
          if (player->has_split) {
            bjcall(write_formatted(player, "player_losses %d #%d", player->current_hand->bet, player->current_hand->id));
          } else {
            bjcall(write_formatted(player, "player_losses %d", player->current_hand->bet));
          }
          player->current_result -= player->current_hand->bet;
          player->bankroll -= player->current_hand->bet;
          if (player->bankroll < player->worst_bankroll) {
            player->worst_bankroll = player->bankroll;
          }
          player->losses++;
        }
 
        blackjack.next_dealer_action = START_NEW_HAND;

      } else if (player->current_hand->blackjack) {
          bjcall(blackjack.current_player->write(player, "blackjack_player"));
          player->current_result += blackjack_conf.blackjack_pays * player->current_hand->bet;
          player->bankroll += blackjack_conf.blackjack_pays * player->current_hand->bet;
          player->player_blackjacks++;
          bjcall(write_formatted(player, "player_wins %g", blackjack_conf.blackjack_pays * player->current_hand->bet));
          player->wins++;
          player->blackjack_wins++;
          
          blackjack.next_dealer_action = START_NEW_HAND;
          
      } else {
        // only if the dealer had the chance to have a blackjack we say "no_blackjacks"
        if (blackjack.dealer_hand->cards->value == 10 || blackjack.dealer_hand->cards->value == 11) {
          bjcall(blackjack.current_player->write(player, "no_blackjacks"));
        }
        blackjack.next_dealer_action = ASK_FOR_PLAY;
        
      }
    break;
    case ASK_FOR_PLAY:
      if (stdout_opts.isatty) { printf(_("player's count is %s%d\n"), player->current_hand->soft?"soft ":"", player->current_hand->count); }
      
      snprintf(outputbuffer, BUF_SIZE-1, "play? %d %d", player->current_hand->soft?-player->current_hand->count:player->current_hand->count, blackjack.dealer_hand->cards->value);
      blackjack.players_input_needed = PLAY;
      // in process_input we have to set next_dealer_action
      
    break;
    case MOVE_ON_TO_NEXT_HAND:
      // see if we finished all the player's hands
      if (player->current_hand->next != NULL) {
        player->current_hand = player->current_hand->next;
        card = deal_card_to_hand(player->current_hand);
        if (player->has_split && player->current_hand->n_cards == 2) {
          bjcall(write_formatted_card(player, 0,  "card_player_second", card));
        } else {
          bjcall(write_formatted_card(player, 0,  "card_player", card));
        }
        if (stdout_opts.isatty) { print_hand_art(player->current_hand); }
        
        if (player->current_hand->count == 21) {
          blackjack.next_dealer_action = MOVE_ON_TO_NEXT_HAND;
        } else {
          blackjack.next_dealer_action = ASK_FOR_PLAY;
        } 
          
        
      } else {
        // assume the player busted in all the hands
        player->busted_all_hands = 1;
        for(hand = player->hands; hand != NULL; hand = hand->next) {
          // if she did not bust, set zero
          if (hand->busted == 0) {
            player->busted_all_hands = 0;
          }
        }
        
        if (player->busted_all_hands) {
          if (stdout_opts.isatty) { printf(_("player busted all hands\n")); }
          bjcall(write_formatted_card(player, 0,  "card_dealer_hole", blackjack.dealer_holecard));
          blackjack.holecard_shown = 1;
          if (stdout_opts.isatty) { printf(_("dealer's hand was \n")); }
          if (stdout_opts.isatty) { print_hand_art(blackjack.dealer_hand); }
          blackjack.next_dealer_action = START_NEW_HAND;
          
        } else {
          blackjack.next_dealer_action = HIT_DEALERS_HAND;
          
        }
      }
    
    break;
    case HIT_DEALERS_HAND:
      bjcall(write_formatted_card(player, 1,  "card_dealer_hole", blackjack.dealer_holecard));
      blackjack.holecard_shown = 1;
      if (stdout_opts.isatty) { print_hand_art(blackjack.dealer_hand); }
      if (stdout_opts.isatty) { printf(_("dealer's count is %s%d\n"), blackjack.dealer_hand->soft?"soft ":"", blackjack.dealer_hand->count); }
      
      // hit if count is less than 17 (or equalt to soft 17 if hit_soft_17 is true)
      while (((blackjack.dealer_hand->count < 17 || (blackjack_conf.hit_soft_17 && blackjack.dealer_hand->count == 17 && blackjack.dealer_hand->soft))) && blackjack.dealer_hand->busted == 0) {
        card = deal_card_to_hand(blackjack.dealer_hand);
        bjcall(write_formatted_card(player, 1, "card_dealer", card));
        if (stdout_opts.isatty) { print_hand_art(blackjack.dealer_hand); }
        if (stdout_opts.isatty) { printf(_("dealer's count is %s%d\n"), blackjack.dealer_hand->soft?"soft ":"", blackjack.dealer_hand->count); }
      }
      
      if (blackjack.dealer_hand->busted) {
        bjcall(player->write(player, "busted_dealer"));
        player->dealer_busts++;
        for(hand = player->hands; hand != NULL; hand = hand->next) {
          if (hand->busted == 0) {
            if (player->has_split) {
              bjcall(write_formatted(player, "player_wins %d #%d", hand->bet, hand->id));
            } else {
              bjcall(write_formatted(player, "player_wins %d", hand->bet));
            }
            player->current_result += hand->bet;
            player->bankroll += hand->bet;
            player->wins++;
            if (player->doubled) {
              player->doubled_wins++;
            } else {
              player->plain_wins++;
            }
          }
        }
      } else {
        for(hand = player->hands; hand != NULL; hand = hand->next) {
          if (hand->busted == 0) {  // busted hands have already been solved
            if (blackjack.dealer_hand->count > hand->count) {
              if (player->has_split) {
                bjcall(write_formatted(player, "player_losses %d #%d", hand->bet, hand->id));
              } else {
                bjcall(write_formatted(player, "player_losses %d", hand->bet));
              }
              player->current_result -= hand->bet;
              player->bankroll -= hand->bet;
              if (player->bankroll < player->worst_bankroll) {
                player->worst_bankroll = player->bankroll;
              }
              player->losses++;
            } else if (blackjack.dealer_hand->count == hand->count) {
              if (player->has_split) {
                bjcall(write_formatted(player, "player_pushes #%d", hand->id));
              } else {
                bjcall(write_formatted(player, "player_pushes"));
              }
              player->pushes++;
            } else {
              if (player->has_split) {
                bjcall(write_formatted(player, "player_wins %d #%d", hand->bet, hand->id));
              } else {
                bjcall(write_formatted(player, "player_wins %d", hand->bet));
              }
              player->current_result += hand->bet;
              player->bankroll += hand->bet;
              player->wins++;
              
              // TODO: this does not work for split hand
              if (player->doubled) {
                player->doubled_wins++;
              } else {
                player->plain_wins++;
              }
            }
          }
        }
      }

      blackjack.next_dealer_action = START_NEW_HAND;

    break;
    
  }
  
  return 0;
}

// returns zero if it is a common command and we need to ask again
// returns positive if what was asked was answered
// returns negative if what was aked was not asnwered or the command does not apply
int dealer_process_input(player_t *player, char *command) {
  
  hand_t *hand;
  card_t *card;
  
  // we firs check common commands
/// quit  
  if (strcmp(command, "quit") == 0 || strcmp(command, "q") == 0) {
    blackjack.done = 1;
    return 1;

/// help    
  } else if (strcmp(command, "help") == 0) {
    printf("help yourself\n");
    return 0;

/// count    
  } else if (strcmp(command, "count") == 0 || strcmp(command, "c") == 0) {
    bjcall(write_formatted(player, "%d", (player->current_hand->soft?(-1):(+1)) * player->current_hand->count));
    return 0;

/// upcard_value
  } else if (strcmp(command, "upcard_value") == 0 || strcmp(command, "upcard") == 0 || strcmp(command, "u") == 0) {
    bjcall(write_formatted(player, "%d", blackjack.dealer_hand->cards->value));
    return 0;
    
/// bankroll
  } else if (strcmp(command, "bankroll") == 0 || strcmp(command, "b") == 0) {
    bjcall(write_formatted(player, "%g", player->bankroll));
    return 0;

/// hands
  } else if (strcmp(command, "hands") == 0) {
    bjcall(write_formatted(player, "%g", blackjack.hand));
    return 0;

/// table
  } else if (strcmp(command, "table") == 0 || strcmp(command, "t") == 0) {
    // TODO: give a command back
    // TODO: if table if empty, do not segfault
    printf("\n");
    printf(_("current table\n"));
    for (player = blackjack.players; player != NULL; player = player->next) {
      for (hand = player->hands; hand != NULL; hand = hand->next) {
        printf(_("%s's hand #%d: "), player->name, hand->id);
        for (card = hand->cards; card != NULL; card = card->next) {
          printf(" ");
          print_card_unicode(card);
        }
        if (hand->blackjack) {
          printf(" (blackjack)\n");
        } else {
          printf(" (%s%d)\n", hand->soft?"soft ":"", hand->count);
        }
      }
    }
    
    if (blackjack.holecard_shown == 0) {
      printf(_("dealer's upcard :  "));
      print_card_unicode(blackjack.dealer_hand->cards);
      printf("\n");      
    } else {
      printf(_("dealer's hand  :  "));
      for(card = blackjack.dealer_hand->cards; card != NULL; card = card->next) {
        printf(" ");
        print_card_unicode(card);
      }
      if (blackjack.dealer_hand->blackjack) {
        printf("(blackjack)\n");
      } else {
        printf("(%s%d)\n", blackjack.dealer_hand->soft?"soft ":"", blackjack.dealer_hand->count);
      }
    }
    
    
    return 0;
  } else if (command[0] == '\n') {
    return 0;
  }
  
  // particular commands
  // these have to return a positive number
  switch(blackjack.players_input_needed) {
    case BET:
      player->current_hand->bet = atoi(command);
      // TODO: bet = 0 -> wonging
      if (player->hands->bet <= 0 || (blackjack_conf.max_bet != 0 && player->hands->bet > blackjack_conf.max_bet)) {
        bjcall(write_formatted(player, "invalid_bet %d", player->hands->bet));
        return -1;
      } else {
        blackjack.next_dealer_action = DEAL_PLAYERS_FIRST_CARD;
        return 1;
      }
    break;
    case INSURANCE:
      if (strcmp(command, "yes") == 0 || strcmp(command, "y") == 0) {
        player->hands->insured = 1;
        player->current_result -= 0.5*player->hands->bet;
        player->bankroll -= 0.5*player->hands->bet;
        player->insured_hands++;
      } else if (strcmp(command, "no") == 0 || strcmp(command, "n") == 0) {
        ;
      } else {
        bjcall(write_formatted(player, "invalid_command"));
        if (stdout_opts.isatty) { printf(_("answer either yes or no to insurance\n")); }
        return -1;
      }
      blackjack.next_dealer_action = CHECK_FOR_BLACKJACKS;
      return 1;
    break;
    case PLAY:
      if (strcmp(command, "stand") == 0 || strcmp(command, "s") == 0) {
        blackjack.next_dealer_action = MOVE_ON_TO_NEXT_HAND;
        return 1;
      } else if (strcmp(command, "double") == 0 || strcmp(command, "d") == 0) {
        if (player->current_hand->n_cards == 2) {
          if (stdout_opts.isatty) { printf(_("doubling down, dealing only one card\n")); }
          
          // TODO: check bankroll
          player->current_hand->bet *= 2;
          player->doubled_hands++;
          player->doubled = 1;
          player->total_money_waged += player->current_hand->bet;
          
          card = deal_card_to_hand(player->current_hand);
          bjcall(write_formatted_card(player, 0,  "card_player", card));
          if (stdout_opts.isatty) { print_hand_art(player->current_hand); }
          if (stdout_opts.isatty) { printf(_("player's count is %s%d\n"), player->current_hand->soft?"soft ":"", player->current_hand->count); }

          if (player->current_hand->busted) {
            bjcall(write_formatted(player, "busted_player %d", player->current_hand->count));
            if (stdout_opts.isatty) { printf(_("player busted with %d\n"), player->current_hand->count); }
            player->current_result -= player->current_hand->bet;
            player->bankroll -= player->current_hand->bet;
            player->player_busts++;
            player->losses++;
          }
          
          blackjack.next_dealer_action = MOVE_ON_TO_NEXT_HAND;
          return 1;          

        } else {
          bjcall(write_formatted(player, "invalid_command"));
          if (stdout_opts.isatty) { printf(_("cannot double down now\n")); }
          return -1;
        }
      } else if (strcmp(command, "split") == 0 || strcmp(command, "p") == 0) {
        if (player->has_split < 3 &&  // up to three splits (i.e. four hands) TODO: option
            player->current_hand->n_cards == 2 && player->current_hand->cards->value == player->current_hand->cards->next->value) {
          // mark that we split to put ids in the hands
          player->has_split++;
          
          // the first hand is id 1, then we add one
          if (player->current_hand == player->hands) {
            player->current_hand->id = 1;
          }
          
          hand = calloc(1, sizeof(hand_t));
          // TODO: check bankroll
          hand->bet = player->current_hand->bet;
          player->total_money_waged += player->current_hand->bet;
          hand->id = player->current_hand->id + 1;
          append_hand(&player->hands, hand);
          
          // take the second card to the second hand
          card = calloc(1, sizeof(card_t));
          memcpy(card, &blackjack.card[player->current_hand->cards->next->tag], sizeof(card_t));
          
          // remove the card from the first hand
          delete_card(&player->current_hand->cards, player->current_hand->cards->next);
          // and put it in the second hand
          append_card(&hand->cards, card);
          
          // deal a card to the first hand
          card = deal_card_to_hand(player->current_hand);

          bjcall(write_formatted_card(player, 0,  "card_player_second", card));
          if (stdout_opts.isatty) { print_hand_art(player->current_hand); }
          
          // aces get dealt only on card (and also if she already got 21)
          if (player->current_hand->cards->value == 11 || player->current_hand->count == 21) {
            if ((player->current_hand = player->current_hand->next) != NULL) {
              card = deal_card_to_hand(player->current_hand);

              bjcall(write_formatted_card(player, 0,  "card_player_second", card));
              if (stdout_opts.isatty) { print_hand_art(player->current_hand); }
              
              // if she had an ace or got 21 we are done
              if (player->current_hand->cards->value == 11 || player->current_hand->count == 21) {
                blackjack.next_dealer_action = MOVE_ON_TO_NEXT_HAND;
              } else {
                blackjack.next_dealer_action = ASK_FOR_PLAY;
              }
              return 1;
            } else {
              blackjack.next_dealer_action = MOVE_ON_TO_NEXT_HAND;
              return 1;
            }
          } else {
            blackjack.next_dealer_action = ASK_FOR_PLAY;
            return 1;
          }
          
        } else {
          bjcall(player->write(player, "invalid_command"));
          if (stdout_opts.isatty) { printf(_("cannot split now\n")); }
          return -1;
        }
        
      } else if (strcmp(command, "hit") == 0 || strcmp(command, "h") == 0) {
        card = deal_card_to_hand(player->current_hand);

        bjcall(write_formatted_card(player, 0,  "card_player", card));
        if (stdout_opts.isatty) { print_hand_art(player->current_hand); }

        if (player->current_hand->busted) {
          bjcall(write_formatted(player, "busted_player %d", player->current_hand->count));
          if (stdout_opts.isatty) { printf(_("player busted with %d\n"), player->current_hand->count); }
          player->current_result -= player->current_hand->bet;
          player->bankroll -= player->current_hand->bet;
          player->player_busts++;
          player->losses++;
          
          blackjack.next_dealer_action = MOVE_ON_TO_NEXT_HAND;
          return 1;
          
        } else if (player->current_hand->count == 21) {
          blackjack.next_dealer_action = MOVE_ON_TO_NEXT_HAND;
          return 1;
          
        } else {
          blackjack.next_dealer_action = ASK_FOR_PLAY;
          return 1;
        }
      } else {
        bjcall(player->write(player, "invalid_command"));
        return -1;
      }
    break;
  }
  
  return 0;
}
