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
#include "version-vcs.h"

#include <string.h>

#define ENGINE  "a free & open blackjack engine\n"

void
libreblackjack_shortversion (void)
{

#ifdef LIBREBLACKJACK_VCS_BRANCH
  printf ("libreblackjack %s%s %s\n", LIBREBLACKJACK_VCS_VERSION,
	  (LIBREBLACKJACK_VCS_CLEAN == 0) ? "" : "+Δ",
	  strcmp (LIBREBLACKJACK_VCS_BRANCH,
		  "master") ? LIBREBLACKJACK_VCS_BRANCH : "");
#else
  printf ("libreblackjack %s\n", PACKAGE_VERSION);
#endif

  printf (_(ENGINE));
  return;
}

void
libreblackjack_help (char *program_name)
{
  printf (_("Usage: %s [options] [path_to_conf_file]\n"), program_name);
  printf (_(ENGINE));

  printf (_("\n"));
  printf (_
	  ("If no configuration file is given, a file named blackjack.conf\n"));
  printf (_("in the current directory is used, provided it exists.\n"));
  printf (_
	  ("See the full documentation for the available options and the default values.\n"));

  printf (_("\n"));
  printf (_
	  ("  -h, --hands=N    set the number of hands to play before quiting\n"));
  printf (_("  -d, --decks=N    set the number of decks to use\n"));
  printf (_
	  ("  -f, --flatbet    do not ask for the bet before each hand, use a unit flat bet\n"));
  printf (_
	  ("  -i, --internal   use the internal player to play against the dealer (not interactive)\n"));
  printf (_("\n"));
  printf (_("  -h, --help       display this help and exit\n"));
  printf (_("  -v  --version    output version information and exit\n"));

  return;
}


void
libreblackjack_copyright (void)
{
  printf (_("\
copyright (c) %s jeremy theler.\n\
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>\n\
This is free software: you are free to change and redistribute it.\n\
There is NO WARRANTY, to the extent permitted by law.\n\n"), "2016--2020");
  return;
}
