#!/usr/bin/env zsh
 
### Job name
#BSUB -J OpenMPI36
 
### File / path where STDOUT & STDERR will be written
###    %J is the job ID, %I is the array ID
#BSUB -o OpenMPI36.%J.%I
 
### Request the time you need for execution in minutes
### The format for the parameter is: [hour:]minute,
### that means for 80 minutes you could also use this: 1:20
#BSUB -W 6:00
 
### Request memory you need for your job per PROCESS in MB
#BSUB -M 128
 
### Request the number of compute slots you want to use
#BSUB -n 2
 
### Use esub for Open MPI
#BSUB -a openmpi

#BSUB -P aices
 
module load TECHNICS
module load openfoam/5.0

### Execute your application
$MPIEXEC $FLAGS_MPI_BATCH foamExec CoMeTFoam -parallel
