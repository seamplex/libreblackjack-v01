---
title: Libre Blackjack
subtitle:  A free blackjack back end
desc: a completely free-as-in-freedom blackjack engine designed to study and analyze the game statistics using different playing strategies ranging from simple card counting up to other complex algorithms based on artificial intelligence.
author: Jeremy Theler
date: February 20, 2020
version: v0.1.73-g340abaf+Δ
infoname: blackjack
---

# Overview

include(overview.md)

# Running `blackjack`

## Invocation

The format for running the `blackjack` program is:

```
blackjack [options] [path_to_conf_file]
```

If no configuration file is given, a file named `blackjack.conf` in the current directory is used, provided it exists.
With no options and no configuration file, `blackjack` starts in interactive mode and it is ready to start a blackjack game.

The `blackjack` executable supports the following options:


include(help.md)


## Interactive game



# Commands

The dealer (he) and the player (she) “talk” through commands, which are ASCII strings sent through any of the different IPC mechanisms discussed in [Automated playing through IPC]. In the most basic case, a human player reads commands from the dealer from `blackjack`’s  standard output and writes her commands into the dealer’s standard input. Those commands from the dealer that require a particular action from the player end with a quotation sign such as `bet?`, `insurance?` or `play?`.

All numerical values such as hand totals or bankrolls are given as decimal ASCII strings.

## From the dealer to the player


## From the player to the dealer

The following commands are available for the player for playing her hand.

include(input-particular.md)


The following are general commands in the sense that they can be sent from the player to the dealer at any moment of the game.

include(input-general.md)





# Configuration file

Libre Blackjacks reads a configuration file that contains
 
 * settings about the rules of the game
    - number of decks,
    - whether if the dealer has to hit soft seventeen or not,
    - blackjack payout,
    - maximum bet allowed,
    - etc...
 * how the player is supposed to play
    - number of hands
    - whether a flat or variable bet is going to be used,
    - etc...
 * if there are any particular shoe arrangement, i.e. a predefined set of cards dealt in a certain order for instance to play one million hands of a sixteen against a dealer’s ten
 * what kind of information is shown in the interactive session
    - if ASCII-art cards are supposed to be shown,
    - a real-time delay to make the game smoother,
    - etc.
 * how the automated player communicates with the dealer
    - using standard input/output,
    - FIFO named pipes,
    - POSIX message queues,
    - POSIX shared memory,
    - etc...
 
The location of the configuration file can be given in the command line. If none is provided, a file named `blackjack.conf` in the current directory is used. If such file does not exists, the defaults values of each variable are used. Individual variables can be set from the command line by passing one or more times the option `--`configuration_variable`[=`*value*`]` in the [invocation].

Comments can be inserted using either a hash `#` or a colon `;`. The following configuration file is the default provided in the main distribution tarball:

```ini
# Default Libre Blackjack configuration file

card_format = utf8_single   # either utf8, utf8_single, ascii, value or tag  
# utf8,         one ascii char for the rank and one utf8 representation
#               of the suit ♠,♥,♦,♣
# utf8_single,  a single utf8 entity for the card, i.e. 🃞 🃊 🃗 🂱 ...
# ascii,        two ascii chars, one for the rank A,2,...,T,J,Q,J
#               and one for the suit S,H,D,C
# value,        the value for the game, A = 11, J,Q,K=10 or face number
# tag,          integer between 1-52, suit between 0-3,
#               rank between 1-13: tag = 13*suit + rank

# uncomment the following line to arrange cards
# arranged_cards = 1 5 14 9 27

flat_bet = 1       # do not ask for bets
no_insurance = 1   # do not ask for insurance
decks = 1          # number of decks, negative means infinite
```

## Variables and values

include(conf.md)



# Results

## Rules

## CPU

## Player




## Automatic internal player

## Automated playing through IPC

### Standard input/output

### FIFO named pipes

### POSIX message queues

### POSIX shared memory objects

### TCP (through `netcat`)


# Example automated players

The directory `players` contains a few examples of automated player, which are discussed in the following sections. A script `check.sh` runs some of them and compares the expected value of the bankroll relative to the number of hands which each player obtains with the theoretical expected value (according to the game rules and player’s strategy) within an  allowed statistical uncertainty. This scripts writes the following table (actual values might vary depending on the random nature of the game):

include(../players/check.md)

The columns are

 1. Case name, as discussed below.
 2. Expected theoretical result in absolute units (i.e. -0.004 means -0.4%)
 3. Actual result obtained by Libre Blackjack in absolute units
 4. Estimated error equal to the standard deviation of the result
 5. Number of played hands per second
 6. Whether the result coincides or not with the theoretical value


include(players.md)



