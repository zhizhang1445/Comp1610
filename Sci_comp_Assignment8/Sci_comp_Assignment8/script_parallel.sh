#!/usr/bin/env bash

FILE=timings_adv.txt

if test -f "$FILE"; then
    rm $FILE
fi

for i in {1..16}; do
    export OMP_NUM_THREADS=$i
    echo -e "\n$OMP_NUM_THREADS" >> $FILE
    { time ./wave1d_parallel longwaveparams.txt ; } 2>> $FILE
done