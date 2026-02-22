#include "matrix.h"

Matrix* matrix_create(size_t rows, size_t cols, size_t element_size,
                      void (*print_element)(void*),
                      void (*add_elements)(void*, void*, void*),
                      void (*multiply_elements)(void*, void*, void*),
                      double (*norm_element)(void*),
                      void (*set_zero)(void*),
                      void (*copy_element)(void*, void*)){

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
    matrix->norm_element = norm_element;
    matrix->set_zero = set_zero;
    matrix->copy_element = copy_element;

    return matrix;

}