#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define DEFAULT_NTHREADS 128

typedef struct Matrix{
    int** mat; // matrix
    int r; // num of row
    int c; // num of column
}Matrix;

Matrix* New_Matrix(int r, int c){
    if(r <= 0 || c <= 0)
        return (Matrix*)1;
    Matrix* m = (Matrix*) malloc(sizeof(Matrix));
    if(m == NULL)  return NULL;
    m->r = r;
    m->c = c;
    m->mat = (int**) malloc(sizeof(int*) * r);
    if(m->mat == NULL)  return NULL;
    for(int i=0;i<r;i++){
        m->mat[i] = (int*) calloc(c, sizeof(int));
        if(m->mat[i] == NULL)  return NULL;
    }
    return m;
}

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

Work* New_Work_Array(int n, Matrix* m1, Matrix* m2, Matrix* prod){
    Work* new_works = (Work*) malloc(sizeof(Work) * n);
    if(new_works == NULL)  return NULL;
    for(int i=0;i<n;i++){
        new_works[i].m1 = m1->mat;
        new_works[i].m2 = m2->mat;
        new_works[i].prod = prod->mat;
        new_works[i].r = m1->r;
        new_works[i].c = m2->c;
        new_works[i].k = m1->c;
        new_works[i].nthreads = n;
        new_works[i].no = i;
    }
    return new_works;
}

void* multiply(void* void_work){
    Work* work = (Work*) void_work;
    int count = work->no;
    while(count < work->r * work->c){
        int r = count / work->c;  // current row
        int c = count % work->c;  // current column
        for(int i=0;i<work->k;i++){
            work->prod[r][c] += work->m1[r][i] * work->m2[i][c];
        }
        count += work->nthreads;
    }
    return NULL;
}

Matrix* matrix_multiplier(Matrix* m1, Matrix* m2, int nthreads){
    int n = m1->c;
    if(m1->c != m2->r || m1->r <= 0 || m1->c <=0 || m2->c <= 0)
        return (Matrix*)1;
    Matrix* prod = New_Matrix(m1->r, m2->c);
    if(prod == NULL)  return NULL;

    if(nthreads == 0) // nthreads = min(default, m1->r * m2->c)
        nthreads = DEFAULT_NTHREADS < m1->r * m2->c ? DEFAULT_NTHREADS : m1->r * m2->c;

    Work* works = New_Work_Array(nthreads, m1, m2, prod);
    pthread_t threads[nthreads];
    for(int i=0;i<nthreads;i++){
        pthread_create(&threads[i], NULL, multiply, (void*)&works[i]);
    }

    for(int i=0;i<nthreads;i++){
        pthread_join(threads[i], NULL);
    }
    free(works);
    return prod;
}

Matrix* array_to_matrix(int* p, int r, int c){
    Matrix* m = New_Matrix(r,c);
    if(m == NULL)  return NULL;
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            m->mat[i][j] = p[i*c + j];
        }
    }
    return m;
}

int main(){
    int a[6] = {1,2,3,4,5,6};
    int b[6] = {1,2,3,4,5,6};
    Matrix* m1 = array_to_matrix(a,3,2);
    Matrix* m2 = array_to_matrix(b,2,3);
    Matrix* result = matrix_multiplier(m1,m2, 0);
    if(result == 1){
        printf("input error\n");
        return 0;
    }
    for(int i=0;i<result->r;i++){
        for(int j=0;j<result->c;j++){
            printf("%d ",result->mat[i][j]);
        }
        printf("\n");
    }
    return 0;
}

