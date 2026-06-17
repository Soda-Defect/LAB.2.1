#include <stdio.h>
#include <string.h>
#include "../include/matrix/matrix.h"
#include "../include/interface.h"

Matrix* matrix_create(int dimension, TypeInfo* typeInfo, MatrixErrors* operationResult){

    if (dimension <= 0){
        *operationResult = INVALID_MATRIX_SIZE;
        return NULL;
    }

    if (typeInfo == NULL || typeInfo->size == 0) {
        *operationResult = INVALID_TYPE_INFO;
        return NULL;
    }

    Matrix* matrix = (Matrix *)malloc(sizeof(Matrix));

    if (matrix == NULL) {
        *operationResult = MEMORY_ALLOCATION_FAILED;
        return NULL;
    }

    matrix->data = malloc(typeInfo->size * dimension * dimension);

    if (matrix->data == NULL) {
        *operationResult = MEMORY_ALLOCATION_FAILED;
        free(matrix);
        return NULL;
    }

    matrix->dimension = dimension;
    matrix->typeInfo = typeInfo;

    *operationResult = MATRIX_OPERATION_OK;
    return matrix;

}

MatrixErrors push_el_matrix(Matrix* mat, void* item, size_t row, size_t col) {
    if (mat == NULL) {
        return MATRIX_NOT_DEFINED;
    }
    
    if (item == NULL) {
        return MATRIX_NOT_DEFINED;
    }
    
    if (row >= mat->dimension || col >= mat->dimension) {
        return INVALID_MATRIX_INDEX;
    }

    char* target = ((char*)(mat->data) + (row * mat->dimension + col) * mat->typeInfo->size); 
    memcpy(target, item, mat->typeInfo->size);
    
    return MATRIX_OPERATION_OK;
}

void* element_get(Matrix* mat, size_t row, size_t col, MatrixErrors* operationResult) {
    if (mat == NULL) {
        *operationResult = MATRIX_NOT_DEFINED;
        return NULL;
    }
    
    if (row >= mat->dimension || col >= mat->dimension) {
        *operationResult = INVALID_MATRIX_INDEX;
        return NULL;
    }

    *operationResult = MATRIX_OPERATION_OK;
    return ((char*)(mat->data) + (row * mat->dimension + col) * mat->typeInfo->size);
}

Matrix* matrix_add(Matrix* mat_1, Matrix* mat_2, MatrixErrors* operationResult) {
    if (mat_1 == NULL || mat_2 == NULL) {
        *operationResult = MATRIX_NOT_DEFINED;
        return NULL;
    }
    
    if (mat_1->typeInfo->add == NULL || mat_2->typeInfo->add == NULL) {
        *operationResult = OPERATION_NOT_DEFINED;
        return NULL;
    }
    
    if (mat_1->dimension != mat_2->dimension) {
        *operationResult = MATRIX_SIZE_MISMATCH;
        return NULL;
    }
    
    if (mat_1->typeInfo != mat_2->typeInfo) {
        *operationResult = INCOMPATIBLE_MATRIX_TYPES;
        return NULL;
    }

    Matrix* result = matrix_create(mat_1->dimension, mat_1->typeInfo, operationResult);
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < mat_1->dimension; i++) {
        for (size_t j = 0; j < mat_1->dimension; j++) {
            void* sum = malloc(mat_1->typeInfo->size);
            if (sum == NULL) {
                *operationResult = MEMORY_ALLOCATION_FAILED;
                matrix_free(result);
                return NULL;
            }

            MatrixErrors err;
            void* elem_1 = element_get(mat_1, i, j, &err);
            void* elem_2 = element_get(mat_2, i, j, &err);
            
            if (elem_1 == NULL || elem_2 == NULL) {
                free(sum);
                matrix_free(result);
                *operationResult = err;
                return NULL;
            }

            mat_1->typeInfo->add(sum, elem_1, elem_2);
            err = push_el_matrix(result, sum, i, j);
            free(sum);
            
            if (err != MATRIX_OPERATION_OK) {
                *operationResult = err;
                matrix_free(result);
                return NULL;
            }
        }
    }

    *operationResult = MATRIX_OPERATION_OK;
    return result;
}

Matrix* matrix_mult(Matrix* mat_1, Matrix* mat_2, MatrixErrors* operationResult) {    
    if (mat_1 == NULL || mat_2 == NULL) {
        *operationResult = MATRIX_NOT_DEFINED;
        return NULL;
    }
    
    if (mat_1->typeInfo->add == NULL || mat_1->typeInfo->multiply == NULL) {
        *operationResult = OPERATION_NOT_DEFINED;
        return NULL;
    }
    
    if (mat_1->dimension != mat_2->dimension) {
        *operationResult = MATRIX_SIZE_MISMATCH;
        return NULL;
    }
    
    if (mat_1->typeInfo != mat_2->typeInfo) {
        *operationResult = INCOMPATIBLE_MATRIX_TYPES;
        return NULL;
    }

    Matrix* result = matrix_create(mat_1->dimension, mat_1->typeInfo, operationResult);
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < mat_1->dimension; i++) {
        for (size_t j = 0; j < mat_2->dimension; j++) {
            void* sum = malloc(mat_1->typeInfo->size);
            if (sum == NULL) {
                *operationResult = MEMORY_ALLOCATION_FAILED;
                matrix_free(result);
                return NULL;
            }
            memset(sum, 0, mat_1->typeInfo->size);
            
            for (size_t k = 0; k < mat_1->dimension; k++) {
                void* mult = malloc(mat_1->typeInfo->size);
                if (mult == NULL) {
                    *operationResult = MEMORY_ALLOCATION_FAILED;
                    free(sum);
                    matrix_free(result);
                    return NULL;
                }
                
                MatrixErrors err;
                void* elem_1 = element_get(mat_1, i, k, &err);
                void* elem_2 = element_get(mat_2, k, j, &err);
                
                if (elem_1 == NULL || elem_2 == NULL) {
                    free(mult);
                    free(sum);
                    matrix_free(result);
                    *operationResult = err;
                    return NULL;
                }
                
                mat_1->typeInfo->multiply(mult, elem_1, elem_2);
                mat_1->typeInfo->add(sum, sum, mult);
                free(mult);
            }
            
            MatrixErrors err = push_el_matrix(result, sum, i, j);
            free(sum);
            
            if (err != MATRIX_OPERATION_OK) {
                *operationResult = err;
                matrix_free(result);
                return NULL;
            }
        }
    }

    *operationResult = MATRIX_OPERATION_OK;
    return result;
}

Matrix* matrix_transp(Matrix* mat_1, MatrixErrors* operationResult) {
    if (mat_1 == NULL) {
        *operationResult = MATRIX_NOT_DEFINED;
        return NULL;
    }

    Matrix* result = matrix_create(mat_1->dimension, mat_1->typeInfo, operationResult);
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < mat_1->dimension; i++) {
        for (size_t j = 0; j < mat_1->dimension; j++) {
            MatrixErrors err;
            void* elem_1 = element_get(mat_1, i, j, &err);
            if (elem_1 == NULL) {
                *operationResult = err;
                matrix_free(result);
                return NULL;
            }
            
            err = push_el_matrix(result, elem_1, j, i);
            if (err != MATRIX_OPERATION_OK) {
                *operationResult = err;
                matrix_free(result);
                return NULL;
            }
        }
    }

    *operationResult = MATRIX_OPERATION_OK;
    return result;
}

MatrixErrors matrix_multiply_const(Matrix* mat_1, int alpha) {
    if (mat_1 == NULL) {
        return MATRIX_NOT_DEFINED;
    }
    
    if (mat_1->typeInfo->mult_const == NULL) {
        return OPERATION_NOT_DEFINED;
    }

    for (size_t i = 0; i < mat_1->dimension; i++) {
        for (size_t j = 0; j < mat_1->dimension; j++) {
            void* elem_1 = (char*)mat_1->data + (i * mat_1->dimension + j) * mat_1->typeInfo->size;
            if (elem_1 == NULL) {
                return MATRIX_NOT_DEFINED;
            }
            mat_1->typeInfo->mult_const(elem_1, elem_1, alpha);
            push_el_matrix(mat_1, elem_1, i, j);
        }
    }
    
    return MATRIX_OPERATION_OK;
}

MatrixErrors print_matrix(Matrix* mat) {
    if (mat == NULL) {
        return MATRIX_NOT_DEFINED;
    }
    
    if (mat->typeInfo == NULL || mat->typeInfo->print == NULL) {
        return OPERATION_NOT_DEFINED;
    }
    
    for (size_t i = 0; i < mat->dimension; i++) {
        printf("|");
        for (size_t j = 0; j < mat->dimension; j++) {
            MatrixErrors err;
            void* elem = element_get(mat, i, j, &err);
            if (elem != NULL && err == MATRIX_OPERATION_OK) {
                mat->typeInfo->print(elem);
            }
            if (j + 1 != mat->dimension) {
                printf(" ");
            }
        }
        printf("|\n");
    }
    
    return MATRIX_OPERATION_OK;
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