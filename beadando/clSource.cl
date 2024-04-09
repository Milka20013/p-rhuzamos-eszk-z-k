__kernel void hello_kernel(__global float *a, __global float *b,
                           __global float *c, int n) {
  int i = get_global_id(0);
  int j = get_global_id(1);
  for (int k = 0; k < n; k++) {
    c[i + k * j] = a[i + k * j] + b[i + k * j];
  }
}