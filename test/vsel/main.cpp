#include "clwrapper.h"

#include <cassert>
#include <cstdio>

int main() {
  // ------------------------------------------------------------------------
  // Show that vector-vector comparisons use -1 for truth, 0 for false
  // ------------------------------------------------------------------------

  float v[4] = {1.0f, 2.0f, 3.0f, 4.0f};
  float w[4] = {5.0f, 6.0f, 7.0f, 8.0f};
  int   c[4] = {0,-1,0,-1};
  float r[4] = {0.0f, 0.0f, 0.0f, 0.0f};
  printf("v  = {%f, %f, %f, %f}\n", v[0], v[1], v[2], v[3]);
  printf("w  = {%f, %f, %f, %f}\n", w[0], w[1], w[2], w[3]);
  printf("c  = {%d, %d, %d, %d}\n", c[0], c[1], c[2], c[3]);
  printf("r  = {%f, %f, %f, %f}\n", r[0], r[1], r[2], r[3]);

  // initialise for device 0 on platform 0, with profiling off
  // this creates a context and command queue
  int platform = 0;
  int device = 1;
  bool profiling = false;
  CLWrapper clw(platform, device, profiling);

  // compile the OpenCL code
  const char *filename = "vsel.cl";
  cl_program program = clw.compile(filename);

  // generate all kernels
  clw.create_all_kernels(program);

  // get handlers to kernels
  cl_kernel vsel = clw.kernel_of_name("vsel");
  cl_kernel vlt  = clw.kernel_of_name("vlt");

  // create some memory objects on the device
  cl_mem d_v = clw.dev_malloc(4*sizeof(float), CL_MEM_READ_ONLY);
  cl_mem d_w = clw.dev_malloc(4*sizeof(float), CL_MEM_READ_ONLY);
  cl_mem d_c = clw.dev_malloc(4*sizeof(int),   CL_MEM_READ_ONLY);
  cl_mem d_r = clw.dev_malloc(4*sizeof(float));

  // memcpy into these objects
  clw.memcpy_to_dev(d_v, 4*sizeof(float), v);
  clw.memcpy_to_dev(d_w, 4*sizeof(float), w);
  clw.memcpy_to_dev(d_c, 4*sizeof(int),   c);
  clw.memcpy_to_dev(d_r, 4*sizeof(float), r);

  // set kernel arguments
  clw.kernel_arg(vsel, d_v, d_w, d_c, d_r);

  // run the kernel
  cl_uint dim = 1;
  size_t global_work_size = 1;
  size_t local_work_size  = 1;
  clw.run_kernel(vsel, dim, &global_work_size, &local_work_size);

  // memcpy back the result
  clw.memcpy_from_dev(d_r, 4*sizeof(float), r);

  // check result
  printf("r' = {%f, %f, %f, %f}\n", r[0], r[1], r[2], r[3]);

  // ------------------------------------------------------------------------

  // set kernel arguments
  clw.kernel_arg(vlt, d_v, d_w, d_c);

  // run the kernel
  // c = (v*v) < w
  // expecting { -1, -1, 0, 0 }
  clw.run_kernel(vlt, dim, &global_work_size, &local_work_size);

  // memcpy back the result
  clw.memcpy_from_dev(d_c, 4*sizeof(int), c);

  // check result
  printf("c' = {%d, %d, %d, %d}\n", c[0], c[1], c[2], c[3]);

  return 0;
}

