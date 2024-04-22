#include "../include/bigint_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void multiply_int_big_nums(int *aArr, int *bArr, int a, int b, int *result)
{
    int **subResults = (int **)malloc(b * sizeof(int *));
    if (subResults == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    for (int i = 0; i < b; i++)
    {
        subResults[i] = (int *)malloc((a + b) * sizeof(int));
        if (subResults[i] == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
    }
    int tmp;
    int digit;
    int carry = 0;
    int tenRemainder;

    for (int i = 0; i < b; i++)
    {
        for (int j = 0; j < a + b; j++)
        {
            subResults[i][j] = 0;
        }

        digit = bArr[i];
        for (int j = a - 1; j >= 0; j--)
        {
            tmp = aArr[j] * digit + carry;
            tenRemainder = tmp % 10;
            subResults[i][j + i + 1] = tenRemainder;
            carry = (tmp - tenRemainder) / 10;
        }
        subResults[i][i] = carry;
        carry = 0;
    }
    /*for (int i = 0; i < b; i++)
    {
        for (int j = 0; j < a + b; j++)
        {
            printf("%d", subResults[i][j]);
        }
        printf("\n");
    }*/
    add_int_subresults(b, a + b, subResults, result);
}

void multiply_int_n_big_nums(int *aArr, int *bArr, int a, int b, int n, int *result)
{
    int **subresults = (int **)malloc(b * sizeof(int *));
    if (subresults == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    for (int i = 0; i < b; i++)
    {
        subresults[i] = (int *)malloc((a + 1) * sizeof(int));
        if (subresults[i] == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
    }
    int tmp;
    int digits;
    int carry = 0;
    int remNumber = pow(10, n) + 0.5;
    int rem;
    for (int i = 0; i < b; i++)
    {
        for (int j = 0; j < a + 1; j++)
        {
            subresults[i][j] = 0;
        }
        digits = bArr[i];
        for (int j = a; j >= 1; j--)
        {
            tmp = aArr[j - 1] * digits + subresults[i][j];
            rem = tmp % remNumber;
            subresults[i][j] = rem;
            carry = (tmp - rem) / remNumber;
            subresults[i][j - 1] = carry;
        }
        carry = 0;
    }
    for (int i = 0; i < b; i++)
    {
        for (int j = 0; j < a + 1; j++)
        {
            printf(" %d ", subresults[i][j]);
        }
        printf("\n");
    }
    add_int_n_subresults(b, a + 1, n, subresults, result);
}

void multiply_long_long_n_big_nums(long long *aArr, long long *bArr, int a, int b, int n, long long *result)
{
    long long **subResults = (long long **)malloc(b * sizeof(long long *));
    if (subResults == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    for (int i = 0; i < b; i++)
    {
        subResults[i] = (long long *)malloc((a + 1) * sizeof(long long));
        if (subResults[i] == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
    }
    long long tmp;
    long long digits;
    long long carry = 0ll;
    long long remNumber = pow(10, n) + 0.5;
    long long rem;
    for (int i = 0; i < b; i++)
    {
        for (int j = 0; j < a + 1; j++)
        {
            subResults[i][j] = 0;
        }
        digits = bArr[i];
        for (int j = a; j >= 1; j--)
        {
            tmp = aArr[j - 1] * digits + subResults[i][j];
            rem = tmp % remNumber;
            subResults[i][j] = rem;
            carry = (tmp - rem) / remNumber;
            subResults[i][j - 1] = carry;
        }
        carry = 0;
    }
    /*for (int i = 0; i < b; i++)
    {
        for (int j = 0; j < a + 1; j++)
        {
            printf(" %d ", subResults[i][j]);
        }
        printf("\n");
    }*/
    add_long_long_n_subresults(b, a + 1, n, subResults, result);
}

void add_int_subresults(int col, int row, int **subresults, int *result)
{
    int tmp = 0;
    int carry = 0;
    int tenRemainder;
    for (int i = row - 1; i >= 0; i--)
    {
        tmp = 0;
        for (int j = 0; j < col; j++)
        {
            tmp += subresults[j][i];
        }
        tmp += carry;
        tenRemainder = tmp % 10;
        result[i] = tenRemainder;
        carry = (tmp - tenRemainder) / 10;
    }
}

void add_int_n_subresults(int row, int col, int n, int **subresults, int *result)
{
    int tmp = 0;
    int carry = 0;
    int remNumber = pow(10, n) + 0.5;
    int rem;
    for (int i = col + col - 2; i >= 0; i--)
    {
        tmp = carry;
        for (int j = row - 1; j >= 0; j--)
        {
            int add = (i - j > col - 1) || (i - j < 0) ? 0 : subresults[j][i - j];
            tmp += add;
        }
        rem = tmp % remNumber;
        result[i] = rem;
        carry = (tmp - rem) / remNumber;
    }

    for (int i = 0; i < row; i++)
    {
        free(subresults[i]);
    }
    free(subresults);
}

void add_long_long_n_subresults(int row, int col, int n, long long **subresults, long long *result)
{
    long long tmp = 0;
    long long carry = 0;
    long long remNumber = pow(10, n) + 0.5;
    long long rem;
    for (int i = col + col - 2; i >= 0; i--)
    {
        tmp = carry;
        for (int j = row - 1; j >= 0; j--)
        {
            int add = (i - j > col - 1) || (i - j < 0) ? 0 : subresults[j][i - j];
            tmp += add;
        }
        rem = tmp % remNumber;
        result[i] = rem;
        carry = (tmp - rem) / remNumber;
    }

    /*for (int i = 0; i < row; i++)
    {
        free(subResults[i]);
    }
    free(subResults);*/
}

unsigned char *generate_random_digits(int char_length, unsigned int seed)
{
    int lower = 49;
    int upper = 57;
    int range = upper - lower + 1;
    srand(seed);
    unsigned char *stream = malloc(char_length + 1);
    for (int i = 0; i < char_length; i++)
    {
        stream[i] = (rand() % range) + lower;
    }
    stream[char_length] = '\0';
    return stream;
}

int *create_int_array_n_from_str(char *str, int n_digits, int *size)
{
    int length = strlen(str);

    int remainder = length % n_digits;
    int arraySize = length / n_digits + (remainder > 0);
    *size = arraySize;
    int *array = (int *)malloc(arraySize * sizeof(int));

    int num = 0;

    if (remainder == 0)
    {
        remainder = n_digits;
    }
    for (int i = 0; i < remainder; i++)
    {
        num = num * 10 + (str[i] - '0');
    }
    array[0] = num;

    if (array == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    int k = 1;
    for (int i = remainder; i < length; i += n_digits)
    {
        num = 0;
        for (int j = 0; j < n_digits; j++)
        {
            num = num * 10 + (str[i + j] - '0');
        }
        array[k] = num;
        k++;
    }

    return array;
}

long long *create_long_long_array_n_from_str(char *str, int n_digits, int *size)
{
    int length = strlen(str);
    int remainder = length % n_digits;
    int arraySize = length / n_digits + (remainder > 0);
    *size = arraySize;
    long long *array = (long long *)malloc(arraySize * sizeof(long long));

    long long num = 0ll;
    if (remainder == 0)
    {
        remainder = n_digits;
    }
    for (int i = 0; i < remainder; i++)
    {
        num = num * 10ll + (long long)(str[i] - '0');
    }
    array[0] = num;

    int k = 1;
    for (int i = remainder; i < length; i += n_digits)
    {
        num = 0ll;
        for (int j = 0; j < n_digits; j++)
        {
            num = num * 10ll + (long long)(str[i + j] - '0');
        }
        array[k] = num;
        k++;
    }
    return array;
}
