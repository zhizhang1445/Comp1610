#!/bin/bash
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=16
#SBATCH --time=4:00:00
#SBATCH --job-name=gnu-parallelx16

module load gcc/9.2.0
module load gnu-parallel

parallel --joblog log -j $SLURM_TASKS_PER_NODE < subjob
