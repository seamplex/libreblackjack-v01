if test ! -e fifo; then
 mkfifo fifo
fi
../../libreblackjack < fifo | ./ace-five.py > fifo
