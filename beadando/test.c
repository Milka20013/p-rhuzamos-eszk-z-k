#include <stdio.h>
#include <time.h>
void multiply(int *aArr, int *bArr, int n, int k, int *result);
void multiply4(int *aArr, int *bArr, int n, int k, int *result);
void addSubResults(int col, int row, int subResults[col][row], int *result);
void addSubResults8(int col, int row, int subResults[col][row], int *result);
int concatenate(int x, int y);

int main(void)
{
    /*int n = 8;
    int k = 8;
    int aArr[] = {5, 6, 1, 6, 1, 2, 3, 4};
    int bArr[] = {7, 2, 4, 5, 1, 2, 3, 4};
    int result[n + k];
    long a = 123456789;
    long b = 123456789;*/

    int n = 2;
    int k = 2;
    int aArr[] = {9999, 9999};
    int bArr[] = {9999, 9999};
    int result[n + k];
    multiply4(aArr, bArr, n, k, result);
    /*clock_t start = clock();
    for (int i = 0; i < 1000000; i++)
    {
        multiply(aArr, bArr, n, k, result);
    }
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nProgram Execution time is: %0.3lf seconds or %0.3lf milliseconds", time_spent, time_spent * 1000);
    start = clock();
    for (int i = 0; i < 1; i++)
    {
        int c = a * b;
    }
    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nProgram Execution time is: %0.3lf seconds or %0.3lf milliseconds\n", time_spent, time_spent * 1000);
    */
    /*for (int i = 0; i < n + k; i++)
    {
        printf("%d", result[i]);
    }*/
}

void multiply(int *aArr, int *bArr, int n, int k, int *result)
{
    int subResults[k][n + k];
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
    int subResults[k][n + 1];
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
        digits = aArr[i];
        for (int j = n; j >= 1; j--)
        {
            tmp = aArr[j - 1] * digits + carry;
            tenThousandRem = tmp % 10000;
            subResults[i][j] = tenThousandRem;
            carry = (tmp - tenThousandRem) / 10000;
            subResults[i][j - 1] = carry;
        }
    }
    addSubResults8(k, n + k, subResults, result);
}

void addSubResults(int col, int row, int subResults[col][row], int *result)
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

void addSubResults8(int col, int row, int subResults[col][row], int *result)
{
    int tmp = 0;
    int carry = 0;
    int billionRemainder;
    for (int i = row - 1; i >= 0; i--)
    {
        for (int j = 1; j < col; j++)
        {
            tmp = subResults[j][i] + (subResults[j][i - 1] / 10) + carry;
            billionRemainder = tmp % 1000000000;
            result[i] = billionRemainder;
            carry = (tmp - billionRemainder) / 1000000000;
        }
    }
}

int concatenate(int x, int y)
{
    int pow = 10;
    while (y >= pow)
        pow *= 10;
    return x * pow + y;
}