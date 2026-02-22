#include "matrix.h"

Matrix* matrix_create(int rows, int cols, int type)
{
    if (rows <= 0 || cols <= 0){
        printf("ОШИБКА: Размеры матрицы должны быть положительными!\n");
        return NULL;
    }

    Matrix* matrix = (Matrix *)malloc(sizeof(Matrix));

    if(!matrix){
        printf("Ошибка выделения памяти для матрицы!\n");
        return NULL;
    }

    matrix->rows = rows;
    matrix->cols = cols;
    matrix->data = (MatrixElement**)malloc(rows * sizeof(MatrixElement*));

    if(!matrix->data){
        free(matrix);
        printf("Ошибка выделения памяти для строк матрицы!\n");
        return NULL;
    }

    for(int i = 0; i < rows; i++){
        matrix->data[i] = (MatrixElement*)malloc(cols * sizeof(MatrixElement));
        if(!matrix->data[i]){
            for(int j = 0; j < i; j++){
                free(matrix->data[j]);
            }
            free(matrix->data);
            free(matrix);
            printf("Ошибка выделения памяти для строки %d матрицы!\n", i);
            return NULL;
        }

        for(int j = 0; j < cols; j++){
            if(type == 1){
                matrix->data[i][j].type = TYPE_INT;
                matrix->data[i][j].data.int_value = 0;
            }
            else{
                matrix->data[i][j].type = TYPE_DOUBLE;
                matrix->data[i][j].data.int_value = 0.0;
            }
        }
    }

    return matrix;

}