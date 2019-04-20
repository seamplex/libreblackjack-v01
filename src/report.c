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
#include "libreblackjack.h"

#include <math.h>
#include <sys/time.h>
#include <sys/resource.h>


int write_yaml_report(player_t *player) {
  FILE *file;
  struct rusage usage;
  double wall;
  double ev, error;
  
  if ((file = blackjack_ini.yaml_report) == NULL) {
    file = stderr;
  }
  
  // TODO: elegir que se agreguen comentarios con explicaciones
  fprintf(file, "---\n");  
  fprintf(file, "rules:\n");
  fprintf(file, "  decks:                  %d\n", blackjack_ini.decks);
  fprintf(file, "  hands:                  %g\n", (double)blackjack.hand);
  fprintf(file, "  hit_soft_17:            %d\n", blackjack_ini.hit_soft_17);
  fprintf(file, "  double_after_split:     %d\n", blackjack_ini.double_after_split);
  fprintf(file, "  blackjack_pays:         %g\n", blackjack_ini.blackjack_pays);
  fprintf(file, "  rng_seed:               %d\n", blackjack_ini.rng_seed);
  fprintf(file, "  number_of_burnt_cards:  %d\n", blackjack_ini.number_of_burnt_cards);
  fprintf(file, "  no_negative_bankroll:   %d\n", blackjack_ini.no_negative_bankroll);
  fprintf(file, "  max_bet:                %d\n", blackjack_ini.max_bet);
  
//  card_t *arranged_cards;
//  FILE *command_log;
  
  if (blackjack_ini.decks > 0) {
    fprintf(file, "  penetration:            %g\n", blackjack_ini.penetration);
    fprintf(file, "  penetration_sigma:      %g\n", blackjack_ini.penetration_sigma);
  }

  // TODO
  if (getrusage(RUSAGE_SELF, &usage) == 0) {
    fprintf(file, "cpu:\n");
    fprintf(file, "  user:             %g\n", usage.ru_utime.tv_sec + 1e-6*usage.ru_utime.tv_usec);
    fprintf(file, "  system:           %g\n", usage.ru_stime.tv_sec + 1e-6*usage.ru_stime.tv_usec);
            
    // medimos wall time final
    gettimeofday(&blackjack.wall_time_final, NULL);
    wall = (blackjack.wall_time_final.tv_sec - blackjack.wall_time_initial.tv_sec) + 1e-6 * (blackjack.wall_time_final.tv_usec - blackjack.wall_time_initial.tv_usec);
    fprintf(file, "  wall:             %g\n", wall);
    
    // velocidad
    fprintf(file, "  second_per_hand:  %.1e\n", wall/blackjack.hand);
    fprintf(file, "  hands_per_second: %.1e\n", blackjack.hand/wall);
    
    
    
  }
  
  fprintf(file, "player: \n");
  if (player != blackjack.players || player->next != NULL) {
    fprintf(file, "  name:       %s\n", player->name);
  }
  fprintf(file, "  wins:               %g\n", (double)player->wins/(double)player->number_of_hands);
  fprintf(file, "  pushes:             %g\n", (double)player->pushes/(double)player->number_of_hands);
  fprintf(file, "  losses:             %g\n", (double)player->losses/(double)player->number_of_hands);
  fprintf(file, "  dealer_blackjacks:  %g\n", (double)player->dealer_blackjacks/(double)player->number_of_hands);
  fprintf(file, "  player_blackjacks:  %g\n", (double)player->player_blackjacks/(double)player->number_of_hands);
  fprintf(file, "  dealer_busts:       %g\n", (double)player->dealer_busts/(double)player->number_of_hands);
  fprintf(file, "  player_busts:       %g\n", (double)player->player_busts/(double)player->number_of_hands);
  fprintf(file, "  doubled_hands:      %g\n", (double)player->doubled_hands/(double)player->number_of_hands);
  fprintf(file, "  doubled_wins:       %g\n", (double)player->doubled_wins/(double)player->number_of_hands);
  fprintf(file, "  insured_hands:      %g\n", (double)player->insured_hands/(double)player->number_of_hands);
  fprintf(file, "  insured_wins:       %g\n", (double)player->insured_wins/(double)player->number_of_hands);
  
  fprintf(file, "  number_of_hands:    %g\n", (double)player->number_of_hands);
  fprintf(file, "  number_of_shuffles: %g\n", (double)blackjack.shuffles);
  fprintf(file, "  total_money_waged:  %g\n", (double)player->total_money_waged);
  fprintf(file, "  worst_bankroll:     %g\n", (double)player->worst_bankroll);
  fprintf(file, "  final_bankroll:     %g\n", (double)player->bankroll);  
  
  // return is a keyword!
//  ev = (double)player->bankroll/player->total_money_waged;
  ev = (double)player->bankroll/(double)blackjack.hand;

//  error = sqrt(player->variance / (double)(player->total_money_waged))
  error = sqrt(player->variance / (double)(blackjack.hand));
  
  fprintf(file, "  return:             %+g\n", ev);
  fprintf(file, "  variance:           % g\n", player->variance);
  fprintf(file, "  deviation:          % g\n", sqrt(player->variance));
  fprintf(file, "  error:              % g\n", sqrt(player->variance / (double)(blackjack.hand)));
  fprintf(file, "  result:             \"(%+.2f ± %.2f) %%\"\n", 100.0*ev, 100*error);
  fprintf(file, "...\n");  
  
  return 0;
}
