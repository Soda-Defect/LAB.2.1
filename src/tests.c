#include <stdio.h>
#include <assert.h>
#include "../include/matrix/matrix.h"
#include "../include/complex.h"
#include "../include/interface.h"
#include "../include/matrix/matrix_int.h"
#include "../include/matrix/matrix_float.h"
#include "../include/matrix/matrix_complex.h"

#define ASSERT_EQ(x, y) assert((x) == (y))

void test_create(int dimension, void* array_el, TypeInfo* typeInfo)
{
    printf("\n=== Тестирование создания матрицы ===\n");

    MatrixErrors error;

    if (typeInfo->size == sizeof(int)) {
        printf("\nmatrix_create: создаем матрицу типа int размерностью %d\n", dimension);
    } else if (typeInfo->size == sizeof(float)) {
        printf("\nmatrix_create: создаем матрицу типа float размерностью %d\n", dimension);
    } else if (typeInfo->size == sizeof(Complex)) {
        printf("\nmatrix_create: создаем матрицу типа complex размерностью %d\n", dimension);
    }
    Matrix* mat = matrix_create(dimension, typeInfo, &error);
    assert(mat != NULL);
    ASSERT_EQ(mat->dimension, dimension);

    printf("\nДобавляем элементы (функция push_el_matrix)\n");
    for(int i = 0; i < mat->dimension; i++){
        for(int j = 0; j < mat->dimension; j++){
            void* elem_ptr = (char*)array_el + (i * mat->dimension + j) * typeInfo->size;
            if (typeInfo->size == sizeof(int)) {
                int elem = *(int*)elem_ptr;
                error = push_el_matrix(mat, elem_ptr, i, j);
                printf("push_el_matrix: Добавляем элемент %d в [%d][%d] матрицы типа int размерности %d\n", elem, i, j, dimension);
            } else if (typeInfo->size == sizeof(float)) {
                float elem = *(float*)elem_ptr;
                error = push_el_matrix(mat, elem_ptr, i, j);
                printf("push_el_matrix: Добавляем элемент %.2f в [%d][%d] матрицы типа float размерности %d\n", elem, i, j, dimension);
            } else if (typeInfo->size == sizeof(Complex)) {
                Complex elem = *(Complex*)elem_ptr;
                error = push_el_matrix(mat, elem_ptr, i, j);
                printf("push_el_matrix: Добавляем элемент (%d + %di) в [%d][%d] матрицы типа complex размерности %d\n", elem.real, 
                    elem.imag, i, j, dimension);
            }
        }
    }

    printf("\nСозданная матрица\n");
    print_matrix(mat);
    printf("\n");

    for(int i = 0; i < mat->dimension; i++){
        for(int j = 0; j < mat->dimension; j++){
            void* elem_ptr = (char*)array_el + (i * mat->dimension + j) * typeInfo->size;
            void* ptr = element_get(mat, i, j, &error);
            if (typeInfo->size == sizeof(int)){
                int elem = *(int*)elem_ptr;
                printf("element_get: Берем элемент %d из [%d][%d] матрицы типа int размерности %d\n", elem, i, j, dimension); 
                ASSERT_EQ(*(int*)ptr, elem);     
            }else if(typeInfo->size == sizeof(float)){
                float elem = *(float*)elem_ptr;
                printf("element_get: Берем элемент %.2f из [%d][%d] матрицы типа float размерности %d\n", elem, i, j, dimension); 
                ASSERT_EQ(*(float*)ptr, elem);     
            }else if (typeInfo->size == sizeof(Complex)) {
                Complex elem = *(Complex*)elem_ptr;
                Complex elem_mat = *(Complex*)ptr;
                error = push_el_matrix(mat, elem_ptr, i, j);
                printf("element_get: Берем элемент (%d + %di) из [%d][%d] матрицы типа complex размерности %d\n", elem.real, 
                    elem.imag, i, j, dimension);
                ASSERT_EQ(elem_mat.real, elem.real);  
                ASSERT_EQ(elem_mat.imag, elem.imag);  
            }
        }
    }
    matrix_free(mat);

    printf("\n=== Обработка ошибок создания===\n");
    
    printf("\nПопытка создать матрицу с отрицательным размером (Ошибка INVALID_MATRIX_SIZE)\n");
    mat = matrix_create(-3, typeInfo, &error);
    ASSERT_EQ(error, INVALID_MATRIX_SIZE);
    print_matrix_error(error);
    ASSERT_EQ(mat, NULL);

    printf("\nПопытка создать матрицу без typeinfo (Ошибка INVALID_TYPE_INFO)\n");
    mat = matrix_create(3, NULL, &error);
    ASSERT_EQ(error, INVALID_TYPE_INFO);
    print_matrix_error(error);
    ASSERT_EQ(mat, NULL);

    printf("\nПопытка занести в матрицу элемент в несуществующую ячейку [-1][-2] (Ошибка INVALID_MATRIX_INDEX)\n");
    int elem = 3;
    mat = matrix_create(3, typeInfo, &error);
    error = push_el_matrix(mat, &elem, -1, -2);
    ASSERT_EQ(error, INVALID_MATRIX_INDEX);
    print_matrix_error(error);

    printf("\nПопытка занести в матрицу элемент в несуществующую ячейку [4][4] (Ошибка INVALID_MATRIX_INDEX)\n");
    mat = matrix_create(3, typeInfo, &error);
    error = push_el_matrix(mat, &elem, 4, 4);
    ASSERT_EQ(error, INVALID_MATRIX_INDEX);
    print_matrix_error(error);

    printf("\nПопытка узнать элемент матрицы из несуществующей ячейки [-1][-2] (Ошибка INVALID_MATRIX_INDEX)\n");
    element_get(mat, -1, -2, &error);
    ASSERT_EQ(error, INVALID_MATRIX_INDEX);
    print_matrix_error(error);

    printf("\nПопытка узнать элемент матрицы из несуществующей ячейки [4][4] (Ошибка INVALID_MATRIX_INDEX)\n");
    element_get(mat, 4, 4, &error);
    ASSERT_EQ(error, INVALID_MATRIX_INDEX);
    print_matrix_error(error);

    printf("\nПопытка занести в пустую матрицу элемент(Ошибка MATRIX_NOT_DEFINED)\n");
    mat = NULL;
    error = push_el_matrix(mat, &elem, 0, 0);
    ASSERT_EQ(error, MATRIX_NOT_DEFINED);
    print_matrix_error(error);

    printf("\nПопытка узнать элемент из пустой матрицы (Ошибка MATRIX_NOT_DEFINED)\n");
    mat = matrix_create(3, typeInfo, &error);
    error = push_el_matrix(mat, NULL, 0, 0);
    ASSERT_EQ(error, MATRIX_NOT_DEFINED);
    print_matrix_error(error);
}

void test_operation(void* array_el, void* array_el_2, TypeInfo* typeInfo)
{
    printf("\n=== Тестирование операций матрицы ===\n");

    MatrixErrors error;

    Matrix* mat = matrix_create(3, typeInfo, &error);
    for(int i = 0; i < mat->dimension; i++){
        for(int j = 0; j < mat->dimension; j++){
            void* elem_ptr = (char*)array_el + (i * mat->dimension + j) * typeInfo->size;
            if (typeInfo->size == sizeof(int)) {
                int elem = *(int*)elem_ptr;
                error = push_el_matrix(mat, elem_ptr, i, j);
            } else if (typeInfo->size == sizeof(float)) {
                float elem = *(float*)elem_ptr;
                error = push_el_matrix(mat, elem_ptr, i, j);
            } else if (typeInfo->size == sizeof(Complex)) {
                Complex elem = *(Complex*)elem_ptr;
                error = push_el_matrix(mat, elem_ptr, i, j);
            }
        }
    }
    printf("\nПервая матрица умножения\n");
    print_matrix(mat);

    Matrix* mat_2 = matrix_create(3, typeInfo, &error);
    for(int i = 0; i < mat_2->dimension; i++){
        for(int j = 0; j < mat_2->dimension; j++){
            void* elem_ptr = (char*)array_el_2 + (i * mat_2->dimension + j) * typeInfo->size;
            if (typeInfo->size == sizeof(int)) {
                int elem = *(int*)elem_ptr;
                error = push_el_matrix(mat_2, elem_ptr, i, j);
            } else if (typeInfo->size == sizeof(float)) {
                float elem = *(float*)elem_ptr;
                error = push_el_matrix(mat_2, elem_ptr, i, j);
            } else if (typeInfo->size == sizeof(Complex)) {
                Complex elem = *(Complex*)elem_ptr;
                error = push_el_matrix(mat_2, elem_ptr, i, j);
            }
        }
    }
    printf("\nВторая матрица умножения\n");
    print_matrix(mat_2);

    printf("\nУмножение матриц (функция matrix_mult)\n");
    Matrix* mult = matrix_mult(mat, mat_2, &error);

    for(int i = 0; i < mat->dimension; i++){
        for(int j = 0; j < mat_2->dimension; j++){
            if (typeInfo->size == sizeof(int)){
                int sum = 0;
                for(int k = 0; k < mat -> dimension; k++){
                    int ptr = *(int*)element_get(mat, i, k, &error);
                    int ptr_2 = *(int*)element_get(mat_2, k, j, &error);
                    sum += ptr * ptr_2;
                }
                int ptr_3 = *(int*)element_get(mult, i, j, &error);
                printf("matrix_mult: элемент [%d][%d]. Ожидаемый результат %d Полученный: %d\n", i, j, sum, ptr_3);
                ASSERT_EQ(ptr_3, sum);
            } else if((typeInfo->size == sizeof(float))){
                float sum = 0;
                for(int k = 0; k < mat -> dimension; k++){
                    float ptr = *(float*)element_get(mat, i, k, &error);
                    float ptr_2 = *(float*)element_get(mat_2, k, j, &error);
                    sum += ptr * ptr_2;
                }
                float ptr_3 = *(float*)element_get(mult, i, j, &error);
                printf("matrix_mult: элемент [%d][%d]. Ожидаемый результат %.2f Полученный: %.2f\n", i, j, sum, ptr_3);
                ASSERT_EQ(ptr_3, sum);
            } else if((typeInfo->size == sizeof(Complex))){
                int sum = 0;
                int sum_2 = 0;
                for(int k = 0; k < mat -> dimension; k++){
                    Complex ptr = *(Complex*)element_get(mat, i, k, &error);
                    Complex ptr_2 = *(Complex*)element_get(mat_2, k, j, &error);
                    sum += ptr.real * ptr_2.real - ptr.imag * ptr_2.imag;
                    sum_2 += ptr.real * ptr_2.imag + ptr_2.real * ptr.imag;
                }
                Complex ptr_3 = *(Complex*)element_get(mult, i, j, &error);
                printf("matrix_mult: элемент [%d][%d]. Ожидаемый результат (%d + %di) Полученный: %d\n", i, j, sum, sum_2, ptr_3.real, 
                    ptr_3.imag);
                ASSERT_EQ(ptr_3.real, sum);
                ASSERT_EQ(ptr_3.imag, sum_2);
            }
        }
    }

    printf("\nПервая матрица сложения\n");
    print_matrix(mat);
    printf("\nВторая матрица сложения\n");
    print_matrix(mat_2);
    printf("\nСложение матриц (функция matrix_add)\n");
    Matrix* sum = matrix_add(mat, mat_2, &error);

    for(int i = 0; i < mat->dimension; i++){
        for(int j = 0; j < mat->dimension; j++){
            if (typeInfo->size == sizeof(int)){
                int ptr = *(int*)element_get(mat, i, j, &error);
                int ptr_2 = *(int*)element_get(mat_2, i, j, &error);
                int ptr_3 = *(int*)element_get(sum, i, j, &error);
                printf("matrix_add: элемент [%d][%d]. Ожидаемый результат %d Полученный: %d\n", i, j, ptr_2 + ptr, ptr_3);
                ASSERT_EQ(ptr_2 + ptr, ptr_3);
            } else if((typeInfo->size == sizeof(float))){
                float ptr = *(float*)element_get(mat, i, j, &error);
                float ptr_2 = *(float*)element_get(mat_2, i, j, &error);
                float ptr_3 = *(float*)element_get(sum, i, j, &error);
                printf("matrix_add: элемент [%d][%d]. Ожидаемый результат %.2f Полученный: %.2f\n", i, j, ptr_2 + ptr, ptr_3);
                ASSERT_EQ(ptr_2 + ptr, ptr_3);
            } else if((typeInfo->size == sizeof(Complex))){
                Complex ptr = *(Complex*)element_get(mat, i, j, &error);
                Complex ptr_2 = *(Complex*)element_get(mat_2, i, j, &error);
                Complex ptr_3 = *(Complex*)element_get(sum, i, j, &error);
                printf("matrix_add: элемент [%d][%d]. Ожидаемый результат (%d + %di) Полученный: (%d + %di)\n", i, j, ptr_3.real, 
                    ptr_3.imag, ptr.real + ptr_2.real, ptr.imag + ptr_2.imag);
                ASSERT_EQ(ptr_3.real, ptr.real + ptr_2.real);
                ASSERT_EQ(ptr_3.imag, ptr.imag + ptr_2.imag);
            }
        }
    }

    printf("\nТранспонироание матрицы (функция matrix_transp)\n");
    printf("\nМатрица для транспонирования\n");
    print_matrix(mat);
    Matrix* transp = matrix_transp(mat, &error);
    for(int i = 0; i < mat->dimension; i++){
        for(int j = 0; j < mat->dimension; j++){
            if (typeInfo->size == sizeof(int)){
                int ptr = *(int*)element_get(mat, i, j, &error);
                int ptr_2 = *(int*)element_get(transp, j, i, &error);
                printf("matrix_transp: элемент [%d][%d]. Ожидаемый результат %d Полученный: %d\n", i, j, ptr, ptr_2);
                ASSERT_EQ(ptr, ptr_2);
            } else if((typeInfo->size == sizeof(float))){
                float ptr = *(float*)element_get(mat, i, j, &error);
                float ptr_2 = *(float*)element_get(transp, j, i, &error);
                printf("matrix_transp: элемент [%d][%d]. Ожидаемый результат %.2f Полученный: %.2f\n", i, j, ptr, ptr_2);
                ASSERT_EQ(ptr, ptr);
            } else if((typeInfo->size == sizeof(Complex))){
                Complex ptr = *(Complex*)element_get(mat, i, j, &error);
                Complex ptr_2 = *(Complex*)element_get(transp, j, i, &error);
                printf("matrix_transp: элемент [%d][%d]. Ожидаемый результат (%d + %di) Полученный: (%d + %di)\n", i, j, ptr.real, 
                    ptr.imag, ptr_2.real, ptr_2.imag);
                ASSERT_EQ(ptr.real, ptr.real);
                ASSERT_EQ(ptr.imag, ptr.imag);
            }
        }
    }

    matrix_free(mat_2);
    printf("\nУмножение на скаляр 3 (matrix_multiply_const)\n");
    printf("\nМатрица для умножения на скаляр\n");
    print_matrix(mat);
    mat_2 = matrix_create(3, typeInfo, &error);
    for(int i = 0; i < mat_2->dimension; i++){
        for(int j = 0; j < mat_2->dimension; j++){
            void* elem_ptr = (char*)array_el + (i * mat_2->dimension + j) * typeInfo->size;
            if (typeInfo->size == sizeof(int)) {
                int elem = *(int*)elem_ptr;
                error = push_el_matrix(mat_2, elem_ptr, i, j);
            } else if (typeInfo->size == sizeof(float)) {
                float elem = *(float*)elem_ptr;
                error = push_el_matrix(mat_2, elem_ptr, i, j);
            } else if (typeInfo->size == sizeof(Complex)) {
                Complex elem = *(Complex*)elem_ptr;
                error = push_el_matrix(mat_2, elem_ptr, i, j);
            }
        }
    }
    matrix_multiply_const(mat, 3);
     for(int i = 0; i < mat -> dimension; i++){
        for(int j = 0; j < mat -> dimension; j++){
            if (typeInfo->size == sizeof(int)){
                int ptr = *(int*)element_get(mat_2, i, j, &error);
                int ptr_2 = *(int*)element_get(mat, i, j, &error);
                printf("matrix_multiply_const: элемент [%d][%d] умноженный на 3. Ожидаемый результат %d Полученный: %d\n", i, j, ptr * 3,
                     ptr_2);
                ASSERT_EQ(ptr * 3, ptr_2);
            } else if (typeInfo->size == sizeof(float)){
                float ptr = *(float*)element_get(mat_2, i, j, &error);
                float ptr_2 = *(float*)element_get(mat, i, j, &error);
                printf("matrix_multiply_const: элемент [%d][%d] умноженный на 3. Ожидаемый результат %.2f Полученный: %.2f\n", i, j, 
                    ptr * 3, ptr_2);
                ASSERT_EQ(ptr * 3, ptr_2);
            } else if (typeInfo->size == sizeof(Complex)){
                Complex ptr = *(Complex*)element_get(mat_2, i, j, &error);
                Complex ptr_2 = *(Complex*)element_get(mat, i, j, &error);
                printf("matrix_multiply_const: элемент [%d][%d] умноженный на 3. Ожидаемый результат (%d + %di) Полученный:(%d + %di)\n", 
                    i, j, ptr.real * 3, ptr.imag * 3, ptr_2.real, ptr_2.imag);
                ASSERT_EQ(ptr.real * 3, ptr_2.real);
                ASSERT_EQ(ptr.imag * 3, ptr_2.imag);
            }
        }
    }

    printf("\n=== Обработка ошибок операций ===\n");

    printf("\nПопытка сложить матрицы разной размерности (MATRIX_SIZE_MISMATCH)\n");
    mat_2 = matrix_create(4, typeInfo, &error);
    sum = matrix_add(mat, mat_2, &error);
    ASSERT_EQ(error, MATRIX_SIZE_MISMATCH);
    print_matrix_error(error);
    ASSERT_EQ(sum, NULL);

    printf("\nПопытка умножить матрицы разной размерности (MATRIX_SIZE_MISMATCH)\n");
    mult = matrix_mult(mat, mat_2, &error);
    ASSERT_EQ(error, MATRIX_SIZE_MISMATCH);
    print_matrix_error(error);
    ASSERT_EQ(mult, NULL);

    printf("\nПопытка сложить матрицы разных типов (INCOMPATIBLE_MATRIX_TYPES)\n");
    mat_2 = matrix_create(4, GetIntTypeInfo(), &error);
    mat = matrix_create(4, GetFloatTypeInfo(), &error);
    sum = matrix_add(mat, mat_2, &error);
    ASSERT_EQ(error, INCOMPATIBLE_MATRIX_TYPES);
    print_matrix_error(error);
    ASSERT_EQ(sum, NULL);

    printf("\nПопытка умножить матрицы разных типов (INCOMPATIBLE_MATRIX_TYPES)\n");
    mat_2 = matrix_create(4, GetIntTypeInfo(), &error);
    mat = matrix_create(4, GetFloatTypeInfo(), &error);
    mult = matrix_mult(mat, mat_2, &error);
    ASSERT_EQ(error, INCOMPATIBLE_MATRIX_TYPES);
    print_matrix_error(error);
    ASSERT_EQ(sum, NULL);
}

void run_int_matrix()
{
    printf("\n=== Тестирование матрицы целых чисел ===\n");

    int array_el[] = {1, 5, 7, 2, 4, 9, 8, 0, 3};
    int array_el_2[] = {8, 0, 7, 2, 4, 3, 0, 6, 9};

    test_create(3, array_el, GetIntTypeInfo());

    test_operation(array_el, array_el_2, GetIntTypeInfo());

    printf("\n=== Тестирование матрицы целых чисел закончен ===\n");
}

void run_float_matrix()
{
    printf("\n=== Тестирование матрицы вещественных чисел ===\n");
    
    float array_el[] = {1.12, 5.01, 7.2, 2.41, 4.37, 9.04, 8.24, 1.09, 3.1};
    float array_el_2[] = {8.14, 1.34, 7.1, 2.01, 4.73, 3.9, 5.25, 6.41, 9.02};

    test_create(3, array_el, GetFloatTypeInfo());
    
    test_operation(array_el, array_el_2,GetFloatTypeInfo());
    
    printf("\n=== Тестирование матрицы вещественных чисел закончен ===\n");
}

void run_complex_matrix()
{
    printf("\n=== Тестирование матрицы комплексных чисел ===\n");

    int array_re[] = {-1, 5, -7, 2, 4, 9, 8, 7, -3};
    int array_im[] = {9, -4, 1, 5, -3, 7, 2, 8, 3};
    Complex array_el[9];
    for(int i = 0; i < 9; i++){
        array_el[i].real = array_re[i];
        array_el[i].imag = array_im[i];
    }

    int array_re_2[] = {8, 1, 7, 2, 4, 3, 4, 6, 9};
    int array_im_2[] = {-1, 2, -7, 4, 3, 8, -6, 5, 1};
    Complex array_el_2[9];
    for(int i = 0; i < 9; i++){
        array_el_2[i].real = array_re_2[i];
        array_el_2[i].imag = array_im_2[i];
    }

    test_create(3, array_el, GetComplexTypeInfo());
    
    test_operation(array_el, array_el_2,GetFloatTypeInfo());

    printf("\n=== Тестирование матрицы комплексных чисел закончен ===\n");
}

void run_all_matrix()
{
    run_int_matrix();
    run_float_matrix();
    run_complex_matrix();
}