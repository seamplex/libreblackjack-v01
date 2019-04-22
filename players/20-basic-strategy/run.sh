#!/bin/bash

# TODO: check for installed bc, awk


declare -A strategy
declare -A ev

# --------------------------------------------------------------
# hard totals
cp hard-stand.txt hard.txt

for hand in `seq 20 -1 4`; do

 # choose two random cards that make up the player's assumed total
 card1=11
 card2=11
 while test $card1 -gt 10 -o $card2 -gt 10; do
#    card1=`echo ${RANDOM} % \(${hand}-3\) + 2 | bc`
   card1=$((${RANDOM} % (${hand}-3) + 2))
   card2=$((${hand} - ${card1}))
 done
 
 for upcard in `seq 2 9` T A; do

  if [ "$upcard" = "T" ]; then
    upcard_n=10
  elif [ "$upcard" = "A" ]; then
    upcard_n=1
  else
    upcard_n=$(($upcard))
  fi

  n=100     # start with 100 hands
  best="x"  # start with uncertainty so we need to play
  
  while [ "${best}" = "x" ]; do
   # tell the user which combination we are trying and how many we will play
   echo -n ${hand}-${upcard} \($card1 $card2\) "n="${n}
  
   for play in s d h; do
    
    # start with options.ini and add some custom stuff
    cp options.ini libreblackjack.ini
    cat << EOF >> libreblackjack.ini
hands = ${n}
dealer2player = internal
arranged_cards = ${card1} $((${upcard_n} + 13)) $((${card2} + 26))
yaml_report = h${hand}-${upcard}-${play}.yaml
#log = h${hand}-${upcard}-${play}.log
EOF

    # read the current strategy
    while read hh p2 p3 p4 p5 p6 p7 p8 p9 pT pA; do
     # hh already has the "h"
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
    
    # override the read strategy with the explicit play: s, d or h
    strategy[h${hand},${upcard}]=${play}
    
    # save the new (temporary) strategy
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
   
    # ensamble the full bs.txt file with soft stands and no pairing
    cat hard.txt soft-stand.txt pairs-no.txt > bs.txt
   
    # play!
    ../../libreblackjack > /dev/null
   
    # evaluate the results
    ev[h${hand},${upcard},${play}]=`grep return h${hand}-${upcard}-${play}.yaml | awk '{printf("%+g", $2)}'`
    error[h${hand},${upcard},${play}]=`grep error h${hand}-${upcard}-${play}.yaml | awk '{printf("%.1g", $2)}'`
    
   done
  
   # choose the best one
   ev_s=`printf %g ${ev[h${hand},${upcard},s]}`
   ev_d=`printf %g ${ev[h${hand},${upcard},d]}`
   ev_h=`printf %g ${ev[h${hand},${upcard},h]}`
  
   
   if [ $n -le 999999 ]; then 
    # if we still have room, take into account errors
    error_s=${error[h${hand},${upcard},s]}
    error_d=${error[h${hand},${upcard},d]}
    error_h=${error[h${hand},${upcard},h]}
   else
    # instead of running infinite hands, above a threshold asume errors are zero
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
  
  # save the strategy again with the best strategy
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


# cp posta.txt hard.txt

# --------------------------------------------------------------
# soft totals
cp soft-stand.txt soft.txt

# hand=20
for hand in `seq 20 -1 12`; do

 # one card is an ace
 card1=1
 card2=$((${hand} - 10 - ${card1}))
 
# upcard=2 
 for upcard in `seq 2 9` T A; do

  if [ "$upcard" = "T" ]; then
    upcard_n=10
  elif [ "$upcard" = "A" ]; then
    upcard_n=1
  else
    upcard_n=$(($upcard))
  fi

  n=1000    # start with this number of hands, and increase if needed
  best="x"  # start with uncertainty so we need to play
  
  while [ "${best}" = "x" ]; do
   # tell the user which combination we are trying and how many we will play
   echo -n ${hand}-${upcard} \($card1 $card2\) "n="${n}
  
   for play in s d h; do
    
    # start with options.ini and add some custom stuff
    cp options.ini libreblackjack.ini
    cat << EOF >> libreblackjack.ini
hands = ${n}
dealer2player = internal
arranged_cards = ${card1} $((${upcard_n} + 13)) $((${card2} + 26))
yaml_report = s${hand}-${upcard}-${play}.yaml
#log = s${hand}-${upcard}-${play}.log
EOF

    # read the current strategy
    while read sh p2 p3 p4 p5 p6 p7 p8 p9 pT pA; do
     strategy[${sh},2]=$p2   
     strategy[${sh},3]=$p3
     strategy[${sh},4]=$p4    
     strategy[${sh},5]=$p5    
     strategy[${sh},6]=$p6    
     strategy[${sh},7]=$p7    
     strategy[${sh},8]=$p8    
     strategy[${sh},9]=$p9    
     strategy[${sh},T]=$pT    
     strategy[${sh},A]=$pA    
    done < soft.txt
    
    # override the read strategy with the explicit play: s, d or h
    strategy[s${hand},${upcard}]=${play}
    
    # save the new (temporary) strategy
    rm -f soft.txt
    for h in `seq 20 -1 12`; do
     echo -n "s${h}  " >> soft.txt
     for u in `seq 2 9` T A; do
      echo -n "${strategy[s${h},${u}]}  " >> soft.txt
     done
     echo >> soft.txt
    done
    cp soft.txt s${hand}-${upcard}-${play}.str
   
    # ensamble the full bs.txt file no pairing
    cat hard.txt soft.txt pairs-no.txt > bs.txt
   
    # play!
    ../../libreblackjack > /dev/null
   
    # evaluate the results
    ev[s${hand},${upcard},${play}]=`grep return s${hand}-${upcard}-${play}.yaml | awk '{printf("%+g", $2)}'`
    error[s${hand},${upcard},${play}]=`grep error s${hand}-${upcard}-${play}.yaml | awk '{printf("%.1g", $2)}'`
    
   done
  
   # choose the best one
   ev_s=`printf %g ${ev[s${hand},${upcard},s]}`
   ev_d=`printf %g ${ev[s${hand},${upcard},d]}`
   ev_h=`printf %g ${ev[s${hand},${upcard},h]}`
  
   
   if [ $n -le 999999 ]; then 
    # if we still have room, take into account errors
    error_s=${error[s${hand},${upcard},s]}
    error_d=${error[s${hand},${upcard},d]}
    error_h=${error[s${hand},${upcard},h]}
   else
    # instead of running infinite hands, above a threshold asume errors are zero
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

  strategy[s${hand},${upcard}]=${best}
  
  # save the strategy again with the best strategy
  rm -f soft.txt
  for h in `seq 20 -1 12`; do
   echo -n "s${h}  " >> soft.txt
   for u in `seq 2 9` T A; do
    echo -n "${strategy[s${h},${u}]} " >> soft.txt
   done
   echo >> soft.txt
  done
 
 done
done
