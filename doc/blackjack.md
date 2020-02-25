---
title: LibreBlackjack
subtitle:  A free blackjack back end
desc: a completely free-as-in-freedom blackjack engine designed to study and analyze the game statistics using different playing strategies ranging from simple card counting up to other complex algorithms based on artificial intelligence.
author: Jeremy Theler
date: February 20, 2020
version: v0.1.73-g340abaf+Δ
infoname: blackjack
---

# Overview

include(overview.md)

# Running `libreblackjack`

## Invocation

```{=texinfo}
The format for running the @command{libreblackjack} program is:

@example
libreblackjack @var{options} @var{path_to_conf_file}
@end example

If no configuration file is given, a file named @file{blackjack.conf} in the current directory is used, provided it exists.
With no options and no configuration file, `libreblackjack` starts in interactive mode and
it is ready to start a blackjack game.

@command{libreblackjack} supports the following options:

@table @option
@item --hands=number
@itemx -h number
Specify the number of hands to play.

@item --decks=number
@itemx -d number
Specify the number of decks to use in the shoe.

@item --flatbet
@itemx -f
Do not ask for the amount to bet before starting a new hand and use a flat unit bet.

@item --internal
@itemx -i
Use the internal player to play against itself.

@item --help
@itemx -h
Print an informative help message on standard output and exit
successfully.

@item --version
@itemx -v
Print the version number and licensing information of Hello on
standard output and then exit successfully.

@end table
```

## Interactive game

## Automated playing


# Configuration file

include(conf.md)

# Commands





# Example automated players

include(players.md)



