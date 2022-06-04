#!/usr/bin/env bash
debugjob -n 16

FILE=timings_omp.txt

if test -f "$FILE"; then
    rm $FILE
fi

for i in {1..16}; do
    export OMP_NUM_THREADS=$i
    echo -e "\n$OMP_NUM_THREADS" >> $FILE
    { time ./analysewave_omp longresult.nc output.txt ; } 2>> $FILE
    rm output.txt
done