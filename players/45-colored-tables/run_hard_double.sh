#!/bin/bash

rm -rf hard_double
mkdir -p hard_double
cd hard_double

for player in `seq 5 20`; do
 for dealer in 2 3 4 5 6 7 8 9 T A; do

  firstcard=11
  secondcard=11
  while test $firstcard -gt 10 -o $secondcard -gt 10; do
    firstcard=`echo ${RANDOM} % \(${player}-3\) + 2 | bc`
    secondcard=`echo ${player} - ${firstcard} | bc`
  done
  
  if [ "${dealer}" = "A" ]; then
    upcard=1
  elif [ "${dealer}" = "T" ]; then
    upcard=10
  else
    upcard=${dealer}
  fi
  
  for play in stand double; do
    playerpadded=`printf %02d ${player}`
    cp -r ../../22-strategy-from-file ${playerpadded}-vs-${dealer}-${play}
  
    cd  ${playerpadded}-vs-${dealer}-${play}
    cp ../../options.ini libreblackjack.ini
    cat << EOF >> libreblackjack.ini
card_format = value
dealer2player = mq file_d2p
player2dealer = mq file_p2d

arranged_cards = ${firstcard} ${upcard} `echo ${secondcard} + 13 | bc`
yaml_report=../${playerpadded}-vs-${dealer}-${play}.yaml
EOF

   echo "---------------------------------------------------------------------------"
   echo ${player}-vs-${dealer} ${play}
   echo "---------------------------------------------------------------------------"

   if [ "${play}" = "double" ]; then
     action=1
   else
     action=0
   fi

   cp ../../no_split.txt ./split.txt
   cp ../../no_soft_double.txt ./soft_double.txt
   awk -f ../../hit.awk -vdealer=${dealer} -vplayer=${player} -vaction=${action} < ../../hard_double.txt > hard_double.txt 

   rm -f /dev/mqueue/*

   ./custom &
   libreblackjack
 
   cd ..
   
  done
 
 done
done

cd ..
