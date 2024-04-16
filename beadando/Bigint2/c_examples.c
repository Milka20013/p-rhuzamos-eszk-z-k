#include "bigint.h"
#include "time.h"
#include <stdio.h>

int main(){
    char buf[65536];

    /* neat trick to avoid having to write &a, &b, &c everywhere */
    bigint a[1], b[1], c[1];

    /* bigints have to be initialized (same as memset'ed to zero) */
    bigint_init(a);
    bigint_init(b);
    bigint_init(c);

    /* create bigint from string */
    bigint_from_str(a, "72");
    bigint_from_str(b, "72");

    /* c = a * b */
    /* first parameter is destination parameter */
    clock_t start = clock();
    for (int i = 0; i < 10000000; i++)
    {
        bigint_mul(c, a, b);
    }
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nProgram Execution time is: %0.3lf seconds or %0.3lf milliseconds\n", time_spent, time_spent * 1000);
    
    bigint_free(a);
    bigint_free(b);
    bigint_free(c);

    return 0;
}
