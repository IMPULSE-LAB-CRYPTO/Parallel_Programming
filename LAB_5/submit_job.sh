#!/bin/bash
#SBATCH --job-name=Simonov_MPI_Lab5
#SBATCH --time=00:05:00
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=4
#SBATCH --partition=batch
#SBATCH --output=result_simonov.out

# Активация среды Intel
source /soft/intel/parallel_studio_xe_2016.3.067/bin/psxevars.sh intel64

# Запуск программы
mpirun ./matrix_mpi
