#!/bin/bash

# TODO: check for installed bc, awk


declare -A strategy
declare -A ev

# hard totals
cp hard-stand.txt hard.txt

for hand in `seq 20 -1 4`; do

 # choose two random cards that make up the player's assumed total
 card1=11
 card2=11
 while test $card1 -gt 10 -o $card2 -gt 10; do
   card1=`echo ${RANDOM} % \(${hand}-3\) + 2 | bc`
   card2=`echo ${hand} - ${card1} | bc`
 done
 
 for upcard in `seq 2 9` T A; do

  if [ "$upcard" = "T" ]; then
    upcard_n=$((10))
  elif [ "$upcard" = "A" ]; then
    upcard_n=$((1))
  else
    upcard_n=$(($upcard))
  fi

  n=100     # start with 100 hands
  best="x"  # we do not know yet what to do
  
  while [ "${best}" = "x" ]; do
   echo -n ${hand}-${upcard} \($card1 $card2\) "n="${n}
  
   for play in s d h; do
    
    # el ini
    cp options.ini libreblackjack.ini
    echo "hands = ${n}" >> libreblackjack.ini
    echo "dealer2player = internal"
    echo "arranged_cards = ${card1} $((${upcard_n} + 13)) $((${card2} + 26))" >> libreblackjack.ini
    echo "yaml_report = h${hand}-${upcard}-${play}.yaml" >> libreblackjack.ini
    echo "#log = h${hand}-${upcard}-${play}.log" >> libreblackjack.ini
    
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
    for h in `seq 20 -1 4`; do
     echo -n "h${h}  " >> hard.txt
     # TODO: extra space if h < 10
     for u in `seq 2 9` T A; do
      echo -n "${strategy[h${h},${u}]}  " >> hard.txt
     done
     echo >> hard.txt
    done
    cp hard.txt h$hand-$upcard-$play.str
   
    # ensamblamos el bs.txt
    cat hard.txt soft-stand.txt pairs-no.txt > bs.txt
   
    # jugamos
    ../../libreblackjack > /dev/null
   
    # miramos como salimos
    ev[h${hand},${upcard},${play}]=`grep return h${hand}-${upcard}-${play}.yaml | awk '{printf("%+g", $2)}'`
    error[h${hand},${upcard},${play}]=`grep error h${hand}-${upcard}-${play}.yaml | awk '{printf("%.1g", $2)}'`
    
   done
  
   # elegimos cual de los tres stand, double o hit fue mejor
   ev_s=`printf %g ${ev[h${hand},${upcard},s]}`
   ev_d=`printf %g ${ev[h${hand},${upcard},d]}`
   ev_h=`printf %g ${ev[h${hand},${upcard},h]}`
  
   
   if [ $n -le 999999 ]; then 
    error_s=${error[h${hand},${upcard},s]}
    error_d=${error[h${hand},${upcard},d]}
    error_h=${error[h${hand},${upcard},h]}
   else
    error_s=0
    error_d=0
    error_h=0
   fi  

   echo -ne "\ts=${ev_s} (${error_s})"
   echo -ne "\td=${ev_d} (${error_d})"
   echo -ne "\th=${ev_h} (${error_h})"
  
   if   (( $(echo "${ev_s}-${error_s} > ${ev_d}+${error_d}" | bc -l) )) &&
        (( $(echo "${ev_s}-${error_s} > ${ev_h}+${error_h}" | bc -l) )); then
    best="s"
    echo -e "\tstand"
   elif (( $(echo "${ev_d}-${error_d} > ${ev_s}+${error_s}" | bc -l) )) &&
        (( $(echo "${ev_d}-${error_d} > ${ev_h}+${error_h}" | bc -l) )); then
    best="d"
    echo -e "\tdouble"
   elif (( $(echo "${ev_h}-${error_h} > ${ev_s}+${error_s}" | bc -l) )) &&
        (( $(echo "${ev_h}-${error_h} > ${ev_d}+${error_d}" | bc -l) )); then
    best="h"
    echo -e "\thit"
   else
    best="x"
    n=$((${n} * 10))
    echo -e "\tuncertain"
   fi
  done

  strategy[h${hand},${upcard}]=${best}
  
  # volvemos a grabar la estrategia con el valor que elegimos
  rm -f hard.txt
  for h in `seq 20 -1 4`; do
   echo -n "h${h}  " >> hard.txt
   # TODO: extra space if h < 10
   for u in `seq 2 9` T A; do
    echo -n "${strategy[h${h},${u}]} " >> hard.txt
   done
   echo >> hard.txt
  done
 
 done
done
