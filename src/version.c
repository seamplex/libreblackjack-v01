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
#include "version.h"

#include <string.h>

void libreblackjack_shortversion(void) {
  // TODO: gettext & version from hg

#ifdef LIBREBLACKJACK_VCS_BRANCH
  printf("libreblackjack %s.%s %s (%s%s %s)\n", LIBREBLACKJACK_VCS_MAJOR, LIBREBLACKJACK_VCS_MINOR,
                                      strcmp(LIBREBLACKJACK_VCS_BRANCH, "default")?LIBREBLACKJACK_VCS_BRANCH:"",
                                      LIBREBLACKJACK_VCS_SHORTID,
                                      (LIBREBLACKJACK_VCS_CLEAN==0)?"":"+Δ",
                                      LIBREBLACKJACK_VCS_DATE);
#else
  printf("libreblackjack %s\n", PACKAGE_VERSION);
#endif

  printf("a free & open blackjack engine\n");
  return;
}


void libreblackjack_copyright(void) {
  printf("\
copyright (c) %s jeremy theler.\n\
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>\n\
This is free software: you are free to change and redistribute it.\n\
There is NO WARRANTY, to the extent permitted by law.\n\n",
             "2016" );
  return;
}