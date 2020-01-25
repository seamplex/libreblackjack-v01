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
#include "libreblackjack.h"

#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/time.h>

int main(int argc, char** argv) {
  
  int i, optc;
  int option_index = 0;
  int show_help = 0;
  int show_version = 0;
  int show_bar = 0;
  int bar_already_alloced = 0;
  int hands_per_char = 0;
  unsigned long int last_hand_per_char = 0;
  int current_invalid_command = 0;
  char *argument_for_ini;
  char *equal_sign;
  
 
  player_t *player;
  player_t *tmp;  // for FOR_EACH_SAFE

  const struct option longopts[] = {
    { "help",        no_argument,       NULL, 'h'},
    { "version",     no_argument,       NULL, 'v'},
    { "decks",       required_argument, NULL, 'd'},
    { "hands",       required_argument, NULL, 'n'},
    { "internal",    no_argument,       NULL, 'i'},
    { "flatbet",     optional_argument, NULL, 'f'},
    { NULL, 0, NULL, 0 }
  };    

  setlocale (LC_ALL, "");
  bindtextdomain (PACKAGE,  "/usr/share/locale/");
  textdomain (PACKAGE);

  opterr = 0;
  while ((optc = getopt_long_only(argc, argv, "hvd:n:if:", longopts, &option_index)) != -1) {
    switch (optc) {
      case 'h':
        show_help = 1;
        break;
      case 'v':
        show_version = 1;
        break;
      case 'd':
        bjcallpop(fbj_ini_handler("decks", optarg));
        break;
      case 'n':
        bjcallpop(fbj_ini_handler("hands", optarg));
        break;
      case 'i':
        bjcallpop(fbj_ini_handler("player2dealer", "internal"));
        bjcallpop(fbj_ini_handler("dealer2player", "internal"));
        bjcallpop(fbj_ini_handler("flat_bet", "1"));
        bjcallpop(fbj_ini_handler("no_insurance", "1"));
        break;
      case 'f':
        if (optarg != NULL) {
          bjcallpop(fbj_ini_handler("flat_bet", optarg));
        } else {
          bjcallpop(fbj_ini_handler("flat_bet", "1"));
        }
        break;
      case '?':
        argument_for_ini = strdup(argv[optind-1]);
        if ((equal_sign = strchr(argument_for_ini, '=')) == NULL) {
          if (fbj_ini_handler(argument_for_ini+2, "") <= 0) {
            fprintf(stderr, _("Unkown option '%s'.\n"), argument_for_ini);
            fprintf(stderr, _("Try '%s --help' for more information.\n)"), argv[0]);
            return 1;
          }
        } else {
          *equal_sign = '\0';
          if (fbj_ini_handler(argument_for_ini+2, equal_sign+1) <= 0) {
            fprintf(stderr, _("Unkown option '%s'.\n"), argument_for_ini);
            fprintf(stderr, _("Try '%s --help' for more information.\n"), argv[0]);
            return 1;
          }
        }
        free(argument_for_ini);
        break;
      default:
        break;
    }
  }  
  
  if (show_version) {
    libreblackjack_shortversion();
    libreblackjack_copyright();
  }
  if (show_help) {
    // TODO
    printf("help\n");
  }
  
  if (show_version || show_help) {
    return 0;
  }

  // medimos wall time inicial
  gettimeofday(&blackjack.wall_time_initial, NULL);
  
  // si nos quedaron argumentos sin procesar, es el ini
  if (optind == argc) {
    if (bjinit(NULL) != 0) {
      blackjack_pop_errors();
      return 1;
    }
  } else {
    if (bjinit(argv[optind]) != 0) {
      blackjack_pop_errors();
      return 1;
    }
  }

  // TODO: ver  
  if (stdout_opts.isatty) {
    libreblackjack_shortversion();
    libreblackjack_copyright();
  }
  
  blackjack.next_dealer_action = START_NEW_HAND;
  blackjack.last_pass = 1;
  
  // TODO: revisar/elegir por ini
//  setvbuf(stdout, NULL, _IONBF, 0);
  setlinebuf(stdout);
  
  // TODO: elegir, poner opcion -q (y --verbose)
  if (blackjack.players->dealer2player.ipc_type != ipc_none) {
    if (blackjack_ini.hands != 0) {
      show_bar = 1;
      hands_per_char = blackjack_ini.hands/50;
    }
  }
  
  while (!blackjack.done) {

    // por default hacemos que no se necesite feedback
    // si no se necesita feedback, en dealer_action seteamos next_action
    // si se necesita feedback, en process_player_input se setea el next_action
    // asi podemos chequear que el feedback que pedimos es valido
    blackjack.players_input_needed = NONE;
    
    // limpiamos el output buffer (se usa para re-preguntar cuando es invalida la entrada)
    outputbuffer[0] = '\0';
    current_invalid_command = 0;

    if (dealer_action() != 0) {
      blackjack_pop_errors();
      return 1;
    }
    
    if (show_bar != 0) {
      if (blackjack.hand == 2 && bar_already_alloced == 0) {
        printf("\n");
        for (i = 0; i < 50; i++) {
          printf("-");
        }
        for (i = 0; i < 50; i++) {
          printf("\b");
        }
        bar_already_alloced = 1;
        fflush(stdout);
      }
      if ((blackjack.hand - last_hand_per_char) > hands_per_char) {
        printf("=");
        fflush(stdout);
        last_hand_per_char = blackjack.hand;
      }
    }
 
    if (blackjack.players_input_needed != NONE) {
      do {
        
        if (outputbuffer[0] != '\0') {
          if (blackjack.current_player->write(blackjack.current_player, outputbuffer) != 0) {
            blackjack_pop_errors();
            return 1;
          }
          
          if (blackjack_ini.log != NULL) {
            fprintf(blackjack_ini.log, "-> %s\n", outputbuffer);
            fflush(blackjack_ini.log);
          }
        }
        
        if (blackjack.current_player->read(blackjack.current_player, inputbuffer) != 0) {
          blackjack_pop_errors();
          return 1;
        }
        if (blackjack_ini.log != NULL) {
          fprintf(blackjack_ini.log, "<- %s\n", inputbuffer);
          fflush(blackjack_ini.log);
        }
        
        if (blackjack_ini.max_invalid_commands != 0 && current_invalid_command++ > blackjack_ini.max_invalid_commands) {
          blackjack.current_player->write(blackjack.current_player, "max_incorrect_commands");
          blackjack_push_error_message(_("reached the maximum number of allowed incorrect commands (%d)"), blackjack_ini.max_invalid_commands);
          blackjack_pop_errors();
          blackjack.current_player->write(blackjack.current_player, "bye");
          exit(1);
        }
      } while (dealer_process_input(blackjack.current_player, inputbuffer) <= 0);
    }
  }

  if (show_bar) {
    printf("=\n\n");
  }
  
  // cleanup
  LL_FOREACH_SAFE(blackjack.players, player, tmp) {
    blackjack.current_player->write(player, "bye");
    write_yaml_report(blackjack.players);
    destroy_player(player);
  }
  destroy_hands(&blackjack.dealer_hand);
  free_rl_stdin();
  free(blackjack.shoe);
  if (blackjack_ini.log != NULL) {
    fclose(blackjack_ini.log);
  }
#ifdef HAVE_LIBGSL
  gsl_rng_free(blackjack.rng);
#endif
  
  
 
  return (EXIT_SUCCESS);
}

