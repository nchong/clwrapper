module load intel-suite/11.1
module load opencl/intel-1.5

cd $PBS_O_WORKDIR
CLWRAPPER_LIB_PATH=$PBS_O_WORKDIR/../../lib
export LD_LIBRARY_PATH=$CLWRAPPER_LIB_PATH/:$LD_LIBRARY_PATH

module list
echo $LD_LIBRARY_PATH
ldd $CLWRAPPER_LIB_PATH/libclwrapper.so
ldd saxpy

./saxpy
