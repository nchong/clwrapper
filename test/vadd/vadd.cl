__kernel void vadd(__global int *x, __global int *y, __global int *z, int n) {
  int i = get_global_id(0);
  if (i < n) {
    z[i] = x[i] + y[i];
  }
}
