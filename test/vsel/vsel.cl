__kernel void vsel(__global float4 *v, __global float4 *w, __global int4 *c, __global float4 *r) {
  r[0] = select(v[0],w[0],c[0]);
}
