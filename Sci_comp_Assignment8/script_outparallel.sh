#!/usr/bin/env bash

FILE=timings_out.txt

if test -f "$FILE"; then
    rm $FILE
fi

for i in {1..16}; do
    export OMP_NUM_THREADS=$i
    echo -e "\n$OMP_NUM_THREADS" >> $FILE
    { time ./wave1d_outparallel longwaveparams.txt ; } 2>> $FILE
done