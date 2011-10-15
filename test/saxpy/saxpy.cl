__kernel void saxpy(__global float *x, __global float *y, int n, float a) {
  int i = get_global_id(0);
  if (i < n) {
    y[i] += a * x[i];
  }
}
