#!/bin/bash

# get into the correct PWD
if [ ! -x ./check.sh ]; then
  cd players
fi

# expected results
declare -A expected=(\
["00-always-stand"]="-0.15" \
["05-no-bust"]="-0.075" \
["08-mimic-the-dealer"]="-0.055" \
["22-strategy-from-file"]="-0.005")

# allowed deviation
sigma=0.02

# if there is something on the commandline, use that one, ot
if test ! -z "$1"; then
  player=`basename $1`     # remove trailing '/'
else
  player=`echo *`
fi

for i in $player; do
  if test -d $i -a -x $i/run.sh; then
    cd $i
    echo -n "$i, expected ${expected["$i"]}... "
    ./run.sh 2>&1 | grep return | awk -v expected=${expected["$i"]} -v sigma=${sigma} 'END {ok = ($2 > (expected-sigma) && $2 < (expected+sigma))?0:1; print $2, ok==0?"ok":"failed"; exit ok }'
    result=$?
    cd ..
  else
    result=77
  fi
done
