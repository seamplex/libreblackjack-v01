#!/bin/bash

rm -rf hard_hit
mkdir -p hard_hit
cd hard_hit

for player in `seq 5 20`; do
 for dealer in 2 3 4 5 6 7 8 9 T A; do

  # zero-padded string with the player's assumed first two-cards total
  playerpadded=`printf %02d ${player}`

  # choose two random cards that make up the player's assumed total
  firstcard=11
  secondcard=11
  while test $firstcard -gt 10 -o $secondcard -gt 10; do
    firstcard=`echo ${RANDOM} % \(${player}-3\) + 2 | bc`
    secondcard=`echo ${player} - ${firstcard} | bc`
  done
  
  # get the tag of the dealer's upcard
  if [ "${dealer}" = "A" ]; then
    upcard=1
  elif [ "${dealer}" = "T" ]; then
    upcard=10
  else
    upcard=${dealer}
  fi
  
  for play in stand hit; do
    mkdir ${playerpadded}-vs-${dealer}-${play}
#     cp -r ../../22-strategy-from-file 
  
    cd  ${playerpadded}-vs-${dealer}-${play}
    # use the base options.ini and then add the arranged cards
    cp ../../options.ini libreblackjack.ini
    cat << EOF >> libreblackjack.ini
card_format = value
dealer2player = mq file_d2p
player2dealer = mq file_p2d

arranged_cards = ${firstcard} ${upcard} `echo ${secondcard} + 13 | bc`
yaml_report=../${playerpadded}-vs-${dealer}-${play}.yaml
EOF

#    echo "---------------------------------------------------------------------------"
   echo ${player}-vs-${dealer} ${play}
#    echo "---------------------------------------------------------------------------"

   if [ "${play}" = "hit" ]; then
     action=1
   else
     action=0
   fi

   # copy the strategy files 
   cp ../../no_split.txt       ./split.txt
   cp ../../no_soft_double.txt ./soft_double.txt
   cp ../../no_hard_double.txt ./hard_double.txt
   cp ../../no_soft_hit.txt    ./soft_hit.txt
   
   awk -f ../../hit.awk -vdealer=${dealer} -vplayer=${player} -vaction=${action} < ../../hard_hit.txt > hard_hit.txt 

   rm -f /dev/mqueue/*

   ../../../22-strategy-from-file/custom &
   libreblackjack > /dev/null
 
   cd ..
   
  done
 
 done
done

cd ..
