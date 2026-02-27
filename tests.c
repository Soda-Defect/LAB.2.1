#include <stdio.h>
#include <assert.h>
#include "include/matrix/matrix.h"
#include "include/matrix/matrix_int.h"
//#include "include/matrix/matrix_float.h"
//#include "include/matrix/matrix_complex.h"

#define ASSERT_EQ(x, y) assert((x) == (y))

void run_int_matrix()
{
    printf("\n=== Тестирование матрицы целых чисел ===\n");

    printf("Создание матрицы 3x3\n");
    Matrix* mat = create_int_matrix(3);
    assert(mat != NULL);
    ASSERT_EQ(mat->razm, 3);

    printf("Добавляем элементы\n");
    int array_el[] = {10, 5, 7, 2, 18, 9, 8, 14, 6};
    int elem;
    int k = 0;
    int *ptr, *ptr_2, *ptr_3, *ptr_4;
    for(int i = 0; i < mat->razm; i++){
        for(int j = 0; j < mat->razm; j++){
            elem = array_el[k];
            k++;
            push_el_matrix(mat, &elem, i, j);
        }
    }
    print_matrix(mat);
    k = 0;
    for(int i = 0; i < mat->razm; i++){
        for(int j = 0; j < mat->razm; j++){
            elem = array_el[k];
            k++;
            ptr = (int*)element_get(mat, i, j);
            ASSERT_EQ(*ptr, elem);
        }
    }

    printf("Создание второй матрицы 3x3\n");
    Matrix* mat_2 = create_int_matrix(3);
    assert(mat_2 != NULL);
    ASSERT_EQ(mat_2->razm, 3);

    printf("Добавляем элементы\n");
    int array_el_2[] = {8, 0, 7, 16, 4, 3, 21, 6, 10};
    int elem_2;
    k = 0;
    for(int i = 0; i < mat_2->razm; i++){
        for(int j = 0; j < mat_2->razm; j++){
            elem_2 = array_el_2[k];
            k++;
            push_el_matrix(mat_2, &elem_2, i, j);
        }
    }
    print_matrix(mat_2);
    k = 0;
    for(int i = 0; i < mat_2->razm; i++){
        for(int j = 0; j < mat_2->razm; j++){
            elem_2 = array_el_2[k];
            k++;
            ptr = (int*)element_get(mat_2, i, j);
            ASSERT_EQ(*ptr, elem_2);
        }
    }

    printf("Умножение матриц\n");
    Matrix* mult = matrix_mult(mat, mat_2);
    print_matrix(mult);
    for(int i = 0; i < mat->razm; i++){
        for(int j = 0; j < mat->razm; j++){
            int sum = 0;
            for(int k = 0; k < mat -> razm; k++){
                ptr = (int*)element_get(mat, i, k);
                ptr_2 = (int*)element_get(mat_2, k, j);
                sum += *ptr * *ptr_2;
            }
            ptr_3 = (int*)element_get(mult, i, j);
            ASSERT_EQ(*ptr_3, sum);
        }
    }

    printf("Сложение матриц\n");
    Matrix* sum = matrix_add(mat, mat_2);
    print_matrix(sum);
    for(int i = 0; i < mat->razm; i++){
        for(int j = 0; j < mat->razm; j++){
            ptr = (int*)element_get(mat, i, j);
            ptr_2 = (int*)element_get(mat_2, i, j);
            ptr_3 = (int*)element_get(sum, i, j);
            ASSERT_EQ(*ptr_3, *ptr + *ptr_2);
        }
    }

    matrix_free(mat_2);

    printf("Транспонироание матрицы\n");
    Matrix* transp = matrix_transp(mat);
    print_matrix(transp);
    for(int i = 0; i < mat->razm; i++){
        for(int j = 0; j < mat->razm; j++){
            ptr = (int*)element_get(mat, i, j);
            ptr_2 = (int*)element_get(transp, j, i);
            ASSERT_EQ(*ptr, *ptr_2);
        }
    }

    printf("Прибавление к строке 1 линейной комбинации строк, умноженных на 2 и 1\n");
    mat_2 = create_int_matrix(3);
    k = 0;
    for(int i = 0; i < mat_2->razm; i++){
        for(int j = 0; j < mat_2->razm; j++){
            elem = array_el[k];
            k++;
            push_el_matrix(mat_2, &elem, i, j);
        }
    }
    int rowIndex = 1;
    int alpha1 = 2, alpha2 = 1;
    matrix_add_line_comb(mat, rowIndex - 1, 1, &alpha1);
    matrix_add_line_comb(mat, rowIndex - 1, 2, &alpha2);
    print_matrix(mat);
    
    ptr = (int*)element_get(mat, 0, 0);
    ptr_2 = (int*)element_get(mat_2, 0, 0);
    ptr_3 = (int*)element_get(mat_2, 1, 0);
    ptr_4 = (int*)element_get(mat_2, 2, 0);
    ASSERT_EQ(*ptr, *ptr_2 + *ptr_3 * 2 + *ptr_4);
    ptr = (int*)element_get(mat, 0, 1);
    ptr_2 = (int*)element_get(mat_2, 0, 1);
    ptr_3 = (int*)element_get(mat_2, 1, 1);
    ptr_4 = (int*)element_get(mat_2, 2, 1);
    ASSERT_EQ(*ptr, *ptr_2 + *ptr_3 * 2 + *ptr_4);
    ptr = (int*)element_get(mat, 0, 2);
    ptr_2 = (int*)element_get(mat_2, 0, 2);
    ptr_3 = (int*)element_get(mat_2, 1, 2);
    ptr_4 = (int*)element_get(mat_2, 2, 2);
    ASSERT_EQ(*ptr, *ptr_2 + *ptr_3 * 2 + *ptr_4);

    matrix_free(mat_2);
    matrix_free(mat);

    printf("\n=== Тестирование матрицы целых чисел закончен ===\n");
}

void run_all_matrix()
{
    run_int_matrix();
}