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

## Internal player 

## Automated playing through IPC

### Standard input/output

### FIFO named pipes

### POSIX message queues

### POSIX shared memory objects synchronized with semaphores

### TCP (through `netcat`)

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
 
The location of the configuration file can be given in the command line. If none is provided, a file named `blackjack.conf` in the current directory is used. If such file does not exists, the defaults values of each variable are used. Individual variables can be set from the command line by passing one or more times the option `--`configuration_variable`[=`*value*`]` in the [invocation].

include(conf.md)

# Commands





# Example automated players

include(players.md)



