define(case_title, Always stand)
---
title: case_title
...

# case_title

> Difficulty: case_difficulty/100

To play libreblackjack as an “always-stander” run the following command:

```
input(run.sh)dnl
```

The UNIX command `yes stand` writes the string “stand” repeteadly to the standard output, which is piped to the executable `libreblackjack` (assumed to be installed system-wide). The arguments tell libreblackjack to play one hundred thousand hands (`-n1e5`) using a flat bet (`flat_bet`, it defaults to a unit bet in each hand) and without asking for insurance if the dealer shows an ace (`no_insurance`). As there is no `libreblackjack.ini` file, the rules are---as expected---the default ones (see the documentation for details).

The `/dev/null` part is important, otherwise libreblackjack will think that there is a human at the other side of the table and will

  1. run slower (it will add explicit delays to mimic an actual human dealer), and
  2. give all the details of the dealt hands in the terminal as ASCII (actually UTF-8) art

This example is only one-way (i.e. the player ignores what the dealer says) so it is better to redirect the standard output to `/dev/null` to save execution time. The results are written as a [YAML](http://yaml.org/)-formatted data to `stderr` by default once the hands are over, so they will show up in the terminal nevertheless. This format is human-friendly (far more than JSON) so it can be easily parsed, but it also allows complex objects to be represented (arrays, lists, etc.).


As an exercise, verify that the analytical probability of getting a natural playing with a single deck (for both the dealer and the player) is 32/663 = 0.04826546...

```yaml
---
rules:
  decks:                  6
  hands:                  100000
  hit_soft_17:            1
  double_after_split:     1
  blackjack_pays:         1.5
  rng_seed:               -2067081387
  number_of_burnt_cards:  0
  no_negative_bankroll:   0
  max_bet:                0
  penetration:            0.75
  penetration_sigma:      0.05
cpu:
  user:             0.238384
  system:           0.226465
  wall:             0.462519
  second_per_hand:  4.6e-06
  hands_per_second: 2.2e+05
player: 
  wins:               0.38547
  pushes:             0.04744
  losses:             0.56709
  dealer_blackjacks:  0.04749
  player_blackjacks:  0.04803
  dealer_busts:       0.27168
  player_busts:       0
  doubled_hands:      0
  doubled_wins:       0
  insured_hands:      0
  insured_wins:       0
  number_of_hands:    100000
  number_of_shuffles: 2070
  total_money_waged:  100000
  worst_bankroll:     -15870.5
  final_bankroll:     -15868
  return:             -0.15868
  variance:            0.984727
  deviation:           0.992334
  error:               0.00313804
  result:             "(-15.9 ± 0.6) %"
...
```

case_nav
