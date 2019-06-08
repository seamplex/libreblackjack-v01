define(case_title, Derivation of the basic strategy)
---
title: case_title
...

# case_title

> Difficulty: case_difficulty/100

## Quick run

Execute the `run.sh` script. It should take a minute or so:

```
$ ./run.sh
h20-2 (10 10) n=1000    s=0.634 (0.03)  d=-1.676 (0.03) h=-0.844 (0.02) stand
h20-3 (10 10) n=1000    s=0.66 (0.03)   d=-1.744 (0.03) h=-0.847 (0.02) stand
h20-4 (10 10) n=1000    s=0.65 (0.03)   d=-1.708 (0.03) h=-0.852 (0.02) stand
[...]
p2-T n=1000     y=-0.552 (0.05) n=-0.381 (0.03) no
p2-A n=1000     y=-0.565 (0.04) n=-0.543 (0.03) uncertain
p2-A n=10000    y=-0.6505 (0.01)        n=-0.5025 (0.008)       no
```

A new text file called `bs.txt` with the strategy should be created from scratch:

```
include(bs.txt)dnl
```

## Full table with results

The script computes the expected value of each combination

 1. Player’s hand (hard, soft and pair)
 2. Dealer upcard
 3. Hit, soft and stand (for hards and softs) and splitting or not (for pairs)
 
The results are given as the expected value in percentage with the uncertainty (one standard deviation) in the last significant digit.
 

define(table_head,
 <thead>
  <tr>
   <th class="text-center" width="10%" colspan="2">Hand</th>
   <th class="text-center" width="9%">2</th>
   <th class="text-center" width="9%">3</th>
   <th class="text-center" width="9%">4</th>
   <th class="text-center" width="9%">5</th>
   <th class="text-center" width="9%">6</th>
   <th class="text-center" width="9%">7</th>
   <th class="text-center" width="9%">8</th>
   <th class="text-center" width="9%">9</th>
   <th class="text-center" width="9%">T</th>
   <th class="text-center" width="9%">A</th>
  </tr>
 </thead> 
)
 
<table class="table table-sm table-responsive table-hover small w-100">
 table_head
 <tbody> 
include(pair.html)
 </tbody>
 table_head
 <tbody> 
include(soft.html)
 </tbody>
 table_head
 <tbody> 
include(hard.html)
 </tbody>
</table>

## Detailed explanation

We want to derive the basic strategy from scratch, i.e. without assuming anything. What we are going to do is to play a large (more on what _large_ means below) number of hands by fixing our first two cards and the dealer upcard and sequentially standing, doubling or hitting the first card. Then we will compare the results for the three cases and select as the proper strategy the better one.

Standing and doubling are easy plays, because after we stand or double the dealer plays accordingly to the rules. She hits until seventeen (either soft or hard). But if we hit on our hand, we might need to make another decision wether to stand or hit again. As we do not want to assume anything, we have to play in such an order that if we do need to make another decision, we already know which is the better one. 

### Hard hands

So we start by arranging the shoe so that the user gets hard twenty (i.e. two faces) and the dealer gets succesively upcards of two to ace. So we play each combination of dealer upcard (ten) three times each playing either

 1. always standing
 2. always doubling
 3. always hitting
 
In general the first two plays are easy, because the game stops either after standing or after receiving only one card. The last one might lead to further hitting, but since we are starting with a hard twenty, that would either give the player twenty one or a bust. In any case, the game also ends.
So we play a certain number of hands (say one thousand hands) each of these three plays for each of the ten upcard faces and record the outcome. The correct play for hard twenty against each of the ten upcards is the play that gave the better result, which is of course standing.

Next, we do the same for a hard nineteen. In this case, the hitting play might not end after one card is drawn. But if that is the case, i.e. receiving an ace for a total of hard twenty, we already know what the best play is from the previous step so we play accordingly and we stand. Repeating this procedure down to hard four we can build the basic strategy table for any hard total against any dealer upcard.

### Soft hands

We can now switch to analyze soft hands. Starting from soft twenty (i.e. an ace and a nine) we do the same we did for the hard case. The only difference is that wehn hitting, we might end either in another soft hand which we would already analyzed because we start from twenty and go down, or in a hard hand, which we also already analyzed se we can play accordingly.

### Pairs

When dealing with pairs, we have to decide wether to split or not. When we do not split, we end up in one of the already-analyzed cases: either a soft twelve of any even hard hand. When we split, we might end in a hard or soft hand (already analyzed) or in a new pair. But since the new pair can be only the same pair we are analyzing, we have to treat it like we treated the first pair: either to split it or not, so we know how to deal with it.  

### Number of hands

The output is the expected value~$e$ of the bankroll, which is a random variable with an associated uncertainty~$\Delta e$ (i.e. a certain numbers of standard deviations). For example, if we received only blackjacks, the expected value would be 1.5 (provided blackjacks pay 3 to 2). If we busted all of our hands without doubling or splitting, the expected value would be -1. In order to say that the best strategy is, let’s say stand and not hitting or doubling, we have to make sure that

\[ e_h-\Delta e_h > e_s+\Delta e_s \]

and

\[ e_h-\Delta e_h > e_d+\Delta e_d \]

If there is no play that can give a better expected value than the other two taking into account the uncertainties, then we have to play more hands in order to reduce the random uncertainty.


## Implementation

The steps above can be written in a [Bash](https://en.wikipedia.org/wiki/Bash_%28Unix_shell%29) script that

 * loops over hands and upcards,
 * creates a strategy file for each possible play hit, double or stand (or split or not),
 * runs [Libreblackjack](https://www.seamplex.com/blackjack),
 * checks the results and picks the best play,
 * updates the strategy file

```bash
include(run.sh)
```

case_nav
