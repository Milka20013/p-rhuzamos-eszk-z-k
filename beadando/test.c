#include "utils/include/bigint_utils.h"

#include <time.h>
#include <stdio.h>

int main(void)
{
    const int length_int = 4;
    const int length_long_long = 9;
    const int length_str = 2048;
    unsigned char *str = generate_random_digits(length_str, 0);
    for (int i = 0; i < length_str; i++)
    {
        printf("%c", str[i]);
    }
    printf("\n");

    int n;
    int *aArr = create_int_array_n_from_str(str, length_int, &n);
    int k;
    int *bArr = create_int_array_n_from_str(str, length_int, &k);
    int ln;
    long long *lAarr = create_long_long_array_n_from_str(str, length_long_long, &ln);
    int lk;
    long long *lBarr = create_long_long_array_n_from_str(str, length_long_long, &lk);

    int result[n + k];
    long long resultL[ln + lk];

    clock_t start = clock();

    for (int i = 0; i < 1; i++)
    {
        multiply_int_big_nums(aArr, bArr, n, k, result);
        // multiply_int_n_big_nums(aArr, bArr, n, k, length_int, result);
        // multiply_long_long_n_big_nums(lAarr, lBarr, ln, lk, length_long_long, resultL);
    }
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nProgram Execution time is: %0.3lf seconds or %0.3lf milliseconds\n", time_spent, time_spent * 1000);
    for (int i = 0; i < ln + lk; i++)
    {
        printf(" %d ", resultL[i]);
    }
}