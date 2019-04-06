#!/bin/bash

if [ -z "`which awk`" ]; then
  echo "error: awk is not installed"
  exit 1
fi

# get into the correct PWD
if [ ! -f ./parse_yaml.sh ]; then
  cd players
fi
if [ ! -f ./parse_yaml.sh ]; then
  echo "error: call me from the players directory"
  exit 1
fi

# include parse_yaml function
. ./parse_yaml.sh


# expected results
declare -A expected=(\
["00-internal"]="-0.005" \
["02-always-stand"]="-0.15" \
["05-no-bust"]="-0.075" \
["08-mimic-the-dealer"]="-0.055")

# allowed deviation
sigma=0.02

# if there is something on the commandline, use that one, otherwise the expected keys
if test ! -z "$1"; then
  player=`basename $1`     # remove trailing '/'
else
  player="${!expected[@]}"
fi

echo ' Name | Expected |  Result | Error | Speed | Status '
echo ' ---- | -------- |  ------ | ----- | ----- | ------ '
for i in $player; do
  if test -d $i -a -x $i/run.sh; then
    cd $i
    echo -ne ${i}' | '${expected["$i"]}' | '
    ./run.sh 1>/dev/null 2>../$i.yaml
    eval $(parse_yaml ../$i.yaml "result_")
    echo -ne ${result_player_return}' | '${result_player_error}' | '${result_cpu_hands_per_second}' | '
    echo ${result_player_return} | awk -v e=${expected["$i"]} -v s=${sigma} 'END {ok = ($1>(e-s)&&$1<(e+s)); print ok?"ok":"failed"; exit !ok }'
    result=$?
    cd ..
  else
    echo "skipped $i"
    result=77
  fi
done
