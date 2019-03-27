if test ! -e fifo; then
 mkfifo fifo
fi
../../libreblackjack -n1e5 < fifo | ./no-bust.pl > fifo
