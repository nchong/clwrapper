#include "clwrapper.h"

#include <cassert>
#include <cstdio>

int main() {
  // test data
  int N = 8;
  size_t ArraySize = N * sizeof(int);
  int *x = new int[N];
  int *y = new int[N];
  int *z = new int[N];
  for (int i=0; i<N; i++) {
    x[i] = i;
    y[i] = N-i;
  }
  // expect vadd(x,y,z,N) to give z[i] = N, for all i

  // initialise for device 0 on platform 0, with profiling off
  // this creates a context and command queue
  int platform = 0;
  int device = 0;
  bool profiling = false;
  CLWrapper clw(platform, device, profiling);

  // compile the OpenCL code
  const char *filename = "vadd.cl";
  cl_program program = clw.compile(filename);

  // generate all kernels
  clw.create_all_kernels(program);

  // get handlers to kernels
  cl_kernel vadd = clw.kernel_of_name("vadd");

  // create some memory objects on the device
  cl_mem d_x = clw.dev_malloc(ArraySize, CL_MEM_READ_ONLY);
  cl_mem d_y = clw.dev_malloc(ArraySize, CL_MEM_READ_ONLY);
  cl_mem d_z = clw.dev_malloc(ArraySize);

  // memcpy into these objects
  clw.memcpy_to_dev(d_x, ArraySize, x);
  clw.memcpy_to_dev(d_y, ArraySize, y);

  // set kernel arguments
  clw.kernel_arg(vadd, d_x, d_y, d_z, N);

  // run the kernel
  cl_uint dim = 1;
  size_t global_work_size = N;
  size_t local_work_size  = N; //NB this means N cannot exceed the maximum worksize of the device
  clw.run_kernel(vadd, dim, &global_work_size, &local_work_size);

  // memcpy back the result
  clw.memcpy_from_dev(d_z, ArraySize, z);

  // check results
  for (int i=0; i<N; i++) {
    assert(z[i] == N);
  }
  printf("TEST PASSED\n");

  // cleanup
  delete[] x;
  delete[] y;
  delete[] z;
  // device objects will be auto-deleted when clw is destructed
  // or, we can do it manually like this:
  // clw.dev_free(d_x);
  return 0;
}

