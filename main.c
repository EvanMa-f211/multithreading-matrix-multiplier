#include "matrix_multiplier.h"

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