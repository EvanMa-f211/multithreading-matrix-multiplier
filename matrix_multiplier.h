#ifndef PARALLEL_MATRIX_MULTIPLIER
#define PARALLEL_MATRIX_MULTIPLIER

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define DEFAULT_NTHREADS 128

typedef struct Matrix{
    int** mat; // matrix
    int r; // num of row
    int c; // num of column
}Matrix;

Matrix* New_Matrix(int r, int c);

Matrix* array_to_matrix(int* p, int r, int c);

typedef struct Work{
    int** m1;
    int** m2;
    int** prod;
    int r; // m1->r = prod->r
    int c; // m2->c = prod->c
    int k; // m1->r = m2->c = k
    int nthreads; // num of threads
    int no; // serial number
}Work;

Work* New_Work_Array(int n, Matrix* m1, Matrix* m2, Matrix* prod);


void* multiply(void* void_work);

Matrix* matrix_multiplier(Matrix* m1, Matrix* m2, int nthreads);

#endif