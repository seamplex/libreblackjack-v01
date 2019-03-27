mkfifo mimic_d2p mimic_p2d
../../libreblackjack &
./mimic-the-dealer.awk < mimic_d2p > mimic_p2d
