/*------------ -------------- -------- --- ----- ---   --       -            -
 *  libreblackjack
 *
 *  Copyright (C) 2016 jeremy theler
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

int count;

int dealer_to_internal(player_t *player, const char *command) {
  
  
  
  return 0;
}


int player_from_internal(player_t *player, char *buffer) {

  snprintf(buffer, BUF_SIZE, "stand");
  
  return 0;
}
