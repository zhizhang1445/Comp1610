#!/bin/bash
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=16
#SBATCH --time=15:00
#SBATCH --job-name mpi
#SBATCH --output=mpi%j.out
#SBATCH --mail-type=FAIL

module load gcc/9
module load openmpi/4

FILE=timings_mpi.txt

if test -f "$FILE"; then
    rm $FILE
fi

for i in {1..32}; do
    if test -f "output.txt"; then
        rm output.txt
    fi

    mpirun -n $i hostname
    echo -e "\n$i" >> $FILE
    { time mpirun -n $i ./analysewave_mpi longresult.nc output.txt ;} 2>> $FILE
done