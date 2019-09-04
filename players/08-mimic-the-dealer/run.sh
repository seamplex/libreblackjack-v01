if [ -z "`which gawk`" ]; then
  echo "error: gawk is not installed"
  exit 1
fi      

mkfifo mimic_d2p mimic_p2d
../../libreblackjack &
./mimic-the-dealer.awk < mimic_d2p > mimic_p2d
