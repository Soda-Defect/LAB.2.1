#include "include/matrix.h"

Matrix* matrix_create(size_t rows, size_t cols, size_t element_size,
                      void (*print_element)(void*),
                      void (*add_elements)(void*, void*, void*),
                      void (*multiply_elements)(void*, void*, void*)){

    if (rows <= 0 || cols <= 0){
        printf("ОШИБКА: Размеры матрицы должны быть положительными!\n");
        return NULL;
    }

    Matrix* matrix = (Matrix *)malloc(sizeof(Matrix));

    if(!matrix){
        printf("Ошибка выделения памяти для матрицы!\n");
        return NULL;
    }
    if(element_size == 0){
        printf("ОШИБКА: Размер элемента должен быть больше нуля!\n");
        return NULL;
    }

    matrix->data = malloc(element_size * rows * cols);

    if(!matrix->data){
        free(matrix);
        return NULL;
    }

    matrix->rows = rows;
    matrix->cols = cols;
    matrix->element_size;

    matrix->print_element = print_element;
    matrix->add_elements = add_elements;
    matrix->multiply_elements = multiply_elements;

    return matrix;

}

void matrix_free(Matrix* mat)
{
    if (mat != NULL) {
        if (mat -> data != NULL) {
            free(mat -> data);
        }
        free(mat);
    }
    return;
}