#!/bin/bash

rm -rf split
mkdir -p split
cd split

for firstcard in `seq 2 9` T A; do
 for dealer in `seq 2 9` T A; do

  if [ "${dealer}" = "A" ]; then
    upcard=1
  elif [ "${dealer}" = "T" ]; then
    upcard=10
  else
    upcard=${dealer}
  fi
  
  player="${firstcard},${firstcard}"
  if [ "${firstcard}" = "A" ]; then
    firstcardvalue=1
  elif [ "${firstcard}" = "T" ]; then
    firstcardvalue=10
  else
    firstcardvalue=${firstcard}
  fi
  
  for play in split nosplit; do
    cp -r ../../22-strategy-from-file ${player}-vs-${dealer}-${play}
  
    cd  ${player}-vs-${dealer}-${play}
    cp ../../options.ini libreblackjack.ini
    cat << EOF >> libreblackjack.ini
card_format = value
dealer2player = mq file_d2p
player2dealer = mq file_p2d

arranged_cards = `echo ${firstcardvalue} + 13 | bc` ${upcard} `echo ${firstcardvalue} + 26 | bc`
yaml_report=../${player}-vs-${dealer}-${play}.yaml
EOF

   echo "---------------------------------------------------------------------------"
   echo ${player}-vs-${dealer} ${play}
   echo "---------------------------------------------------------------------------"

   if [ "${play}" = "split" ]; then
     action=1
   else
     action=0
   fi

   awk -f ../../hit.awk -vdealer=${dealer} -vplayer=${player} -vaction=${action} < ../../split.txt > split.txt 

   rm -f /dev/mqueue/*

   ./custom &
   libreblackjack
 
   cd ..
   
  done
 
 done
done

cd ..
