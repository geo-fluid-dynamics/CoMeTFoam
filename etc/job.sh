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
#BSUB -n 16
 
### Use esub for Open MPI
#BSUB -a openmpi
 
### (OFF) load another Open MPI version than the default one
# module switch openmpi openmpi/1.7.4
 
### Change to the work directory
# cd /home/ks018038/repos/ks018038_DiMIce/trunk/OpenFOAM/CoMeTFoam/test/ConvergenceAnalysis/ViskantaImmersedCylinder 

#BSUB -P aices
 
module load TECHNICS
module load openfoam

### Execute your application
$MPIEXEC $FLAGS_MPI_BATCH foamExec /home/ks018038/OpenFOAM/ks018038-3.0.1/platforms/linux64IccDPInt32Opt/lib/CoMeTFoam -parallel
