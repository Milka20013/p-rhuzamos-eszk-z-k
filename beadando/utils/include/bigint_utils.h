#ifndef BIGINT_UTILS_H
#define BIGINT_UTILS_H

/*
    Multiplies two big numbers by the pen and paper method. An int array contains the big numbers' digits.
*/

void multiply_int_big_nums(int *aArr, int *bArr, int a, int b, int *result);
/*
    Multiplies two big numbers by the pen and paper method. An int array contains the big numbers' digits in chuncks of n.
*/

void multiply_int_n_big_nums(int *aArr, int *bArr, int a, int b, int n, int *result);
/*
    Multiplies two big numbers by the pen and paper method. A long long array contains the big numbers' digits in chuncks of n.
*/

void multiply_long_long_n_big_nums(long long *aArr, long long *bArr, int a, int b, int n, long long *result);
/*
    Adds the subresults of the multiplication in the pen and paper method.
*/

void add_int_subresults(int col, int row, int **subresults, int *result);
/*
    Adds the subresults of the multiplication in the pen and paper method in chunks of n.
*/

void add_int_n_subresults(int row, int col, int n, int **subresults, int *result);
/*
    Adds the subresults of the multiplication in the pen and paper method in chunks of n.
*/
void add_long_long_n_subresults(int row, int col, int n, long long **subresults, long long *result);

/*
    Generates a string with random chars ranging from 0-9. Like "063123".
*/
unsigned char *generate_random_digits(int char_length, unsigned int seed);

/*
    Creates an array of ints from string. Every n_digits of the string is an array item.
    If the string length is not divisible by n_digits, then the first array item contains the remainder number of digits.
    The length of the resulting array is in the size variable.
*/

int *create_int_array_n_from_str(char *str, int n_digits, int *size);

/*
    Creates an array of long longs from string. Every n_digits of the string is an array item.
    If the string length is not divisible by n_digits, then the first array item contains the remainder number of digits.
    The length of the resulting array is in the size variable.
*/

long long *create_long_long_array_n_from_str(char *str, int n_digits, int *size);

#endif