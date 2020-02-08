
---
title: Mimic the dealer
...

# Mimic the dealer

> Difficulty: 08/100

This example implements a “mimic-the-dealer strategy,” i.e. hits if the hand totals less than seventeen and stands on eighteen or more. The player stands on hard seventeen but hits on soft seventeen. 

This time, the configuration of the game is read from an ini file called `libreblackjack.ini`. In general, if this file exists in the directory where libreblackjack is executed, it is read and parsed. The options should be fairly self descriptive. See the documentation for a detailed explanation of the options that can be entered in the ini file. In particular, we ask to play one hundred thousand hands at a six-deck game where the dealer hits soft seventeens. If the random seed is set to a fixed value so each execution will lead to the very same sequence of cards.

Now, there are two options that tell libreblackjack how is the player going to talk to the backend: `player2dealer` and `dealer2player`. The first one sets the communication mechanism from the player to the dealer (by default is libreblackjack's standard input), and the second one sets the mechanism from the dealer to the player (by default libreblackjack's standard output). In this case, the ini file reads:

```
player2dealer = fifo player2dealer
dealer2player = fifo dealer2player
```

This means that two FIFOs (a.k.a. named pipes) are to be used for communication, `player2dealer` from the player to the dealer and `dealer2player` for the dealer to the player. If these FIFOs do not exist, they are created by libreblackjack upon execution. 

The player this time is implemented as an awk script, whose input should be read from `dealer2player` and whose output should be written to `player2dealer`. To run the game, execute libreblackjack in one terminal making sure the current directory is where the `libreblackjack.ini` file exists. It should print a message telling that it is waiting for someone to be at the other side of the named pipes:

```
../../libreblackjack
[...]
waiting for dealer2player buffered fifo 'dealer2player'...
```

In another terminal run the player

```
./mimic-the-dealer.awk < dealer2player > player2dealer
```

Both dealer and player may be run in the same terminal putting the first one on the background:

```
if [ -z "`which gawk`" ]; then
  echo "error: gawk is not installed"
  exit 1
fi      

rm -f mimic_d2p mimic_p2d
mkfifo mimic_d2p mimic_p2d
libreblackjack &
./mimic-the-dealer.awk < mimic_d2p > mimic_p2d
```

To understand the decisions taken by the player, we have to remember that when libreblackjack receives the command `count` asking for the current player's count, it returns a positive number for hard hands and a negative number for soft hands. The instructions `fflush()` are needed in order to avoid deadlocks on the named pipes:

```awk
#!/usr/bin/gawk -f
function abs(x){return ( x >= 0 ) ? x : -x } 

/bet\?/ {
  print "1";
  fflush();
}

/insurance\?/ {
  print "no";
  fflush();
}

/play\?/ {
  count = $2
  # mimic the dealer: hit until 17 (hit soft 17)
  if (abs(count) < 17 || count == -17) {   # soft hands are negative
    print "hit";
  } else {
    print "stand";
  }
  fflush();  
}

/bye/ {
  exit;
}
```

> Exercise: modify the player and the ini file so both the dealer and the player may stand on soft seventeen. Analyze the four combinations (player h17 - dealer h17, player h17 - dealer s17, player s17 - dealer h17, player s17 - dealer s17)

-------
:::{.text-center}
[Previous](../05-no-bust) | [Index](../) | [Next](../20-basic-strategy)
:::
