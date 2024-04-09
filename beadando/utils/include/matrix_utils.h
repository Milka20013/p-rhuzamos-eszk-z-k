#ifndef MATRIX_UTILS.H
#define MATRIX_UTILS .H

#include <stdlib.h>
#include <stdio.h>
typedef struct
{
    unsigned M;
    unsigned N;
    float *data;
} MatrixF;

/*
    Creates a matrix with dimension MxN
*/
MatrixF create_matrix(unsigned M, unsigned N);

/*
    Get the matrix element's pointer at position (m,n)
*/
float *get_matrix_element(MatrixF *matrix, unsigned m, unsigned n);

/*
    Prints the matrix to the console
*/
void print_matrix(MatrixF *matrix);
/*
    Free the memory of the matrix
*/
void delete_matrix(MatrixF *matrix);

#endif