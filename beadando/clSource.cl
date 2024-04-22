__kernel void hello_kernel(__global int *aArr, __global int *bArr,
                           __global int *result, __global int *subresults,
                           __global int *carries, int a, int b) {
  int i = get_global_id(0);

  int carry = 0;
  int digit = bArr[i];
  int tmp = 0;
  int tenRemainder = 0;
  for (int j = a - 1; j >= 0; j--) {
    tmp = aArr[j] * digit + carry;
    tenRemainder = tmp % 10;
    subresults[i * a + j] = tenRemainder;
    carry = (tmp - tenRemainder) / 10;
  }
  subresults[i * a] = carry;

  carries[i] = 0;
  result[i] = 0;
}