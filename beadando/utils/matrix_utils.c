#include "include/matrix_utils.h"

MatrixF create_matrix(unsigned M, unsigned N)
{
    MatrixF matrix;
    matrix.M = M;
    matrix.N = N;
    matrix.data = (float *)calloc(M * N, sizeof(int));
    return matrix;
}

float *get_matrix_element(MatrixF *matrix, unsigned m, unsigned n)
{
    return &(matrix->data[m * matrix->N + n]);
}

void print_matrix(MatrixF *matrix)
{
    for (unsigned i = 0; i < matrix->M; i++)
    {
        for (unsigned j = 0; j < matrix->N; j++)
        {
            printf(" %0.2f ", *get_matrix_element(matrix, i, j));
        }
    }
}

void delete_matrix(MatrixF *matrix)
{
    free(matrix->data);
}