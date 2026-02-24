#include <stdio.h>
#include <assert.h>
#include "include/matrix/matrix.h"
#include "include/matrix/matrix_int.h"
#include "include/matrix/matrix_float.h"
#include "include/matrix/matrix_complex.h"

void run_int_matrix()
{
    printf("\n=== Тестирование матрицы целых чисел ===\n");

    printf("Создание матрицы 3x3\n");
    Matrix* mat = create_int_matrix(3, 3);
    assert(mat != NULL);
    ASSERT_EQ(mat->rows, 3);
    ASSERT_EQ(mat->cols, 3);

    printf("Добавляем элементы\n");
    int array_el[] = {10, 5, 7, 2, 18, 9, 8, 14, 6};
    int elem;
    int k = sizeof(array_el) / sizeof(*array_el);
    int *ptr, *ptr_2;
    for(int i = 0; i < mat->rows; i++){
        for(int j = 0; j < mat->cols; j++){
            elem = array_el[k];
            k--;
            push_el_matrix(mat, &elem, i, j);
        }
    }
    k = sizeof(array_el) / sizeof(*array_el);
    for(int i = 0; i < mat->rows; i++){
        for(int j = 0; j < mat->cols; j++){
            elem = array_el[k];
            k--;
            *ptr = (int*)element_get(mat, i, j);
            ASSERT_EQ(*ptr, elem);
        }
    }

    printf("Транспонироание матрицы\n");
    Matrix* transp = matrix_transp(mat);
    for(int i = 0; i < mat->rows; i++){
        for(int j = 0; j < mat->cols; j++){
            *ptr = (int*)element_get(mat, i, j);
            *ptr_2 = (int*)element_get(mat, j, i);
            ASSERT_EQ(*ptr, *ptr_2);
        }
    }
}