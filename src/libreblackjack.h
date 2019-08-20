/*------------ -------------- -------- --- ----- ---   --       -            -
 *  libreblackjack
 *
 *  Copyright (C) 2016,2019 Jeremy Theler
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
#ifndef _LIBREBLACKJACK_H_
#define _LIBREBLACKJACK_H_

#ifdef HAVE_LIBGSL
 #include <gsl/gsl_types.h>
 #include <gsl/gsl_rng.h>
 #include <gsl/gsl_randist.h>
#endif 

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <mqueue.h>


// https://github.com/troydhanson/uthash
#include "utlist.h"

#define bjcall(function)   if ((function) != 0) return -1
#define bjcallpop(function)   if ((function) <= 0) { blackjack_pop_errors(); return 1; }

#define INI_FILE_PATH "libreblackjack.ini"

// char base64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";

#define START_NEW_HAND                          10
#define ASK_FOR_BETS                            20
#define DEAL_PLAYERS_FIRST_CARD                 30
//#define DEAL_DEALERS_UP_CARD                  40
//#define DEAL_PLAYERS_SECOND_CARD              50
#define DEAL_DEALERS_HOLE_CARD                  60
#define ASK_FOR_INSURANCE                       70
#define CHECK_FOR_BLACKJACKS                    80
#define PAY_OR_TAKE_INSURANCE_BETS              90
#define ASK_FOR_PLAY                           100
#define MOVE_ON_TO_NEXT_HAND                   105
#define HIT_DEALERS_HAND                       110
#define PAYOUT                                 120

#define NONE       0
#define BET        1
#define INSURANCE  2
#define PLAY       3


typedef struct player_t player_t;
typedef struct hand_t hand_t;
typedef struct card_t card_t;
typedef struct ipc_t ipc_t;

#define BUF_SIZE 256
char outputbuffer[BUF_SIZE];
char inputbuffer[BUF_SIZE];

struct ipc_t {
  char *name;
  
  enum {
    ipc_none,
    ipc_fifo,
    ipc_shmem,
    ipc_mqueue,
    ipc_internal,
  } ipc_type;

  int buffered;

  int fd;
  FILE *fp;  
  
  char *shmem;
  sem_t *sem_written;
  sem_t *sem_read;

  mqd_t mq;  
};

struct {
  // rules
  int decks;                     // -1 for infinite
  unsigned long int hands;       // max hands (read from ini or commandline)
  int rng_seed;                  // zero = read from /dev/urandom
  int number_of_burnt_cards;     // number of burnt cards after shuffling
  int no_negative_bankroll;      // do not allow negative bankrolls
  int max_bet;
  int double_after_split;
  int hit_soft_17;
  int max_invalid_commands;
  int shuffle_every_hand;
  
  card_t *arranged_cards;
  FILE *log;
  FILE *yaml_report;
  
  double penetration;
  double penetration_sigma;
  double blackjack_pays;
  double error_standard_deviations;
  
} blackjack_ini;


#define CARD_ART_LINES 6
#define CARD_TYPES     5
#define CARD_SIZE      16

struct card_t {
  int tag;
  int value;

  char token[CARD_TYPES][CARD_SIZE];  
  char text[32];  
  char art[CARD_ART_LINES][CARD_SIZE];
  
  card_t *next;
};

struct {
  
  unsigned long int hand;                      // actual hand number (splits are counted as a single hand)
  unsigned long int shuffles;                  // number of shuffles
  unsigned int infinite_decks_card_number_for_arranged_ones;
  unsigned int next_dealer_action;
  unsigned int players_input_needed;
  unsigned int current_card_index;
  unsigned int cut_card_index;
  unsigned int holecard_shown;
  unsigned int last_pass;
  unsigned int done;
  
  unsigned int n_arranged_cards;
  int *arranged_cards_array;
  
//  card_t *card;
  card_t card[53];
  int *shoe;  
  
  player_t *players;
  player_t *current_player;
  
  hand_t *dealer_hand;
  card_t *dealer_holecard;
  
  struct timeval wall_time_initial;
  struct timeval wall_time_final;
  
  char **error;
  unsigned int error_level;
  
#ifdef HAVE_LIBGSL
  gsl_rng_type *rng_type;
  gsl_rng *rng;  
#else
  void *rng;
#endif  

} blackjack;

struct {
  int isatty;
  int no_color;
  int no_utf8;
  int ascii_art;
    
  char black[8];
  char red[8];
  char green[8];
  char yellow[8];
  char blue[8];
  char magenta[8];
  char cyan[8];  
  char white[8];
  char reset[8];
} stdout_opts;

struct player_t {
  char *name;
  
  hand_t *hands;
  hand_t *current_hand;

  double current_result;  
  double mean;
  double M2;
  double variance;
  
  int has_split;
  int doubled;
  int busted_all_hands;
  
  int flat_bet;
  int no_insurance;
  int always_insure;
  double bankroll;
  double delay;
  
  enum {
    card_utf8,        // one ascii char for the rank and one utf8 representation of the suit ♠,♥,♦,♣
    card_utf8_single, // a single utf8 entity for the card 
    card_ascii,       // two ascii chars, one for the rank A,2,...,T,J,Q,J and one for the suit S,H,D,C
    card_value,       // the value for the game, A = 11, J,Q,K=10 or ran
    card_tag,         // integer between 1--52: tag = 13*suit + rank
  } token_type;

  
  ipc_t dealer2player;
  ipc_t player2dealer;

  int (*write)(player_t *, const char *);
  int (*read)(player_t *, char *);
  
  // statistics
  unsigned long int number_of_hands;
  unsigned long int total_money_waged;
  double worst_bankroll;
  
  unsigned long int dealer_blackjacks;
  unsigned long int player_blackjacks;
  
  unsigned long int dealer_busts;
  unsigned long int player_busts;

  unsigned long int wins;
  unsigned long int blackjack_wins;
  unsigned long int plain_wins;
  unsigned long int pushes;
  unsigned long int losses;
  
  unsigned long int doubled_hands;
  unsigned long int doubled_wins;
  
  unsigned long int insured_hands;
  unsigned long int insured_wins;
  
  
  player_t *next;
};

struct hand_t {
  int id;
  int bet;
  
  int n_cards;
  int soft;
  int blackjack;
  int insured;
  int busted;
  int count;
  
  card_t *cards;

  hand_t *next;
};



// cards.c
extern void print_card_art(card_t *card);
extern void print_hand_art(hand_t *hand);
extern void print_card_unicode(card_t *card);
extern void print_card_text(card_t *card);
extern int compute_count(hand_t *hand);
extern int deal_card(void);
extern card_t *deal_card_to_hand(hand_t *hand);
//extern hand_t *new_hand(hand_t **hands, int id, int bet);
extern void destroy_hands(hand_t **hands);
extern void init_card(int tag, int number, int suit);

extern void init_shoe(void);
extern void shuffle_shoe(void);

// dealer.c
extern int dealer_action(void);
extern int dealer_process_input(player_t *player, char *command);

// stdinout.c
extern int dealer_to_stdout(player_t *, const char *command);
extern int player_from_stdin(player_t *, char *buffer);
extern void free_rl_stdin(void);

// bjinit.c
extern player_t *new_player(const char *name);
extern void destroy_player(player_t *player);
extern player_t *get_player(const char *name);
extern player_t *get_or_define_player(const char *name);
extern player_t *player_from_section(const char *section);
extern int bjinit(char *cmdline_file_path);
int fbj_ini_handler(void* user, const char* section, const char* name, const char* value);

// commands.c
extern int write_formatted_card(player_t *player, int dealer, char *command, card_t *card);
extern int write_formatted(player_t *player, const char *fmt, ...);

// fifo.c
int create_fifo(const char *name);
int dealer_to_fifo(player_t *player, const char *command);
int player_from_fifo(player_t *player, char *buffer);
// version.c
void libreblackjack_shortversion(void);
void libreblackjack_copyright(void);

// report.c
int write_yaml_report(player_t *player);

// error.c
void blackjack_push_error_message(const char *fmt, ...);
void blackjack_pop_error_message(void);
void blackjack_pop_errors(void);
void blackjack_signal_handler(int sig_num);

// shmem.c

int create_shmem(const char *name, char **pointer, sem_t **sem_written, sem_t **sem_read);
int dealer_to_shmem(player_t *player, const char *command);
int player_from_shmem(player_t *player, char *buffer);


// mqueue.c
int create_mqueue(const char *name, mqd_t *mq);
int dealer_to_mqueue(player_t *player, const char *command);
int player_from_mqueue(player_t *player, char *buffer);

// internal.c
extern int dealer_to_internal(player_t *player, const char *command);
extern int player_from_internal(player_t *player, char *buffer);

#endif
