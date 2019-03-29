## Always stand

> Difficulty: 00/100

To play libreblackjack as an “always-stander” run the following command:

```
yes stand | libreblackjack -n1e5 --flat_bet --no_insurance > /dev/null
```

The UNIX command `yes stand` writes the string `stand` repeteadly to the standard output, which is piped to the executable `libreblackjack` (assumed to be installed system-wide). The arguments tell libreblackjack to play one thousand hundred hands (`-n1e5`) using a flat bet (`flat_bet`, it defaults to a unit bet in each hand) and without asking for insurance if the dealer shows an ace (`no_insurance`). As there is no `libreblackjack.ini` file, the rules are---as expected---the default ones (see the documentation for details).

This example is only one-way (i.e. the player ignores what the dealer says) so it is better to redirect the standard output to `/dev/null` to save execution time. The results are written as a [YAML](http://yaml.org/)-formatted data to `stderr` by default once the hands are over, so they will show up in the terminal nevertheless. Besides being human-friendly, this format can be used by [Pandoc](http://pandoc.org/) to generate customized reports in a wide variety of formats.


As an exercise, verify that the analytical probability of getting a natural playing with a single deck (for both the dealer and the player) is 32/663 = 0.04826546...

