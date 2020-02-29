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


`-h number`  or `--hands=number`

:   Specify the number of hands to play. Corresponds to the `hands` variable in the [configuration file].


`-d number` or `--decks=number`

:   Specify the number of decks to use in the shoe. Corresponds to the `decks` variable in the [configuration file].


`--flatbet`

:   Do not ask for the amount to bet before starting a new hand and use a flat unit bet.


`-i` or `--internal`

:   Use the internal player to play against itself. See [internal player] for details.


`-h` or `--help`

:   Print this informative help message on standard output and exit successfully.


`-v` or `--version`

:   Print the version number and licensing information of Hello on standard output and then exit successfully.


## Interactive game

## Internal player 

## Automated playing through IPC

### Standard input/output

### FIFOs

### POSIX message queues

### POSIX shared memory objects synchronized with semaphores

### TCP (through `netcat`)

# Configuration file

include(conf.md)

# Commands





# Example automated players

dnl include(players.md)



