#include "matrix.h"

Matrix* matrix_create(int rows, int cols)
{
    Matrix* matrix = (Matrix *)malloc(sizeof(Matrix));

    if(matrix == NULL){
        return NULL;
    }

    matrix->rows = rows;
    matrix->cols = cols;


}