#!/bin/bash
#PBS -l walltime=1:00:00
#PBS -l select=1:ncpus=1:mem=3800mb:ngpus=0

module load intel-suite/11.1
module load opencl/intel-1.5

cd $PBS_O_WORKDIR
CLWRAPPER_LIB_PATH=$PBS_O_WORKDIR/../../lib
export LD_LIBRARY_PATH=$CLWRAPPER_LIB_PATH/:/apps/opencl/1.5/lib:/apps/opencl/1.5/lib/OpenCL/vendors/intel/:/apps/intel/cc/10.1.018/lib

module list
echo $LD_LIBRARY_PATH
ldd $CLWRAPPER_LIB_PATH/libclwrapper.so
ldd saxpy

./saxpy
