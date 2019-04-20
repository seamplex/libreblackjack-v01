#!/bin/bash

# TODO: check for bc


declare -A strategy
declare -A result

# hard totals
cp hard-stand.txt hard.txt
# hand=4
for hand in `seq 20 -1 4`; do

 # choose two random cards that make up the player's assumed total
 card1=11
 card2=11
 while test $card1 -gt 10 -o $card2 -gt 10; do
   card1=`echo ${RANDOM} % \(${hand}-3\) + 2 | bc`
   card2=`echo ${hand} - ${card1} | bc`
 done
 
#  upcard=8
 for upcard in `seq 2 9` T A; do

  if [ "$upcard" = "T" ]; then
    upcard_n=$((10))
  elif [ "$upcard" = "A" ]; then
    upcard_n=$((1))
  else
    upcard_n=$(($upcard))
  fi

  echo ${hand}-${upcard} \($card1 $card2\)
  
#   play=h
  for play in s d h; do
#    echo ${hand}-${upcard} ${play} \($card1 $card2\)
    
   # el ini
   cp options.ini libreblackjack.ini
   echo "arranged_cards = ${card1} ${upcard_n} `echo $((${card2}))`" >> libreblackjack.ini
   echo "yaml_report = h${hand}-${upcard}-${play}.yaml" >> libreblackjack.ini
   echo "log = h${hand}-${upcard}-${play}.log" >> libreblackjack.ini
    
   # leemos la estrategia actual
   # TODO: tirar comentarios
   while read hh p2 p3 p4 p5 p6 p7 p8 p9 pT pA; do
    strategy[${hh},2]=$p2   
    strategy[${hh},3]=$p3
    strategy[${hh},4]=$p4    
    strategy[${hh},5]=$p5    
    strategy[${hh},6]=$p6    
    strategy[${hh},7]=$p7    
    strategy[${hh},8]=$p8    
    strategy[${hh},9]=$p9    
    strategy[${hh},T]=$pT    
    strategy[${hh},A]=$pA    
   done < hard.txt
    
   # ponemos el play que nos toca
   strategy[h${hand},${upcard}]=${play}
    
   # grabamos la estrategia nueva
   rm -f hard.txt
   for h in `seq 20 -1 5`; do
    echo -n "h${h}  " >> hard.txt
    # TODO: extra space if h < 10
    for u in `seq 2 9` T A; do
     echo -n "${strategy[h${h},${u}]} " >> hard.txt
    done
    echo >> hard.txt
   done
   cp hard.txt h$hand-$upcard-$play.str
   
   # ensamblamos el bs.txt
   cat hard.txt soft-stand.txt pairs-no.txt > bs.txt
   
   # jugamos
   ../../libreblackjack > /dev/null
   
   # miramos como salimos
   result[h${hand},${upcard},${play}]=`grep return h${hand}-${upcard}-${play}.yaml | awk '{print $2}'`
#    echo ${result[h${hand},${upcard},${play}]}
  done
  
  # elegimos cual de los tres stand, double o hit fue mejor
  echo s ${result[h${hand},${upcard},s]} > h${hand}-${upcard}.result
  echo d ${result[h${hand},${upcard},d]} >> h${hand}-${upcard}.result
  echo h ${result[h${hand},${upcard},h]} >> h${hand}-${upcard}.result
  sort -g -k2 h${hand}-${upcard}.result
  strategy[h${hand},${upcard}]=`sort -g -k2 h${hand}-${upcard}.result  | tail -n1 | cut -c1`
  
  # volvemos a grabars la estrategia con el valor que elegimos
  rm -f hard.txt
  for h in `seq 20 -1 5`; do
   echo -n "h${h}  " >> hard.txt
   # TODO: extra space if h < 10
   for u in `seq 2 9` T A; do
    echo -n "${strategy[h${h},${u}]} " >> hard.txt
   done
   echo >> hard.txt
  done
 
 done
done
