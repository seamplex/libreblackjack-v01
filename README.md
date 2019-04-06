# LibreBlackjack

> A [free](https://www.gnu.org/philosophy/free-sw.html) [Blackjack](https://en.wikipedia.org/wiki/Blackjack) back-end inspired by [GNU Chess](https://www.gnu.org/software/chess/).

[LibreBlackjack](https:/www.seamplex.com/libreblackjack) is a blackjack engine that emulates a dealer, deals cards and understands commands such as `hit` or `stand`. The basic idea is that one or more players can talk to LibreBlackjack either in an interactive or automated way through
 
 * the standard input,
 * named pipes,
 * POSIX message queues,
 * TCP (web)sockets (using netcat or gwsocket), or
 * dynamically loaded from shared objects.
  
These players can be actual human players playing in real-time through a front-end (a GUI application, a web-based interface, a mobile app, etc.) or robots that implement a certain betting and playing strategy playing (i.e. card counting) as fast as possible to study and analyze game statistics. There is an internal player that reads the strategy from a text file and plays accordingly. It can also be used to play [#play](ASCII blackjack).

## Why

> I am often surprised that when people drive down two-lane roads, they will trust complete strangers in the oncoming lane not to swerve into their lane causing a head-on collision; but they will not trust mathematicians to create the correct strategy for Blackjack.
>
> _Norman Wattenberger, Modern Blackjack, 2009_

With LibreBlackjack you do not have to trust other people anymore. You have a free blacjack engine which you can

 0. run as you wish, to see the results of billions of blackjack hands,
 1. study to see how it works and change it if you do not like it,
 2. share it with your friends and colleagues, and
 3. distribuite copies of your modified versions.

If you do not know how to program, you have the _freedom_ to hire a programmer to do it for you. That is why [LibreBlackjack](https:/www.seamplex.com/libreblackjack) is [free software](https://www.gnu.org/philosophy/free-sw.html).


## How 

Once you trust the blackjack engine is fair, you can model and simulate any blackjack situation you want, playing millions of times a certain hand (say a sixteen against a ten) in different ways (say hitting or standing) to obtain you own conclusions. You can even build  the [basic strategy charts](https://wizardofodds.com/games/blackjack/strategy/4-decks/) from scratch to convince yourself there is no [flaw](https://wizardofodds.com/ask-the-wizard/blackjack/).

The main objective is research and optimization of playing and betting strategies depending on

 * particular table rules (number of decks, hit on soft 17, double after split, etc.), 
 * card counting strategies 
 * risk of ruin
 * removal of cards
 * arranged shoes
 
These automatic players can range from simple no-bust or mimic-the-dealer hitters or standers, up to neural-networks trained players taking into account every card being dealt passing through basic strategy modified by traditional card counting mechanisms.

# Quick start


```
git clone git@github.com:seamplex/libreblackjack.git
cd libreblackjack
./autogen.sh
./configure
make
sudo make install
```

Note that LibreBlackjack depends on two optional GNU libraries:

 * [GNU Scientific Library](https://www.gnu.org/software/gsl/) for an improved random number generator
 * [GNU Readline](http://tiswww.case.edu/php/chet/readline/rltop.html) for an improved interactive stdin prompt


## Test suite

Run as test suite to check the code work as expected.

```
$ make check
```

The subdirectory `players` contains some automatic players that play against LibreBlackjack. These players are coded in different languages and communicate with LibreBlackjack in a variery of ways in order to illustrate the design basis:

 * `00-internal-player` uses the internal player that defaults to playing one million hands of basic strategy
 * `02-always-stand`, using the UNIX tool `yes` this player always says “stand” into the standard output (which is piped to libreblackjack’s standard input) no matter what the cards are
 * `05-no-bust` is a PERL-based player does not bust (i.e. hits if the hard total is less than twelve) that receives tha cards through the standard input but draws or stands using a FIFO to talk back to the dealer
 * `08-mimic-the-dealer` does tha same the dealer do (hits soft seventeens). It is implemented in AWK using two FIFOs.


# Play

Run LibreBlackjack with no arguments to play Blackjack interactively in ASCII mode

![ASCII playing](doc/ascii.png){.img-responsive}\ 

Edit the file `libreblackjack.ini` to set up rules, arranged shoes and other options. Type `help` at the prompt to get it.

# Automatic playing

See the directory `players` for examples of how to write players in

 * a pure UNIX way using the `yes` tool
 * Perl
 * Awk
 * Python
 * C
 
## TCP Sockets

To play through a TCP socket, call `libreblackjack` from `netcat`. On one host, do

```
nc -l -p1234 -e libreblackjack
```

On the other one, connect to the first host on port 1234:

```
nc host 1234
```

# Licensing

LibreBlackjack is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.

# Further information

Home page: <https://www.seamplex.com/libreblackjack>  
Repository: <https://github.com/seamplex/libreblackjack>  
Mailing list and bug reports: <wasora@seamplex.com>  (you need to subscribe first at <wasora+subscribe@seamplex.com>)  
Follow us: [Twitter](https://twitter.com/seamplex/) [YouTube](https://www.youtube.com/channel/UCC6SzVLxO8h6j5rLlfCQPhA) [LinkedIn](https://www.linkedin.com/company/seamplex/) [Bitbucket](https://bitbucket.org/seamplex/)

----------------------------------------------------

libreblackjack is copyright (C) 2016,2019 Jeremy Theler  
libreblackjack is licensed under [GNU GPL version 3](http://www.gnu.org/copyleft/gpl.html) or (at your option) any later version.  
libreblackjack is free software: you are free to change and redistribute it.  
There is NO WARRANTY, to the extent permitted by law.  
See the file [`COPYING`](https://bitbucket.org/seamplex/libreblackjack/src/default/COPYING) for copying conditions.  
