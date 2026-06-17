#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../include/matrix/matrix.h"
#include "../include/complex.h"
#include "../include/interface.h"
#include "../include/matrix/matrix_int.h"
#include "../include/matrix/matrix_float.h"
#include "../include/matrix/matrix_complex.h"

#define ASSERT_EQ(x, y) assert((x) == (y))

void test_create(size_t dimension, void* array_el, TypeInfo* typeInfo)
{
    printf("\n=== Тестирование создания матрицы ===\n");

    MatrixErrors error;

    if (typeInfo->size == sizeof(int)) {
        printf("\nmatrix_create: создаем матрицу типа int размерностью %zu\n", dimension);
    } else if (typeInfo->size == sizeof(float)) {
        printf("\nmatrix_create: создаем матрицу типа float размерностью %zu\n", dimension);
    } else if (typeInfo->size == sizeof(Complex)) {
        printf("\nmatrix_create: создаем матрицу типа complex размерностью %zu\n", dimension);
    }
    Matrix* mat = matrix_create(dimension, typeInfo, &error);
    assert(mat != NULL);
    ASSERT_EQ(mat->dimension, dimension);

    printf("\nДобавляем элементы (функция push_el_matrix)\n");
    for(size_t i = 0; i < mat->dimension; i++){
        for(size_t j = 0; j < mat->dimension; j++){
            void* elem_ptr = (char*)array_el + (i * mat->dimension + j) * typeInfo->size;
            error = push_el_matrix(mat, elem_ptr, i, j);
            printf("push_el_matrix: Добавляем в [%zu][%zu] матрицы элемент", i, j);
            mat->typeInfo->print(elem_ptr);
            printf("\n");
        }
    }

    printf("\nСозданная матрица\n");
    print_matrix(mat);
    printf("\n");

    for(size_t i = 0; i < mat->dimension; i++){
        for(size_t j = 0; j < mat->dimension; j++){
            void* elem_ptr = (char*)array_el + (i * mat->dimension + j) * typeInfo->size;
            void* ptr = element_get(mat, i, j, &error);
            if (typeInfo->size == sizeof(int)){
                int elem = *(int*)elem_ptr;
                printf("\nelement_get: Берем из [%zu][%zu] матрицы элемент", i, j); 
                mat->typeInfo->print(elem_ptr);
                ASSERT_EQ(*(int*)ptr, elem);     
            }else if(typeInfo->size == sizeof(float)){
                float elem = *(float*)elem_ptr;
                printf("\nelement_get: Берем из [%zu][%zu] матрицы элемент", i, j); 
                mat->typeInfo->print(elem_ptr);
                ASSERT_EQ(*(float*)ptr, elem);     
            }else if (typeInfo->size == sizeof(Complex)) {
                Complex elem = *(Complex*)elem_ptr;
                Complex elem_mat = *(Complex*)ptr;
                error = push_el_matrix(mat, elem_ptr, i, j);
                printf("\nelement_get: Берем из [%zu][%zu] матрицы элемент", i, j);
                mat->typeInfo->print(elem_ptr);
                ASSERT_EQ(elem_mat.real, elem.real);  
                ASSERT_EQ(elem_mat.imag, elem.imag);  
            }
        }
    }
    matrix_free(mat);

    printf("\n\n=== Обработка ошибок создания===\n");
    
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
    for(size_t i = 0; i < mat->dimension; i++){
        for(size_t j = 0; j < mat->dimension; j++){
            void* elem_ptr = (char*)array_el + (i * mat->dimension + j) * typeInfo->size;
            error = push_el_matrix(mat, elem_ptr, i, j);
        }
    }

    printf("\nПервая матрица умножения\n");
    print_matrix(mat);

    Matrix* mat_2 = matrix_create(3, typeInfo, &error);
    for(size_t i = 0; i < mat_2->dimension; i++){
        for(size_t j = 0; j < mat_2->dimension; j++){
            void* elem_ptr = (char*)array_el_2 + (i * mat_2->dimension + j) * typeInfo->size;
            error = push_el_matrix(mat_2, elem_ptr, i, j);
        }
    }

    printf("\nВторая матрица умножения\n");
    print_matrix(mat_2);

    printf("\nУмножение матриц (функция matrix_mult)\n");
    Matrix* mult = matrix_mult(mat, mat_2, &error);

    for(size_t i = 0; i < mat->dimension; i++){
        for(size_t j = 0; j < mat_2->dimension; j++){
            void* sum = malloc(mat->typeInfo->size);
            memset(sum, 0, mat->typeInfo->size);
            for(size_t k = 0; k < mat -> dimension; k++){
                void* ptr = element_get(mat, i, k, &error);
                void* ptr_2 = element_get(mat_2, k, j, &error);
                void* mult_el = malloc(mat->typeInfo->size);
                mat->typeInfo->multiply(mult_el, ptr, ptr_2);
                mat->typeInfo->add(sum, sum, mult_el);
                free(mult_el);
            }
            printf("\nmatrix_mult: элемент [%zu][%zu]. ", i, j);
            printf("Ожидаемый результат:");
            mult->typeInfo->print(sum);
            printf(" Полученный результат:");
            mult->typeInfo->print(element_get(mult, i, j, &error));
            if (typeInfo->size == sizeof(int)){
                ASSERT_EQ(*(int*)element_get(mult, i, j, &error), *(int*)sum);
            } else if (typeInfo->size == sizeof(float)){
                ASSERT_EQ(*(float*)element_get(mult, i, j, &error), *(float*)sum);
            } else if (typeInfo->size == sizeof(int)){
                Complex elem = *(Complex*)element_get(mult, i, j, &error);
                Complex elem_mat = *(Complex*)sum;
                ASSERT_EQ(elem_mat.real, elem.real);  
                ASSERT_EQ(elem_mat.imag, elem.imag);
            }
        }
    }

    printf("\nПервая матрица сложения\n");
    print_matrix(mat);
    printf("\nВторая матрица сложения\n");
    print_matrix(mat_2);
    printf("\nСложение матриц (функция matrix_add)\n");
    Matrix* sum = matrix_add(mat, mat_2, &error);

    for(size_t i = 0; i < mat->dimension; i++){
        for(size_t j = 0; j < mat->dimension; j++){
            void* sum_mat = malloc(mat->typeInfo->size);
            void* ptr = element_get(mat, i, j, &error);
            void* ptr_2 = element_get(mat_2, i, j, &error);
            mat->typeInfo->add(sum_mat, ptr, ptr_2);
            printf("\nmatrix_add: элемент [%zu][%zu]. ", i, j);
            printf("Ожидаемый результат:");
            sum->typeInfo->print(sum_mat);
            printf(" Полученный результат:");
            sum->typeInfo->print(element_get(sum, i, j, &error));
            if (typeInfo->size == sizeof(int)){
                ASSERT_EQ(*(int*)sum_mat, *(int*)element_get(sum, i, j, &error));
            } else if((typeInfo->size == sizeof(float))){
                ASSERT_EQ(*(float*)sum_mat, *(float*)element_get(sum, i, j, &error));
            } else if((typeInfo->size == sizeof(Complex))){
                Complex elem = *(Complex*)element_get(sum, i, j, &error);
                Complex elem_mat = *(Complex*)sum_mat;
                ASSERT_EQ(elem.real, elem_mat.real);
                ASSERT_EQ(elem.imag, elem_mat.imag);
            }
        }
    }

    printf("\nТранспонироание матрицы (функция matrix_transp)\n");
    printf("\nМатрица для транспонирования\n");
    print_matrix(mat);
    Matrix* transp = matrix_transp(mat, &error);
    for(size_t i = 0; i < mat->dimension; i++){
        for(size_t j = 0; j < mat->dimension; j++){
            printf("\nmatrix_transp: элемент [%zu][%zu]. ", i, j);
            printf("Ожидаемый результат:");
            sum->typeInfo->print(element_get(mat, i, j, &error));
            printf(" Полученный результат:");
            sum->typeInfo->print(element_get(transp, j, i, &error));
            if (typeInfo->size == sizeof(int)){
                ASSERT_EQ(*(int*)element_get(mat, i, j, &error), *(int*)element_get(transp, j, i, &error));
            } else if((typeInfo->size == sizeof(float))){
                ASSERT_EQ(*(float*)element_get(mat, i, j, &error), *(float*)element_get(transp, j, i, &error));
            } else if((typeInfo->size == sizeof(Complex))){
                Complex elem = *(Complex*)element_get(mat, i, j, &error);
                Complex elem_mat = *(Complex*)element_get(transp, j, i, &error);
                ASSERT_EQ(elem_mat.real, elem.real);  
                ASSERT_EQ(elem_mat.imag, elem.imag);
            }
        }
    }

    matrix_free(mat_2);
    printf("\nУмножение на скаляр 3 (matrix_multiply_const)\n");
    printf("\nМатрица для умножения на скаляр\n");
    print_matrix(mat);
    mat_2 = matrix_create(3, typeInfo, &error);
    for(size_t i = 0; i < mat_2->dimension; i++){
        for(size_t j = 0; j < mat_2->dimension; j++){
            void* elem_ptr = (char*)array_el + (i * mat_2->dimension + j) * typeInfo->size;
            error = push_el_matrix(mat_2, elem_ptr, i, j);
        }
    }
    matrix_multiply_const(mat, 3);
     for(size_t i = 0; i < mat -> dimension; i++){
        for(size_t j = 0; j < mat -> dimension; j++){
            void* ptr = element_get(mat_2, i, j, &error);
            void* mult_el = malloc(mat->typeInfo->size);
            mat->typeInfo->mult_const(mult_el, ptr, 3);
            printf("\nmatrix_transp: элемент [%zu][%zu]. ", i, j);
            printf("Ожидаемый результат:");
            sum->typeInfo->print(mult_el);
            printf(" Полученный результат:");
            sum->typeInfo->print(element_get(mat, i, j, &error));
            if (typeInfo->size == sizeof(int)){
                ASSERT_EQ(*(int*)mult_el, *(int*)element_get(mat, i, j, &error));
            } else if (typeInfo->size == sizeof(float)){
                ASSERT_EQ(*(float*)mult_el, *(float*)element_get(mat, i, j, &error));
            } else if (typeInfo->size == sizeof(Complex)){
                Complex ptr = *(Complex*)mult_el;
                Complex ptr_2 = *(Complex*)element_get(mat, i, j, &error);
                ASSERT_EQ(ptr.real, ptr_2.real);
                ASSERT_EQ(ptr.imag, ptr_2.imag);
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
    
    test_operation(array_el, array_el_2, GetComplexTypeInfo());

    printf("\n=== Тестирование матрицы комплексных чисел закончен ===\n");
}

void run_all_matrix()
{
    run_int_matrix();
    run_float_matrix();
    run_complex_matrix();
}