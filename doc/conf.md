`blackjack_pays`

:    Blackjack payout ratio

:    Set how much a blackjack received by the player pays.
It can be either a textual `3/2` or `6/5` or any
floating-point number.

:    **Default:** `3/2`


`burnt_cards`

:    Number of burnt cards when starting a new shoe.

:    When a new shoe is started, this number of cards
are burned by the dealer.
Statistically this number does not have any effect,
it is provided for the sake of completeness.

:    **Default:** No cards are burned.


`decks`

:    Number of decks in the shoe.

:    A value of -1 corresponds "infinite" which means
sample a random card instead of actually shuffling a
real shoe and drawing a card from it  

:    **Default:** 6 


`double_after_split`

:    Double after split

:    Set if the player is allowed to double after
splitting. A value of zero means not allowed
and a non-zero means allowed.
This variable can also be shortened as `das`.

:    **Default:** Allowed


`hands`

:    Number of hands to play.

:    After the prescribed number of hands have been played,
the execution ends. A scientific notation number can
be given to avoid issues with too many zeros.
So one million hands can be written either
as `1000000` or as `1e6`.

:    **Default:** One million


`hit_soft_17`

:    Hit soft seventeens

:    Set if the dealer must hit on soft 17s or not.
A value of zero means dealer must stand
and a non-zero means dealer must hit.
This variable can also be shortened as `h17`.

:    **Default:** Dealer must hit soft 17s.


`max_bet`

:    Maximum allowed bet

:    Integer that limits the player's bet with
respect to a minimum value of one.
A value of zero means no limit.

:    **Default:** No limit     


`penetration`

:    Fraction of the shoe where the cut card is
(randomnly) placed

:    This variable controls the percentage of 
the shoe which is used for playing before
re-shuffling. The cut card is placed by the
dealer with a gaussian random distribution 
centered at this fraction $\in [0:1]$ and
standard deviation contrlled by `penetration_sigma`.
The hand in which the cut card appears is
finished and a new show is started.
If the value is zero, the sho is reshuffled after
each hand.

:    **Default:** 0.75


`penetration_sigma`

:    Standard deviation of the distribution of the
fraction that controls the location of the cut card.

:    This variable gives the standard deviation of the
random distribution used to place the cut card in
the shoe before re-shuffling. The cut card is placed
by the dealer with a gaussian random distribution 
centered at the fraction $\in [0:1]$ given by
`penetration` and standard deviation given by this
value.

:    **Default:** 0.05


`rng_seed`

:    Random number generator seed.

:    The seed used by the RNG in charge of shuffling the shoe
(or sampling from an infinite deck if `decks`=-1).
This can be used to have repeteability in the order
of the dealt cards.

:    **Default:** Get seed from `/dev/urandom`. 



