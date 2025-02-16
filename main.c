#include "matrix_multiplier.h"

int main(){
    int r1, c1, r2, c2;

    scanf("%d%d", &r1, &c1);
    Matrix* m1 = New_Matrix(r1, c1);
    for(int i=0; i<r1; i++){
        for(int j=0; j<c1; j++){
            scanf("%d", &m1->mat[i][j]);
        }
    }

    scanf("%d%d", &r2, &c2);
    Matrix* m2 = New_Matrix(r2, c2);
    for(int i=0; i<r2; i++){
        for(int j=0; j<c2; j++){
            scanf("%d", &m2->mat[i][j]);
        }
    }

    Matrix* ans = matrix_multiplier(m1,m2,0);
    if(ans == (Matrix*)1)
        printf("The matrices cannot be multiplied.\n");
    else{
        printf("%d %d\n", ans->r, ans->c);
        for(int i=0; i<ans->r; i++){
            for(int j=0; j<ans->c; j++){
                printf("%d ", ans->mat[i][j]);
            }
            printf("\n");
        }
    }

    return 0;
}