## No-bust strategy

> Difficulty: 05/100

This directory shows how to play a “no-bust” strategy, i.e. not hitting any hand higher or equal to hard twelve with libreblackjack. The communication between the player and the backend is through standard input and output. The player reads from its standard input libreblackjack's commands and writes to its standard output the playing commands. In order to do this a FIFO (a.k.a. named pipe) is needed. So first, we create it (if it is not already created):

```
$ mkfifo fifo
```

Then we execute libreblackjack, piping its output to the player (say `no-bust.pl`) and reading the standard input from `fifo`, whilst at the same time we redirect the player's standard output to `fifo`:

```
../../libreblackjack -n1e5 < fifo | ./no-bust.pl > fifo
```

As this time the player is coded in an interpreted langauge, it is far smarter than the previous `yes`-based player. So the player can handle bets and insurances, and there is not need to pass the options `--flat_bet` nor `--no_insurance` (though they can be passed anyway). Let us take a look at the Perl implementation:

```
#!/usr/bin/perl
# this is needed to avoid deadlock with the fifo
STDOUT->autoflush(1);

while ($command ne "bye") {
  # do not play more than a number of commands
  # if the argument -n was not passed to libreblackjack
  if ($i++ == 123456789) {
    print "quit\n";
    exit;
  }
  
  # read and process the commands
  chomp($command = <STDIN>);
  
  if ($command eq "bet?") {
    print "1\n";
  } elsif ($command eq "insurance?") {
    print "no\n";
  } elsif ($command eq "play?") {
    print "count\n";
    chomp($count = <STDIN>); # the count
    chomp($play = <STDIN>);  # again the "play?" query
    if ($count < 12) {
      print "hit\n";
    } else {
      print "stand\n";
    }
  }
}
```

The very same player may be implemented as a shell script:

```
#!/bin/sh

while command=`line`
do
  if test "${command}" = 'bye'; then
    exit
  elif test "${command}" = 'bet?'; then
    echo 1  
  elif test "${command}" = 'insurance?'; then
    echo "no"
  elif test "${command}" = 'play?'; then
    echo "count"
    count=`line`
    play=`line`      # libreblackjack will ask again for 'play?'
    if test ${count} -lt 12; then
      echo "hit"
    else
      echo "stand"
    fi
  fi
done
```

To check these two players give the same results, make them play agains libreblackjack with the same seed (say one) and send the YAML report to two different files:

```
$ ../../libreblackjack -n1e3 --rng_seed=1 --yaml_report=perl.yml  < fifo | ./no-bust.pl > fifo
$ ../../libreblackjack -n1e3 --rng_seed=1 --yaml_report=shell.yml < fifo | ./no-bust.sh > fifo
$ diff perl.yml shell.yml 
15,17c15,17
< cpu_user:               0.024
< cpu_system:             0.024
< cpu_wall:               0.095334
---
> cpu_user:               0.06
> cpu_system:             0.04
> cpu_wall:               5.64883
```

As expected, the reports are the same. They just differ in the wall time because the shell script is orders of magnitude slower than its Perl-based counterpart. 

> Exercise: modifiy the players so they always insure aces and see if it improves or degrades the result.
