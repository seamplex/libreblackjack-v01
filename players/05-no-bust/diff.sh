blackjack -n1e3 --rng_seed=1 --yaml_report=perl.yml  < fifo | ./no-bust.pl > fifo
blackjack -n1e3 --rng_seed=1 --yaml_report=shell.yml < fifo | ./no-bust.sh > fifo
diff perl.yml shell.yml 
