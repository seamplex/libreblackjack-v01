if [ ! -z "`which awk`" ]; then
  ./blackjack -i 2>&1 | grep return | awk '{e=-4e-3;s=1e-2} END {ok = ($2>(e-s)&&$2<(e+s)); print ok?"ok":"failed"; exit !ok }'
  result=$?
else
  result=77
fi
