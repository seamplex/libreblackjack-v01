#!/bin/bash

rm -rf soft_hit
mkdir -p soft_hit
cd soft_hit

for secondcard in A `seq 2 9`; do
 for dealer in `seq 2 9` T A; do

  firstcard=1
  
  if [ "${dealer}" = "A" ]; then
    upcard=1
  elif [ "${dealer}" = "T" ]; then
    upcard=10
  else
    upcard=${dealer}
  fi
  
  player="A,${secondcard}"
  if [ "${secondcard}" = "A" ]; then
    secondcardvalue=1
  else
    secondcardvalue=${secondcard}
  fi
  
  for play in stand hit; do
    cp -r ../../22-strategy-from-file ${player}-vs-${dealer}-${play}
  
    cd  ${player}-vs-${dealer}-${play}
    cp ../../options.ini libreblackjack.ini
    cat << EOF >> libreblackjack.ini
card_format = value
dealer2player = mq file_d2p
player2dealer = mq file_p2d

arranged_cards = `echo ${firstcard} + 13 | bc` ${upcard} `echo ${secondcardvalue} + 26 | bc`
yaml_report=../${player}-vs-${dealer}-${play}.yaml
EOF

   echo "---------------------------------------------------------------------------"
   echo ${player}-vs-${dealer} ${play}
   echo "---------------------------------------------------------------------------"

   if [ "${play}" = "hit" ]; then
     action=1
   else
     action=0
   fi

   cp ../../no_split.txt ./split.txt
   cp ../../no_soft_double.txt ./soft_double.txt
   cp ../../no_hard_double.txt ./hard_double.txt
   awk -f ../../hit.awk -vdealer=${dealer} -vplayer=${player} -vaction=${action} < ../../soft_hit.txt > soft_hit.txt 

   if [ "${play}" = "stand" ]; then
     cp ../../no_hard_hit.txt ./hard_hit.txt
   fi

   rm -f /dev/mqueue/*

   ./custom &
   libreblackjack
 
   cd ..
   
  done
 
 done
done

cd ..
