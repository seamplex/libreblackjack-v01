#!/bin/sh

while command=`line`
do
  if test "${command}" = 'bye'; then
    exit
  elif test "${command}" = 'bet?'; then
    echo 1  
  elif test "${command}" = 'insurance?'; then
    echo "no"
  elif test "`echo ${command} | cut -c-5`" = 'play?'; then
    echo "count"
    count=`line`
    play=`line`      # libreblackjack will ask again for 'play?'
    if test ${count} -lt 12; then
      echo "hit"
    else
      echo "stand"
    fi
  fi
done
