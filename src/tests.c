#include <stdio.h>
#include <assert.h>
#include "../include/matrix/matrix.h"
#include "../include/complex.h"
#include "../include/matrix/matrix_int.h"
#include "../include/matrix/matrix_float.h"
#include "../include/matrix/matrix_complex.h"

#define ASSERT_EQ(x, y) assert((x) == (y))

void run_int_matrix()
{
    printf("\n=== Тестирование матрицы целых чисел ===\n");

    printf("Создание матрицы 3x3\n");
    Matrix* mat = create_int_matrix(3);
    assert(mat != NULL);
    ASSERT_EQ(mat->razm, 3);

    printf("Добавляем элементы\n");
    int array_el[] = {1, 5, 7, 2, 4, 9, 8, 0, 3};
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
    int array_el_2[] = {8, 0, 7, 2, 4, 3, 0, 6, 9};
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

    printf("Умножение на скаляр 3\n");
    mat_2 = create_int_matrix(3);
    k = 0;
    for(int i = 0; i < mat_2->razm; i++){
        for(int j = 0; j < mat_2->razm; j++){
            elem = array_el[k];
            k++;
            push_el_matrix(mat_2, &elem, i, j);
        }
    }
    matrix_multiply_const(mat, 3);
    print_matrix(mat);

    for(int i = 0; i < mat -> razm; i++){
        for(int j = 0; j < mat -> razm; j++){
            ptr = (int*)element_get(mat, i, j);
            ptr_2 = (int*)element_get(mat_2, i, j);
            ASSERT_EQ(*ptr, *ptr_2 * 3);
        }
    }

    matrix_free(mat_2);
    matrix_free(mat);

    printf("\n=== Тестирование матрицы целых чисел закончен ===\n");
}

void run_float_matrix()
{
    printf("\n=== Тестирование матрицы вещественных чисел ===\n");

    printf("Создание матрицы 3x3\n");
    Matrix* mat = create_float_matrix(3);
    assert(mat != NULL);
    ASSERT_EQ(mat->razm, 3);

    printf("Добавляем элементы\n");
    float array_el[] = {1.12, 5.01, 7.2, 2.41, 4.37, 9.04, 8.24, 1.09, 3.1};
    float elem;
    int k = 0;
    float *ptr, *ptr_2, *ptr_3, *ptr_4;
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
            ptr = (float*)element_get(mat, i, j);
            ASSERT_EQ(*ptr, elem);
        }
    }

    printf("Создание второй матрицы 3x3\n");
    Matrix* mat_2 = create_float_matrix(3);
    assert(mat_2 != NULL);
    ASSERT_EQ(mat_2->razm, 3);

    printf("Добавляем элементы\n");
    float array_el_2[] = {8.14, 1.34, 7.1, 2.01, 4.73, 3.9, 5.25, 6.41, 9.02};
    float elem_2;
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
            ptr = (float*)element_get(mat_2, i, j);
            ASSERT_EQ(*ptr, elem_2);
        }
    }

    printf("Умножение матриц\n");
    Matrix* mult = matrix_mult(mat, mat_2);
    print_matrix(mult);
    for(int i = 0; i < mat->razm; i++){
        for(int j = 0; j < mat->razm; j++){
            float sum = 0.0;
            for(int k = 0; k < mat -> razm; k++){
                ptr = (float*)element_get(mat, i, k);
                ptr_2 = (float*)element_get(mat_2, k, j);
                sum += *ptr * *ptr_2;
            }
            ptr_3 = (float*)element_get(mult, i, j);
            ASSERT_EQ(*ptr_3, sum);
        }
    }

    printf("Сложение матриц\n");
    Matrix* sum = matrix_add(mat, mat_2);
    print_matrix(sum);
    for(int i = 0; i < mat->razm; i++){
        for(int j = 0; j < mat->razm; j++){
            ptr = (float*)element_get(mat, i, j);
            ptr_2 = (float*)element_get(mat_2, i, j);
            ptr_3 = (float*)element_get(sum, i, j);
            ASSERT_EQ(*ptr_3, *ptr + *ptr_2);
        }
    }

    matrix_free(mat_2);

    printf("Транспонироание матрицы\n");
    Matrix* transp = matrix_transp(mat);
    print_matrix(transp);
    for(int i = 0; i < mat->razm; i++){
        for(int j = 0; j < mat->razm; j++){
            ptr = (float*)element_get(mat, i, j);
            ptr_2 = (float*)element_get(transp, j, i);
            ASSERT_EQ(*ptr, *ptr_2);
        }
    }

    printf("Умножение на скаляр 3\n");
    mat_2 = create_float_matrix(3);
    k = 0;
    for(int i = 0; i < mat_2->razm; i++){
        for(int j = 0; j < mat_2->razm; j++){
            elem = array_el[k];
            k++;
            push_el_matrix(mat_2, &elem, i, j);
        }
    }
    matrix_multiply_const(mat, 3);
    print_matrix(mat);

    for(int i = 0; i < mat -> razm; i++){
        for(int j = 0; j < mat -> razm; j++){
            ptr = (float*)element_get(mat, i, j);
            ptr_2 = (float*)element_get(mat_2, i, j);
            ASSERT_EQ(*ptr, *ptr_2 * 3);
        }
    }

    matrix_free(mat_2);
    matrix_free(mat);

    printf("\n=== Тестирование матрицы вещественных чисел закончен ===\n");
}

void run_complex_matrix()
{
    printf("\n=== Тестирование матрицы комплексных чисел ===\n");

    printf("Создание матрицы 3x3\n");
    Matrix* mat = create_complex_matrix(3);
    assert(mat != NULL);
    ASSERT_EQ(mat->razm, 3);

    printf("Добавляем элементы\n");
    int array_re[] = {-1, 5, -7, 2, 4, 9, 8, 7, -3};
    int array_im[] = {9, -4, 1, 5, -3, 7, 2, 8, 3};
    int elem_re, elem_im;
    int k = 0;
    Complex *ptr, *ptr_2, *ptr_3, *ptr_4;
    for(int i = 0; i < mat->razm; i++){
        for(int j = 0; j < mat->razm; j++){
            elem_re = array_re[k];
            elem_im = array_im[k];
            k++;
            Complex c = complex_create(elem_re, elem_im);
            push_el_matrix(mat, &c, i, j);
        }
    }
    print_matrix(mat);
    k = 0;
    for(int i = 0; i < mat->razm; i++){
        for(int j = 0; j < mat->razm; j++){
            elem_re = array_re[k];
            elem_im = array_im[k];
            k++;
            ptr = (Complex*)element_get(mat, i, j);
            ASSERT_EQ(ptr->real, elem_re);
            ASSERT_EQ(ptr->imag, elem_im);
        }
    }

    printf("Создание второй матрицы 3x3\n");
    Matrix* mat_2 = create_complex_matrix(3);
    assert(mat_2 != NULL);
    ASSERT_EQ(mat_2->razm, 3);

    printf("Добавляем элементы\n");
    int array_re_2[] = {8, 1, 7, 2, 4, 3, 4, 6, 9};
    int array_im_2[] = {-1, 2, -7, 4, 3, 8, -6, 5, 1};
    int elem_re_2, elem_im_2;
    k = 0;
    for(int i = 0; i < mat_2->razm; i++){
        for(int j = 0; j < mat_2->razm; j++){
            elem_re_2 = array_re_2[k];
            elem_im_2 = array_im_2[k];
            k++;
            Complex c = complex_create(elem_re_2, elem_im_2);
            push_el_matrix(mat_2, &c, i, j);
        }
    }
    print_matrix(mat_2);
    k = 0;
    for(int i = 0; i < mat_2->razm; i++){
        for(int j = 0; j < mat_2->razm; j++){
            elem_re_2 = array_re_2[k];
            elem_im_2 = array_im_2[k];
            k++;
            ptr = (Complex*)element_get(mat_2, i, j);
            ASSERT_EQ(ptr->real, elem_re_2);
            ASSERT_EQ(ptr->imag, elem_im_2);
        }
    }

    printf("Умножение матриц\n");
    Matrix* mult = matrix_mult(mat, mat_2);
    print_matrix(mult);
    for(int i = 0; i < mat->razm; i++){
        for(int j = 0; j < mat->razm; j++){
            int sum = 0;
            int sum_2 = 0;
            for(int k = 0; k < mat -> razm; k++){
                ptr = (Complex*)element_get(mat, i, k);
                ptr_2 = (Complex*)element_get(mat_2, k, j);
                sum += ptr->real * ptr_2->real - ptr->imag * ptr_2->imag;
                sum_2 += ptr->real * ptr_2->imag + ptr_2->real * ptr->imag;
            }
            ptr_3 = (Complex*)element_get(mult, i, j);
            ASSERT_EQ(ptr_3->real, sum);
            ASSERT_EQ(ptr_3->imag, sum_2);
        }
    }

    printf("Сложение матриц\n");
    Matrix* sum = matrix_add(mat, mat_2);
    print_matrix(sum);
    for(int i = 0; i < mat->razm; i++){
        for(int j = 0; j < mat->razm; j++){
            ptr = (Complex*)element_get(mat, i, j);
            ptr_2 = (Complex*)element_get(mat_2, i, j);
            ptr_3 = (Complex*)element_get(sum, i, j);
            ASSERT_EQ(ptr_3->real, ptr->real + ptr_2->real);
            ASSERT_EQ(ptr_3->imag, ptr->imag + ptr_2->imag);
        }
    }

    matrix_free(mat_2);

    printf("Транспонироание матрицы\n");
    Matrix* transp = matrix_transp(mat);
    print_matrix(transp);
    for(int i = 0; i < mat->razm; i++){
        for(int j = 0; j < mat->razm; j++){
            ptr = (Complex*)element_get(mat, i, j);
            ptr_2 = (Complex*)element_get(transp, j, i);
            ASSERT_EQ(ptr->real, ptr_2->real);
            ASSERT_EQ(ptr->imag, ptr_2->imag);
        }
    }

    printf("Умножение на скаляр 3\n");
    mat_2 = create_complex_matrix(3);
    k = 0;
    for(int i = 0; i < mat_2->razm; i++){
        for(int j = 0; j < mat_2->razm; j++){
            elem_re = array_re[k];
            elem_im = array_im[k];
            k++;
            Complex c = complex_create(elem_re, elem_im);
            push_el_matrix(mat_2, &c, i, j);
        }
    }
    matrix_multiply_const(mat, 3);
    print_matrix(mat);

    for(int i = 0; i < mat -> razm; i++){
        for(int j = 0; j < mat -> razm; j++){
            ptr = (Complex*)element_get(mat, i, j);
            ptr_2 = (Complex*)element_get(mat_2, i, j);
            ASSERT_EQ(ptr->real, ptr_2->real * 3);
            ASSERT_EQ(ptr->imag, ptr_2->imag * 3);
        }
    }

    matrix_free(mat_2);
    matrix_free(mat);

    printf("\n=== Тестирование матрицы комплексных чисел закончен ===\n");
}

void run_all_matrix()
{
    run_int_matrix();
    run_float_matrix();
    run_complex_matrix();
}