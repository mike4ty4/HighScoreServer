#!/bin/bash
# Automated test case for high score server.
# Created at: 2018-05-03 (TAI: 1904043548)

# Do randomized test case.
Players="Sikozu
Cilantro
Skywalker
Vulture
STARWARSSUX
HARRIPOTSUX
TeamZGBH
ZaoGaoBuHao"

player_arr=($Players)
num_players=${#player_arr[*]}

for i in {1..1000}
do
    ../hssclient $1 $((1 + RANDOM % 5)) ${player_arr[$((RANDOM%num_players))]} $((RANDOM % 50000))
    sleep 0.1
done
