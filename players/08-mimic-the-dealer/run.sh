rm -f mimic_d2p mimic_p2d
mkfifo mimic_d2p mimic_p2d
blackjack &
gawk -f mimic-the-dealer.awk < mimic_d2p > mimic_p2d
