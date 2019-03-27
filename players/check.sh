#!/bin/bash

if [ ! -x ./check.sh ]; then
  cd players
fi

declare -A expected=(\
["00-always-stand"]="-0.15" \
["05-no-bust"]="-0.075" \
["08-mimic-the-dealer"]="-0.055" \
["22-strategy-from-file"]="-0.005")

sigma=0.02

if test ! -z "$1"; then
  player=`basename $1`     # remove trailing '/'
else
  player=`echo *`
fi

for i in $player; do
  if test -d $i -a -x $i/run.sh; then
    cd $i
    echo -n "$i, expected ${expected["$i"]}... "
    ./run.sh 2>&1 | grep result | awk -v expected=${expected["$i"]} -v sigma=${sigma} '{print $2} END {exit ($2 > (expected-sigma) && $2 < (expected+sigma))?0:1}'
    result=$?
    cd ..
  else
    result=77
  fi
done
