#include "matrix.h"


int** matrix_alloc(int m,int n)
{
    int i;
    int **tmp;

    tmp = calloc( m, sizeof(int* ) );
    for(i=0;i<m;i++){
        tmp[i]=calloc( n, sizeof(int) );
    }
    return tmp;
}


void matrix_dealloc(int **mat,int m)
{
    int i;
    for (i=0;i<m;i++)
        free(mat[i]);
    free(mat);
}
