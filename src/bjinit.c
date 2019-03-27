/*------------ -------------- -------- --- ----- ---   --       -            -
 *  libreblackjack
 *
 *  Copyright (C) 2016 German (jeremy) Theler
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

#include "libreblackjack.h"
#include "ini.h"

#define INI_TOKEN_SEPARATORS " \t"
#define MATCH(s, n) (strcmp(section, s) == 0 && strcmp(name, n) == 0)

int fbj_ini_handler(void* user, const char* section, const char* name, const char* value) {

  player_t *player;
  char *tokens;
  char *token;
  
// global options (el primero que llega entre ini y commandline pone la opcion)
  if (MATCH("", "decks")) {
    if (blackjack_ini.decks == 0) { blackjack_ini.decks = atoi(value); }

  } else if (MATCH("", "hands")) {
    // asi podemos poner cosas como 1e6
    if (blackjack_ini.hands == 0) { blackjack_ini.hands = (long int)(atof(value)); }

  } else if (MATCH("", "players")) {
    tokens = strdup(value);
    token = strtok(tokens, INI_TOKEN_SEPARATORS);
    while (token != NULL) {
      new_player(token);
      token = strtok(NULL, INI_TOKEN_SEPARATORS);
    }
    free(token);

  } else if (MATCH("", "rng_seed")) {
    if (blackjack_ini.rng_seed == 0) { blackjack_ini.rng_seed = atoi(value); }

  } else if (MATCH("", "rng_type")) {
//        blackjack_ini.rng_type = gsl_rng_mt19937;
    ;

  } else if (MATCH("", "number_of_burnt_cards") || MATCH("", "burnt_cards") || MATCH("", "burntcards")) {
    if (blackjack_ini.number_of_burnt_cards == -1) {  blackjack_ini.number_of_burnt_cards = atoi(value); }

  } else if (MATCH("", "penetration")) {
    if (blackjack_ini.penetration == 0) { blackjack_ini.penetration = atof(value); }
    if (blackjack_ini.penetration == 0) {
      blackjack_ini.penetration = 1e-6;
    }

  } else if (MATCH("", "penetration_sigma")) {
    if (blackjack_ini.penetration_sigma == 0) { blackjack_ini.penetration_sigma = atof(value); }

  } else if (MATCH("", "blackjack_pays") || MATCH("", "bjpays")) {
    if (blackjack_ini.blackjack_pays == -1) {
      if (strcmp(value, "3/2")) {
        blackjack_ini.blackjack_pays = 3.0/2.0;
      } else if (strcmp(value, "6/5")) {
        blackjack_ini.blackjack_pays = 6.0/5.0;
      } else {
        blackjack_ini.blackjack_pays = atof(value);
      }
    }

    if (blackjack_ini.blackjack_pays <= 0) {
      blackjack_push_error_message("blackjack_pays has to be positive, not '%s'", value);
      return -1;
    }

  } else if (MATCH("", "no_negative_bankrolls") || MATCH("", "bouncer")) {
    if (blackjack_ini.no_negative_bankroll == -1) { blackjack_ini.no_negative_bankroll = atoi(value); }

  } else if (MATCH("", "double_after_split") || MATCH("", "das")) {
    if (blackjack_ini.double_after_split == -1) { blackjack_ini.double_after_split = atoi(value); }

  } else if (MATCH("", "hit_soft_17") || MATCH("", "h17")) {
    if (blackjack_ini.hit_soft_17 == -1) { blackjack_ini.hit_soft_17 = atoi(value); }

  } else if (MATCH("", "max_bet") || MATCH("", "max_bet")) {
    if (blackjack_ini.max_bet == 0) {  blackjack_ini.max_bet = atoi(value); }

  } else if (MATCH("", "max_incorrect_commands")) {
    if (blackjack_ini.max_invalid_commands == -1 ) { blackjack_ini.max_invalid_commands = atoi(value); }

  } else if (MATCH("", "log")) {
    if (blackjack_ini.log == NULL ) {
      if ((blackjack_ini.log = fopen(value, "w")) == NULL) {
        blackjack_push_error_message("cannot open log file '%s': %s\n", value, strerror(errno));
        return -1;
      }
    }

  } else if (MATCH("", "yaml_report")) {
    if (blackjack_ini.yaml_report == NULL ) {
      if ((blackjack_ini.yaml_report = fopen(value, "w")) == NULL) {
        blackjack_push_error_message("cannot open YAML report file '%s': %s\n", value, strerror(errno));
        return -1;
      }
    }

  } else if (MATCH("", "arranged_cards")) {
    if (blackjack_ini.arranged_cards == NULL) {
      card_t *arranged_card;
      tokens = strdup(value);
      token = strtok(tokens, INI_TOKEN_SEPARATORS);
      while (token != NULL) {
        arranged_card = calloc(1, sizeof(card_t));
        arranged_card->tag = atoi(token);
        LL_APPEND(blackjack_ini.arranged_cards, arranged_card);
        token = strtok(NULL, INI_TOKEN_SEPARATORS);
      }
      free(tokens);
    }

  } else if (MATCH("", "shuffle_every_hand")) {
    if (blackjack_ini.shuffle_every_hand == -1 ) { blackjack_ini.shuffle_every_hand = atoi(value); }
    
// stdout      
  } else if (MATCH("stdout", "no_color")) {
    if (stdout_opts.no_color == 0) { stdout_opts.no_color = atoi(value); }

  } else if (MATCH("stdout", "no_utf8")) {
    if (stdout_opts.no_utf8 == 0) { stdout_opts.no_utf8 = atoi(value); }

  } else if (MATCH("stdout", "ascii_art")) {
    if (stdout_opts.ascii_art == 0) { stdout_opts.ascii_art = atoi(value); }
      
// player-based options
  } else if (strcmp(name, "flat_bet") == 0 || strcmp(name, "flatbet") == 0) {
    player = player_from_section(section);
    if (strcmp(value, "") == 0) {
      player->flat_bet = 1;
    } else {
      player->flat_bet = atoi(value);
    }

  } else if (strcmp(name, "no_insurance") == 0|| strcmp(name, "noinsurance") == 0) {
    player = player_from_section(section);
    if (strcmp(value, "") == 0) {
      player->no_insurance = 1;
    } else {
      player->no_insurance = atoi(value);
    }
    
  } else if (strcmp(name, "always_insure") == 0|| strcmp(name, "insure") == 0) {
    player = player_from_section(section);
    if (strcmp(value, "") == 0) {
      player->always_insure = 1;
    } else {
      player->always_insure = atoi(value);
    }

  } else if (strcmp(name, "bankroll") == 0) {
    player = player_from_section(section);
    player->bankroll = atof(value);
    player->worst_bankroll = player->bankroll;

  } else if (strcmp(name, "delay") == 0) {
    player = player_from_section(section);
    player->delay = atof(value);

  } else if (strcmp(name, "card_format") == 0) {
    player = player_from_section(section);
    if (strcmp(value, "ascii") == 0) {
      player->card_type = card_ascii;
    } else if (strcmp(value, "utf8") == 0) {
      player->card_type = card_utf8;
    } else if (strcmp(value, "id") == 0) {
      player->card_type = card_id;
    } else if (strcmp(value, "value") == 0) {
      player->card_type = card_value;
    }

  } else if (strcmp(name, "buffered_fifos") == 0 || strcmp(name, "buffered_fifo") == 0 || strcmp(name, "bufferedfifo") == 0) {
    player = player_from_section(section);
    player->dealer2player.buffered = atoi(value);
    player->player2dealer.buffered = atoi(value);

  } else if (strcmp(name, "player2dealer") == 0 || strcmp(name, "dealer2player") == 0) {    
    ipc_t *ipc;
    player = player_from_section(section);
    
    if (strcmp(name, "player2dealer") == 0) {
      ipc = &(player->player2dealer);
    } else if (strcmp(name, "dealer2player") == 0) {
      ipc = &(player->dealer2player);
    }
    
    tokens = strdup(value);
    token = strtok(tokens, INI_TOKEN_SEPARATORS);
    
    if (strcmp(token, "fifo") == 0) {
      ipc->ipc_type = ipc_fifo;
    } else if (strcmp(token, "shmem") == 0) {
      ipc->ipc_type = ipc_shmem;
    } else if (strcmp(token, "mq") == 0 || strcmp(token, "mqueue") == 0) {
      ipc->ipc_type = ipc_mqueue;
    } else {
      blackjack_push_error_message("unkown ipc type '%s'", token);
      return 0;
    }
    
    // the object name
    if ((token = strtok(NULL, INI_TOKEN_SEPARATORS)) == NULL) {
      blackjack_push_error_message("expected object name after ipc type");
      return 0;
    }
    ipc->name = strdup(token);
    
    
    free(tokens);

  } else {
    blackjack_push_error_message("unknown keyword '%s'", name);
    return 0;  /* unknown section/name, error */
  }
  return 1;
}

int bjinit(char *cmdline_file_path) {
  
  char *ini_file_path;
  FILE *ini_file;
  FILE *devrandom;

  // las cosas que pueden ser cero arrancan en menos uno
  blackjack_ini.no_negative_bankroll = -1;
  blackjack_ini.max_bet = -1;
  blackjack_ini.double_after_split = -1;
  blackjack_ini.hit_soft_17 = -1;
  blackjack_ini.max_invalid_commands = -1;
  blackjack_ini.shuffle_every_hand = -1;
        
  // leemos el ini
  ini_file_path = strdup((cmdline_file_path == NULL) ? INI_FILE_PATH : cmdline_file_path);
  if ((ini_file = fopen(ini_file_path, "r")) != NULL) {
    fclose(ini_file);
    if (ini_parse(ini_file_path, fbj_ini_handler, NULL) != 0) {
      return -1;
    }
    if (blackjack.error_level != 0) {
      return -1;
    }
  } else if (cmdline_file_path != NULL) {
    blackjack_push_error_message("cannot open ini file '%s': %s\n", cmdline_file_path, strerror(errno));
    return -1;
  }
  free(ini_file_path);

  // non-zero defaults
  if (blackjack_ini.decks == 0) {  blackjack_ini.decks = 1; }
  if (blackjack_ini.no_negative_bankroll == -1) { blackjack_ini.no_negative_bankroll = 0; }
  if (blackjack_ini.max_bet == -1) { blackjack_ini.max_bet = 0; }
  if (blackjack_ini.double_after_split == -1) { blackjack_ini.double_after_split = 1; }
  if (blackjack_ini.hit_soft_17 == -1) { blackjack_ini.hit_soft_17 = 1; }
  if (blackjack_ini.blackjack_pays == 0) { blackjack_ini.blackjack_pays = 3.0/2.0; }
  if (blackjack_ini.max_invalid_commands == -1) { blackjack_ini.max_invalid_commands = 100; }
  if (blackjack_ini.shuffle_every_hand == -1) { blackjack_ini.shuffle_every_hand = 0; }
  
//  blackjack_inirng_type = gsl_rng_mt19937;
  if (blackjack_ini.penetration == 0) { blackjack_ini.penetration = 0.7; }
  if (blackjack_ini.penetration_sigma ==  0) { blackjack_ini.penetration_sigma = 0.05; }
  
  // si no hay ningun player, creamos uno
  if ((blackjack.current_player = blackjack.players) == NULL) {
    blackjack.current_player = new_player("player");
  }
  
  if (blackjack_ini.rng_seed == 0) {
    assert(devrandom = fopen("/dev/urandom", "r"));
    assert(fread(&blackjack_ini.rng_seed, sizeof(blackjack_ini.rng_seed), 1, devrandom));
    fclose(devrandom);
  }

  // TODO!
  // solo el primer jugador puede salir por tty
  if (blackjack.players->dealer2player.ipc_type == ipc_none) {
    stdout_opts.isatty = isatty(1);
  }
  
  
  if (stdout_opts.isatty && stdout_opts.no_color == 0) {
    strcpy(stdout_opts.black   , "\x1B[0m");
    strcpy(stdout_opts.red     , "\x1B[31m");
    strcpy(stdout_opts.green   , "\x1B[32m");
    strcpy(stdout_opts.yellow  , "\x1B[33m");
    strcpy(stdout_opts.blue    , "\x1B[34m");
    strcpy(stdout_opts.magenta , "\x1B[35m");
    strcpy(stdout_opts.cyan    , "\x1B[36m");
    strcpy(stdout_opts.white   , "\x1B[37m");
    strcpy(stdout_opts.reset   , "\033[0m");    
  }
  
  return 0;
}