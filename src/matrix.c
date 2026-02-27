#include <stdio.h>
#include <string.h>
#include "../include/matrix/matrix.h"
#include "../include/func.h"

Matrix* matrix_create(size_t razm, size_t element_size,
                      void (*print_element)(void*),
                      void (*add_elements)(void*, void*, void*),
                      void (*multiply_elements)(void*, void*, void*)){

    if (razm <= 0){
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

    matrix->data = malloc(element_size * razm * razm);

    if(!matrix->data){
        free(matrix);
        return NULL;
    }

    matrix->razm = razm;
    matrix->element_size = element_size;

    matrix->print_element = print_element;
    matrix->add_elements = add_elements;
    matrix->multiply_elements = multiply_elements;

    return matrix;

}

void push_el_matrix(Matrix* mat, void* item, int row, int col)
{
    if(mat == NULL || item == NULL){
        return;
    }
    if (row < 0 || row > mat->razm || col < 0 || col > mat->razm){
        error_print(6);
        return;
    }

    char* target = ((char*)((mat)->data) + ((row) * (mat)->razm + (col)) * (mat)->element_size); 
    memcpy(target, item, mat -> element_size); 
    return;
}

void* element_get(Matrix* mat, int row, int col)
{
    if(mat == NULL){
        return NULL;
    }
    if (row < 0 || row > mat->razm || col < 0 || col > mat->razm){
        error_print(6);
        return NULL;
    }

    return ((char*)((mat)->data) + ((row) * (mat)->razm + (col)) * (mat)->element_size);
}

Matrix* matrix_add(Matrix* mat_1, Matrix* mat_2)
{
    if(mat_1 == NULL || mat_2 == NULL || mat_1 -> add_elements == NULL || mat_2 -> add_elements == NULL){
        return NULL;
    }
    if(mat_1 -> razm != mat_2 -> razm){
        error_print(8);
        return NULL;
    }

    Matrix* result = matrix_create(mat_1 -> razm, mat_1 -> element_size, mat_1 -> print_element, mat_1 -> add_elements, mat_1 ->multiply_elements);
    if (result == NULL) {
        return NULL;
    }

    for(int i = 0; i < mat_1 -> razm; i++){
        for(int j = 0; j < mat_1 -> razm; j++){
            void* sum = malloc(mat_1 -> element_size);
            if(sum == NULL){
                return NULL;
            }

            void* elem_1 = element_get(mat_1, i, j);
            void* elem_2 = element_get(mat_2, i, j);

            mat_1 -> add_elements(sum, elem_1, elem_2);

            push_el_matrix(result, sum, i, j);
            free(sum);
        }
    }

    return result;
}

Matrix* matrix_mult(Matrix* mat_1, Matrix* mat_2)
{
    if(mat_1 == NULL || mat_2 == NULL || mat_1 -> add_elements == NULL || mat_1 -> multiply_elements == NULL){
        return NULL;
    }
    if(mat_1 -> razm != mat_2 -> razm){
        error_print(9);
        return NULL;
    }

    Matrix* result = matrix_create(mat_1 -> razm, mat_1 -> element_size, mat_1 -> print_element, mat_1 -> add_elements, mat_1 ->multiply_elements);
    if (result == NULL) {
        return NULL;
    }

    for(int i = 0; i < mat_1 -> razm; i++){
        for(int j = 0; j < mat_2 -> razm; j++){
            void* sum = malloc(mat_1 -> element_size);
            if(sum == NULL){
                return NULL;
            }
            memset(sum, 0, mat_1->element_size);
            for(int k = 0; k < mat_1 -> razm; k++){
                void* mult = malloc(mat_1 -> element_size);
                if(mult == NULL){
                    return NULL;
                }
                void* elem_1 = element_get(mat_1, i, k);
                void* elem_2 = element_get(mat_2, k, j);
                mat_1 -> multiply_elements(mult, elem_1, elem_2);
                mat_1 -> add_elements(sum, sum, mult);
                free(mult);
            }
            push_el_matrix(result, sum, i, j);
            free(sum);
        }
    }

    return result;
}

Matrix* matrix_transp(Matrix* mat_1)
{
    if(mat_1 == NULL){
        return NULL;
    }

    Matrix* result = matrix_create(mat_1 -> razm, mat_1 -> element_size, mat_1 -> print_element, mat_1 -> add_elements, mat_1 ->multiply_elements);
    if (result == NULL) {
        return NULL;
    }

    for(int i = 0; i < mat_1 -> razm; i++){
        for(int j = 0; j < mat_1 ->razm; j++){
            void* elem_1 = element_get(mat_1, i, j);
            push_el_matrix(result, elem_1, j, i);
        }
    }

    return result;
}

void matrix_add_line_comb(Matrix* mat_1, int rowIndex, int rowAlph, void* alhpa)
{
    if(mat_1 == NULL || mat_1 -> add_elements == NULL || mat_1 -> multiply_elements == NULL){
        return;
    }

    for(int j = 0; j < mat_1 -> razm; j++){
        void* elem_1 = element_get(mat_1, rowIndex, j);
        void* elem_2 = element_get(mat_1, rowAlph, j);

        void* mult = malloc(mat_1 -> element_size);
        if(mult == NULL){
            return;
        }
        mat_1 -> multiply_elements(mult, alhpa, elem_2);
        mat_1 -> add_elements(elem_1, elem_1, mult);
        push_el_matrix(mat_1, elem_1, rowIndex, j);
    }

}

void print_matrix(Matrix* mat) {
    if (mat == NULL || mat -> print_element == NULL) {
        return;
    }
    for(int i = 0; i < mat->razm; i++){
        printf("|");
        for(int j = 0; j < mat->razm; j++){
            void* elem = element_get(mat, i, j);
            mat -> print_element(elem);
            if(j + 1 != mat->razm){
                printf(" ");
            }
        }
        printf("|\n");
    }
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