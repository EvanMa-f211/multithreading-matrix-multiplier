#include "matrix_multiplier.h"

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
    if(m1 == NULL || m2 == NULL)  return (Matrix*)1;
    int n = m1->c;
    if(m1->c != m2->r || m1->r <= 0 || m1->c <=0 || m2->c <= 0)
        return (Matrix*)1;
    Matrix* prod = New_Matrix(m1->r, m2->c);
    if(prod == NULL)  return NULL;

    if(nthreads == 0) // set to default
        nthreads = DEFAULT_NTHREADS;

    if(nthreads > m1->r * m2->c) // nthreads = min(nthreads, m1->r * m2->c)
        nthreads = m1->r * m2->c;

    Work* works = New_Work_Array(nthreads, m1, m2, prod);
    if(works == NULL)  return NULL;
    
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





