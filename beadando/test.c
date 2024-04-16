#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int *createArray1FromStr(char *str, int *size);
int *createArray4FromStr(char *str, int *size);
void multiply(int *aArr, int *bArr, int n, int k, int *result);
void multiply4(int *aArr, int *bArr, int n, int k, int *result);
void addSubResults(int col, int row, int **subResults, int *result);
void addSubResults4(int row, int col, int **subResults, int *result);

int main(void)
{
    int n;
    int *aArr = createArray4FromStr("72", &n);
    int k;
    int *bArr = createArray4FromStr("72", &k);
    int result[n + k];
    clock_t start = clock();
    long long asd = 640000000000;
    int asd2 = 64;
    long long t;
    int t2;
    for (int i = 0; i < 100000000; i++)
    {
        //multiply4(aArr, bArr, n, k, result);
        t = asd*asd;
    }
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nProgram Execution time is: %0.3lf seconds or %0.3lf milliseconds\n", time_spent, time_spent * 1000);
    /*for (int i = 0; i < n + k; i++)
    {
        printf(" %d ", result[i]);
    }*/
}

void multiply(int *aArr, int *bArr, int n, int k, int *result)
{
    int **subResults = (int **)malloc(k * sizeof(int *));
    if (subResults == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    for (int i = 0; i < k; i++)
    {
        subResults[i] = (int *)malloc((n + k) * sizeof(int));
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

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < n + k; j++)
        {
            subResults[i][j] = 0;
        }

        digit = bArr[i];
        for (int j = n - 1; j >= 0; j--)
        {
            tmp = aArr[j] * digit + carry;
            tenRemainder = tmp % 10;
            subResults[i][j + i + 1] = tenRemainder;
            carry = (tmp - tenRemainder) / 10;
        }
        subResults[i][i] = carry;
        carry = 0;
    }
    /*for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < n + k; j++)
        {
            printf("%d", subResults[i][j]);
        }
        printf("\n");
    }*/
    addSubResults(k, n + k, subResults, result);
}

void multiply4(int *aArr, int *bArr, int n, int k, int *result)
{
    int **subResults = (int **)malloc(k * sizeof(int *));
    if (subResults == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    for (int i = 0; i < k; i++)
    {
        subResults[i] = (int *)malloc((n + 1) * sizeof(int));
        if (subResults[i] == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
    }
    int tmp;
    int digits;
    int carry = 0;
    int tenThousandRem;
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < n + 1; j++)
        {
            subResults[i][j] = 0;
        }
        digits = bArr[i];
        for (int j = n; j >= 1; j--)
        {
            tmp = aArr[j - 1] * digits + subResults[i][j];
            tenThousandRem = tmp % 10000;
            subResults[i][j] = tenThousandRem;
            carry = (tmp - tenThousandRem) / 10000;
            subResults[i][j - 1] = carry;
        }
        carry = 0;
    }
    /*for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < n + 1; j++)
        {
            printf(" %d ", subResults[i][j]);
        }
        printf("\n");
    }*/
    addSubResults4(k, n + 1, subResults, result);
}

void addSubResults(int col, int row, int **subResults, int *result)
{
    int tmp = 0;
    int carry = 0;
    int tenRemainder;
    for (int i = row - 1; i >= 0; i--)
    {
        tmp = 0;
        for (int j = 0; j < col; j++)
        {
            tmp += subResults[j][i];
        }
        tmp += carry;
        tenRemainder = tmp % 10;
        result[i] = tenRemainder;
        carry = (tmp - tenRemainder) / 10;
    }
}

void addSubResults4(int row, int col, int **subResults, int *result)
{
    int tmp = 0;
    int carry = 0;
    int tenThousandRem;
    /*printf(" %d %d", row, col);
    printf("\n");*/
    for (int i = col + col - 2; i >= 0; i--)
    {
        tmp = carry;
        for (int j = row - 1; j >= 0; j--)
        {
            int add = (i - j > col - 1) || (i - j < 0) ? 0 : subResults[j][i - j];
            tmp += add;
        }
        tenThousandRem = tmp % 10000;
        // printf(" %d ", tenThousandRem);
        result[i] = tenThousandRem;
        carry = (tmp - tenThousandRem) / 10000;
    }

    for (int i = 0; i < row; i++) {
        free(subResults[i]);
    }
    free(subResults);
}

int *createArray1FromStr(char *str, int *size)
{
    int length = strlen(str);

    int arraySize = length;
    *size = arraySize;
    int *array = (int *)malloc(arraySize * sizeof(int));
    if (array == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    int num = 0;
    for (int i = 0; i < length; i++)
    {
        num = str[i] - '0';
        array[i] = num;
    }
    return array;
}

int *createArray4FromStr(char *str, int *size)
{
    int length = strlen(str);

    int remainder = length % 4;
    int arraySize = length / 4 + (remainder > 0);
    *size = arraySize;
    int *array = (int *)malloc(arraySize * sizeof(int));

    int num = 0;

    if (remainder == 0)
    {
        remainder = 4;
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
    for (int i = remainder; i < length; i += 4)
    {
        num = 0;
        for (int j = 0; j < 4; j++)
        {
            num = num * 10 + (str[i + j] - '0');
        }
        array[k] = num;
        k++;
    }

    return array;
}