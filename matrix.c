#include <stdio.h>
#include <string.h>
#include "include/matrix/matrix.h"
#include "include/func.h"

Matrix* matrix_create(size_t rows, size_t cols, size_t element_size,
                      void (*print_element)(void*),
                      void (*add_elements)(void*, void*, void*),
                      void (*multiply_elements)(void*, void*, void*)){

    if (rows <= 0 || cols <= 0){
        error_print(2);
        return NULL;
    }

    Matrix* matrix = (Matrix *)malloc(sizeof(Matrix));

    if(!matrix){
        error_print(3);
        return NULL;
    }
    if(element_size == 0){
        error_print(4);
        return NULL;
    }

    matrix->data = malloc(element_size * rows * cols);

    if(!matrix->data){
        free(matrix);
        return NULL;
    }

    matrix->rows = rows;
    matrix->cols = cols;
    matrix->element_size = element_size;

    matrix->print_element = print_element;
    matrix->add_elements = add_elements;
    matrix->multiply_elements = multiply_elements;

    return matrix;

}

void push_back(Matrix* mat, void* item, int row, int col)
{
    if(mat == NULL || item == NULL){
        return;
    }
    if (row < 0 || row > mat->rows || col < 0 || col > mat->cols){
        error_print(6);
        return;
    }

    char* target = ((char*)((mat)->data) + ((row) * (mat)->cols + (col)) * (mat)->element_size); // Итерируемся до места добавления нового элемента
    memcpy(target, item, mat -> element_size); // Добавляем элемент

    return;
}

void* element_get(Matrix* mat, int row, int col)
{
    if(mat == NULL){
        return NULL;
    }
    if (row < 0 || row > mat->rows || col < 0 || col > mat->cols){
        error_print(6);
        return NULL;
    }

    return ((char*)((mat)->data) + ((row) * (mat)->cols + (col)) * (mat)->element_size);
}

void print_matrix(Matrix* mat) {
    if (mat == NULL || mat -> print_element == NULL) {
        return;
    }
    for(int i = 0; i < mat->rows; i++){
        printf("|");
        for(int j = 0; j < mat->cols; j++){
            void* elem = element_get(mat, i, j);
            mat -> print_element(elem);
            if(j + 1 != mat->cols){
                printf(" ");
            }
        }
        printf("|\n");
    }
}

//((char*)((matrix)->data) + ((row) * (matrix)->cols + (col)) * (matrix)->element_size)

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