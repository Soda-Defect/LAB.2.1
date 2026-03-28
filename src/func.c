#include <stdio.h>
#include "../include/tests.h"
#include "../include/complex.h"
#include "../include/matrix/matrix.h"
#include "../include/matrix/matrix_int.h"
#include "../include/matrix/matrix_float.h"
#include "../include/matrix/matrix_complex.h"

void print_type()
{
    printf("\n===================================\n");
    printf("        КОНСОЛЬНОЕ МЕНЮ            \n");
    printf("===================================\n");
    printf("           ТИПЫ ДАННЫХ             \n");
    printf("1. Работа с матрицей целых чисел.\n");
    printf("2. Работа с матрицей вещественных чисел.\n");
    printf("3. Работа с матрицей комплексных чисел.\n");
    printf("4. Запуск тестов со всеми типами.\n");
    printf("0. Выход.\n");
    printf("===================================\n");
}

void print_menu()
{
    printf("\n===================================\n");
    printf("        КОНСОЛЬНОЕ МЕНЮ            \n");
    printf("===================================\n");
    printf("       Квадратная матрица          \n");
    printf("1. Сложение матриц\n");
    printf("2. Произведение матриц\n");
    printf("3. Транспонирование матрицы\n");
    printf("4. Умножение на скаляр\n");
    printf("0. Выход.\n");
    printf("===================================\n");
}

void error_print(int error)
{
    switch(error)
    {
        case 1:
            printf("Выход из программы!\n");
            break;
        case 5:
            printf("Неправильный выбор! Выберите действие из представленных в меню!\n");
            break;
        case 7:
            printf("ОШИБКА: Отсутствует i в комплексном числе!\n");
            break;
        case 10:
            printf("ОШИБКА: Номер строки должен быть больше нуля!\n");
            break;
        case 11:
            printf("ОШИБКА: Номер строки не может быть больше максимального номера строки матрицы!\n");
            break;
        case 12:
            printf("ОШИБКА: Нужно вводить целое число!\n");
            break;
        case 13:
            printf("ОШИБКА: Нужно вводить вещественное число!\n");
            break;
        case 14:
            printf("ОШИБКА: Нужно вводить комплексное в формате a+bi число!\n");
            break;
    }
}

void print_matrix_error(MatrixErrors error) {
    switch(error) {
        case MEMORY_ALLOCATION_FAILED:
            printf("ОШИБКА: Выделения памяти!\n");
            break;
        case MATRIX_NOT_DEFINED:
            printf("ОШИБКА: Матрица не найдена или равна NULL!\n");
            break;
        case OPERATION_NOT_DEFINED:
            printf("ОШИБКА: Операция не определена для этого типа!\n");
            break;
        case INCOMPATIBLE_MATRIX_TYPES:
            printf("ОШИБКА: Несовместимые типы матриц!\n");
            break;
        case INVALID_MATRIX_SIZE:
            printf("ОШИБКА: Недопустимый размер матрицы (должен быть положительным)!\n");
            break;
        case INVALID_MATRIX_INDEX:
            printf("ОШИБКА: Указанный номер не входит в диапазон размера!\n");
            break;
        case INVALID_TYPE_INFO:
            printf("ОШИБКА: Неверная информация о типе\n");
            break;
        case MATRIX_SIZE_MISMATCH:
            printf("ОШИБКА: Несоответствие размера матрицы для работы (матрицы должны быть одинаковой размерности)!\n");
            break;
        default:
            printf("Произошла неизвестная ошибка\n");
            break;
    }
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int int_input_value(const char* prompt)
{
    int value, success;
    char term;
    do {
        printf("%s", prompt);
        success = 0;
        if (scanf("%d%c", &value, &term) == 2 && term == '\n') {
            success = 1;
        } else {
            error_print(12);
            clearInputBuffer();
        }
    } while (!success);
    
    return value;
}

void int_input(Matrix* mat)
{
    int value, success;
    char term;
    for(int i = 0; i < mat -> razm; i++){
        for(int j = 0; j < mat -> razm; j++){
            do{
                success = 0;
                printf("Введите элемент[%d][%d] целого типа:\n", i, j);
                if (scanf("%d%c", &value, &term) == 2 && term == '\n') {
                    success = 1;
                    push_el_matrix(mat, &value, i, j);
                } else {
                    error_print(12);
                    clearInputBuffer();
                }
            }while(!success);
        }
    }
}

void float_input(Matrix* mat)
{
    float value;
    int success;
    char term;
    for(int i = 0; i < mat -> razm; i++){
        for(int j = 0; j < mat -> razm; j++){
            do{
                success = 0;
                printf("Введите элемент[%d][%d] вещественного типа:\n", i, j);
                if (scanf("%f%c", &value, &term) == 2 && term == '\n') {
                    success = 1;
                    push_el_matrix(mat, &value, i, j);
                } else {
                    error_print(13);
                    clearInputBuffer();
                }
            }while(!success);
        }
    }
}

void complex_input(Matrix* mat)
{
    int re, im, success;
    char sign, i_char, term;
    for(int i = 0; i < mat -> razm; i++){
        for(int j = 0; j < mat -> razm; j++){
            do{
                success = 0;
                printf("Введите элемент[%d][%d] в формате a+bi: \n", i, j);
                if (scanf("%d%c%d%c%c", &re, &sign, &im, &i_char, &term) == 5 && term == '\n'){
                    if(i_char != 'i'){
                        error_print(7);
                    }else {
                        if(sign == '-'){
                        im *= -1;
                        }
                        Complex c = complex_create(re, im);
                        push_el_matrix(mat, &c, i, j);
                        success = 1;
                        }
                }else {
                    error_print(14);
                    clearInputBuffer();
                }
            }while(!success);   
        }
    }
}

void process(int choice, Matrix* mat_1, Matrix* mat_2)
{
    if(choice == 0){
        error_print(1);
        return;
    }

    MatrixErrors error;

    switch (choice)
    {
        case 0:
            error_print(1);
            return;
        case 1:
            Matrix* sum = matrix_add(mat_1, mat_2, &error);
            printf("\nПолученная Матрица: \n");
            print_matrix(sum);
            matrix_free(mat_1);
            matrix_free(mat_2);
            matrix_free(sum);
            break;
        case 2:
            Matrix* mult = matrix_mult(mat_1, mat_2, &error);
            printf("\nПолученная Матрица: \n");
            print_matrix(mult);
            matrix_free(mat_1);
            matrix_free(mat_2);
            matrix_free(mult);
            break;
        case 3:
            Matrix* transp = matrix_transp(mat_1, &error);
            printf("\nПолученная Матрица: \n");
            print_matrix(transp);
            matrix_free(mat_1);
            matrix_free(transp);
            break;
        case 4:
            int alpha;
            alpha = int_input_value("На какое число умножить?\n");
            error = matrix_multiply_const(mat_1, alpha);
            printf("\nПолученная Матрица: \n");
            print_matrix(mat_1);
            matrix_free(mat_1);
            break;
        default:
            error_print(5);
            break;
    }
}

int process_types(int type)
{
    int razm, choice;
    Matrix* mat_1 = NULL;
    Matrix* mat_2 = NULL;

    MatrixErrors error;

    if(type >= 1 && type <= 3){
        print_menu();
        choice = int_input_value("Ваш выбор: ");
        if(choice >= 1 && choice <= 4){
            razm = int_input_value("Введите размерность квадратной матрицы\n");
        }
        else{
            if(choice == 0){
                type = 0;
            }
            error_print(5);
            return type;
        }
    }

    switch(type)
    {
        case 0:
            error_print(1);
            return type;
        case 1:
            mat_1 = matrix_create(razm, GetIntTypeInfo(), &error);
            int_input(mat_1);
            printf("\nМатрица: \n");
            print_matrix(mat_1);
            if(choice >= 1 && choice <= 2){
                razm = int_input_value("Введите размерность второй квадратной матрицы\n");
                mat_2 = matrix_create(razm, GetIntTypeInfo(), &error);
                int_input(mat_2);
                printf("\nВторая Матрица: \n");
                print_matrix(mat_2);
            }
            break;
        case 2:
            mat_1 = matrix_create(razm, GetFloatTypeInfo(), &error);
            float_input(mat_1);
            printf("\nМатрица: \n");
            print_matrix(mat_1);
            if(choice >= 1 && choice <= 2){
                razm = int_input_value("Введите размерность второй квадратной матрицы\n");
                mat_2 = matrix_create(razm, GetFloatTypeInfo(), &error);
                float_input(mat_2);
                printf("\nВторая Матрица: \n");
                print_matrix(mat_2);
            }
            break;
        case 3:
            mat_1 = matrix_create(razm, GetComplexTypeInfo(), &error);
            complex_input(mat_1);
            printf("\nМатрица: \n");
            print_matrix(mat_1);
            if(choice >= 1 && choice <= 2){
                razm = int_input_value("Введите размерность второй квадратной матрицы\n");
                mat_2 = matrix_create(razm, GetComplexTypeInfo(), &error);
                complex_input(mat_2);
                printf("\nВторая Матрица: \n");
                print_matrix(mat_2);
            }
            break;
        case 4:
            run_all_matrix();
            return type;
        default:
            error_print(5);
            return type;
    }

    process(choice, mat_1, mat_2);
    return type;
}