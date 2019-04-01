/*------------ -------------- -------- --- ----- ---   --       -            -
 *  libreblackjack
 *
 *  Copyright (C) 2019 jeremy theler
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
#include <ctype.h>

int count;
char dummy[32];
char *response;

char *hit = "h";
char *stand = "s";

#define COMMENT -1
#define HARD     0
#define SOFT     1
#define PAIR     2

// first index = hard, soft, pair
// second index = count (or face for pairs)
// third index = dealer upcard
char strategy[3][32][16];
int initialized;

int internal_init(void) {
  FILE *file;
  char line[256];
  int type, count;
  char *data;
  
  if ((file = fopen("bs.txt", "r")) != NULL) {
    while (fgets(line, 255, file) != NULL) {
      switch (line[0]) {
        case 'h':  // hard count
          type = HARD;
          break;
        case 's':
          type = SOFT;
          break;
        case 'p':
          type = PAIR;
          break;
        default:  // comment
          type = COMMENT;
          break;
      }
      
      if (type != COMMENT) {
        if (type == PAIR && isalpha(line[1])) {
          // pairs can be "pA" or "pT"
          if (line[1] == 'A') {
            count = 11;
          } else if (line[1] == 'T') {
            count = 10;
          } else {
            return -1;
          }
        } else {
          // other should be numbers
          if ((sscanf(line+1, "%d", &count) == 0)) {
            return -1;
          }
        }
        
        // get to the first non-blank character
        data = line+3;
        while (*data == ' ') {
          data++;
        }
        
        if (sscanf(data, "%c %c %c %c %c %c %c %c %c %c",
              &strategy[type][count][2],
              &strategy[type][count][3],
              &strategy[type][count][4],
              &strategy[type][count][5],
              &strategy[type][count][6],
              &strategy[type][count][7],
              &strategy[type][count][8],
              &strategy[type][count][9],
              &strategy[type][count][10],
              &strategy[type][count][11]) != 10) {
          return -1;
        }
        
        // special cases
        // h4 = p2
        if (type == HARD && count == 4) {
          memcpy(strategy[PAIR][2], strategy[type][count], 16*sizeof(char));
        } else if (type == PAIR && count == 2) {
          memcpy(strategy[HARD][4], strategy[type][count], 16*sizeof(char));
        }
        
        // h20 = pT
        if (type == HARD && count == 20) {
          memcpy(strategy[PAIR][10], strategy[type][count], 16*sizeof(char));
        } else if (type == PAIR && count == 10) {
          memcpy(strategy[HARD][20], strategy[type][count], 16*sizeof(char));
        }

        // s12 = pA
        if (type == SOFT && count == 12) {
          memcpy(strategy[PAIR][11], strategy[type][count], 16*sizeof(char));
        } else if (type == PAIR && count == 11) {
          memcpy(strategy[SOFT][12], strategy[type][count], 16*sizeof(char));
        }
        
        
      }
      
      
    }
  
    fclose(file);
  }
  
  initialized = 1;
  
  return 0;
  
}

int dealer_to_internal(player_t *player, const char *command) {

  int type;
  int count;
  
  if (!initialized) {
    internal_init();
  }
  
  if (strncmp(command, "play?", 5) == 0) {
    if (player->current_hand->n_cards == 2 && player->current_hand->cards->value == player->current_hand->cards->next->value) {
      type = PAIR;
      count = player->current_hand->cards->value;
    } else if (player->current_hand->soft) {
      type = SOFT;
      count = player->current_hand->count;
    } else {
      type = HARD;
      count = player->current_hand->count;
    }

    response = &strategy[type][count][blackjack.dealer_hand->cards->value];

    // if strategy calls for double but we are not allowed, hit
    if (response[0] == 'd' && player->current_hand->n_cards != 2) {
      response = hit;
    }
  } else {
    return -1;
  }
  
  return 0;
}


int player_from_internal(player_t *player, char *buffer) {

  strncpy(buffer, response, 1);
  
  return 0;
}
