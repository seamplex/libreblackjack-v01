#!/usr/bin/python

# plays the wizard's ace-five count
# <http://wizardofodds.com/games/blackjack/appendix/17/>
# with the simple strategy at
# <http://wizardofodds.com/games/blackjack/appendix/21/>
#
#
#  Player's hand     Dealer's upcard
# 
#  -- hard --------------------------------
#                    2 to 6     7 to A
#  4 to 8              H          H   
#  9                   D          H   
#  10 or 11        D with more than dealer
#  12 to 16            S          H
#  17 to 21            S          S
#
#  -- soft --------------------------------
#                    2 to 6     7 to A
#  13 to 15            H          H   
#  16 to 18            D          H   
#  19 to 21            S          S
#
#  -- split -------------------------------
#                    2 to 6     7 to A
#  22,33,66,77,99      Y          N   
#  88,AA               Y          Y   
#  44,55,TT            N          N
#
#  Plus:
#    1. surrender 16 vs 10
#    2. never take insurance
#    3. if not allowed to double, stand with soft 18
#

import sys 
import os
sys.stdout = os.fdopen(sys.stdout.fileno(), 'w', 0)

max_bet = 32

line = raw_input()
while line != "bye":
    splitted = 0
    if line == "shuffling":
        count = 0
        bet = 1
        
    if line == "new_hand": 
        players_cards = 0
        
    elif line == "bet?":
        if count <= 1:
            bet = 1
        elif bet < max_bet:
            bet *= 2
        print bet

    if line[:5] == "card_":
        tokens = line.split()
        card = int(tokens[1])
        if card == 11:
            count -= 1
        elif card == 5:
            count += 1

        if line[:17] == "card_player_first":
            players_cards = 1
            card_player_first = card
              
        elif line[:18] == "card_player_second":
            players_cards = 2
            card_player_second = card

        elif line[:11] == "card_player":
            players_cards += 1
                      
    elif line[:5] == "play?":
        tokens = line.split()
        player = int(tokens[1])
        #sys.stderr.write("player %d\n"%player)
        dealer = int(tokens[2])

        if players_cards == 2 and card_player_first == card_player_second:
            if card_player_first == 8 or card_player_first == 11:
                print "split"       # always split eights and aces
                splitted = 1
            elif dealer < 7 and (card_player_first == 2 or card_player_first == 3 or card_player_first == 6 or card_player_first == 7 or card_player_first == 9):
                print "split"
                splitted = 1
  
        if splitted == 0:
            if player > 0:
                # hard
                if player < 9:         
                    print "h"           # hit 4 to 8 against anything
                elif player == 9:
                    if dealer < 7: 
                        if players_cards == 2:
                            print "d"   # double 9 against 2 to 6
                        else:
                            print "h"
                    else:
                        print "h"       # hit 9 against 7 to A
                elif player < 12:
                    if player > dealer:
                        if players_cards == 2:
                            print "d"   # double with 10 or 11 and more than dealer
                        else:
                            print "h"
                    else:
                        print "h"       # otherwise whit
                elif player < 17:
                    if dealer < 7:
                        print "s"       # stand with 12 to 16 against 2 to 6
                    else:
                        print "h"       # hit with 12 to 16 against 7 to A
                else:
                    print "s"           # stand with hard 17 or more
                
            else:
                # soft
                player = abs(player)
                if player < 16:        
                    print "h"           # hit every soft less than 16
                elif player < 19:
                    if dealer < 7:
                        if players_cards == 2:
                            print "d"   # double soft 16 to 18 againt 2 to 6
                        elif player == 18:
                            print "s"   # stand with soft 18
                        else:
                            print "h"
                    else:
                        print "h"       # hit soft 16 to 18 against 7 to A
                else:
                    print "s"           # stand with soft 19 or more

    elif line == "invalid_command":
        sys.stderr.write("le tome la leche al gato\n")
        print "quit"

    line = raw_input()

