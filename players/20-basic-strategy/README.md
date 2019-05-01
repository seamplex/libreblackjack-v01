# Derivation of the basic strategy

> Difficulty: 08/100

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
#    2  3  4  5  6  7  8  9  T  A
h20  s  s  s  s  s  s  s  s  s  s  
h19  s  s  s  s  s  s  s  s  s  s  
h18  s  s  s  s  s  s  s  s  s  s  
h17  s  s  s  s  s  s  s  s  s  s  
h16  s  s  s  s  s  h  h  h  h  h  
h15  s  s  s  s  s  h  h  h  h  h  
h14  s  s  s  s  s  h  h  h  h  h  
h13  s  s  s  s  s  h  h  h  h  h  
h12  h  h  s  s  s  h  h  h  h  h  
h11  d  d  d  d  d  d  d  d  d  d  
h10  d  d  d  d  d  d  d  d  h  h  
h9   h  d  d  d  d  h  h  h  h  h  
h8   h  h  h  h  h  h  h  h  h  h  
h7   h  h  h  h  h  h  h  h  h  h  
h6   h  h  h  h  h  h  h  h  h  h  
h5   h  h  h  h  h  h  h  h  h  h  
h4   h  h  h  h  h  h  h  h  h  h  

#    2  3  4  5  6  7  8  9  T  A
s20  s  s  s  s  s  s  s  s  s  s  
s19  s  s  s  s  d  s  s  s  s  s  
s18  d  d  d  d  d  s  s  h  h  h  
s17  h  d  d  d  d  h  h  h  h  h  
s16  h  h  d  d  d  h  h  h  h  h  
s15  h  h  d  d  d  h  h  h  h  h  
s14  h  h  h  h  d  h  h  h  h  h  
s13  h  h  h  h  d  h  h  h  h  h  
s12  h  h  h  h  d  h  h  h  h  h  

#    2  3  4  5  6  7  8  9  T  A
pA   y  y  y  y  y  y  y  y  y  y  
pT   n  n  n  n  n  n  n  n  n  n  
p9   y  y  y  y  y  n  y  y  n  n  
p8   y  y  y  y  y  y  y  y  y  y  
p7   y  y  y  y  y  y  n  n  n  n  
p6   y  y  y  y  y  n  n  n  n  n  
p5   n  n  n  n  n  n  n  n  n  n  
p4   n  n  n  y  y  n  n  n  n  n  
p3   y  y  y  y  y  y  n  n  n  n  
p2   y  y  y  y  y  y  n  n  n  n  
```


## Detailed exaplanation

We want to derive the basic strategy from scratch, i.e. without assuming anything. What we are going to do is to play a large (more on what _large_ means below) number of hands by fixing our first two cards and the dealer upcard and sequentially standing, doubling or hitting the first card. Then we will compare the results for the three cases and select as the proper strategy the better one.

Standing and doubling are easy plays, because after we stand or double the dealer plays accordingly to the rules. She hits until seventeen (either soft or hard). But if we hit on our hand, we might need to make another decision wether to stand or hit again. As we do not want to assume anything, we have to play in such an order that if we do need to make another decision, we already know which is the better one. 

TO BE COMPLETED

