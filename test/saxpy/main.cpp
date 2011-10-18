#include "clwrapper.h"

#include <cassert>
#include <cmath>
#include <cstdio>

void host_saxpy(float *x, float *y, int n, float a) {
  for (int i=0; i<n; i++) {
    y[i] += a * x[i];
  }
}

int main() {
  // test data
  int N = 16;
  float *x = new float[N];
  float *y = new float[N];
  float *expected = new float[N];
  float a = 3.14;
  for (int i=0; i<N; i++) {
    x[i] = i;
    y[i] = expected[i] = N-i;
  }
  host_saxpy(x, expected, N, a);

  // initialise for device 0 on platform 0, with profiling (for timing) on.
  // this creates a context and command queue
  int platform = 0;
  int device = 0;
  bool profiling = true;
  CLWrapper clw(platform, device, profiling);

  // compile the OpenCL code
  const char *filename = "saxpy.cl";
  cl_program program = clw.compile(filename);

  // generate all kernels
  clw.create_all_kernels(program);

  // get handlers to kernels
  cl_kernel saxpy = clw.kernel_of_name("saxpy");

  // create some memory objects on the device
  cl_mem d_x = clw.dev_malloc(sizeof(float)*N, CL_MEM_READ_ONLY);
  cl_mem d_y = clw.dev_malloc(sizeof(float)*N, CL_MEM_READ_WRITE);

  // memcpy into these objects (you can time these if profiling is on)
  float memcpy_time  = clw.memcpy_to_dev(d_x, sizeof(float)*N, x);
        memcpy_time += clw.memcpy_to_dev(d_y, sizeof(float)*N, y);

  // set kernel arguments
  clw.kernel_arg(saxpy, d_x, d_y, N, a);

  // run the kernel and time it since profiling is on
  cl_uint dim = 1;
  size_t global_work_size = N;
  size_t local_work_size  = N; //NB this means N cannot exceed the maximum worksize of the device
  float kernel_time = clw.run_kernel_with_timing(saxpy, dim, &global_work_size, &local_work_size);

  // memcpy back the result
  memcpy_time += clw.memcpy_from_dev(d_y, sizeof(float)*N, y);

  // check results
  float e = 0.0001;
  for (int i=0; i<N; i++) {
    assert(abs(y[i] - expected[i]) < e);
  }
  printf("TEST PASSED\n");

  // print out timing results
  printf("memcpy: %f ms\n", memcpy_time);
  printf("kernel: %f ms\n", kernel_time);

  // cleanup
  delete[] x;
  delete[] y;
  delete[] expected;
  // device objects will be auto-deleted when clw is destructed
  // or, we can do it manually like this:
  // clw.dev_free(d_x);
  return 0;
}

