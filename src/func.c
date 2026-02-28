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
    printf("2. Работа с матрицей дробных чисел.\n");
    printf("3. Работа с матрицей комплексных чисел.\n");
    printf("4. Запуск тестов со всеми типами.\n");
    printf("0. Выход.\n");
    printf("===================================\n");
    printf("Ваш выбор: ");
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
    printf("Ваш выбор: ");
}

void error_print(int error)
{
    switch(error)
    {
        case 1:
            printf("Выход из программы!\n");
            break;
        case 2:
            printf("ОШИБКА: Размер матрицы должен быть положительным!\n");
            break;
        case 3:
            printf("Ошибка выделения памяти для матрицы!\n");
            break;
        case 4:
            printf("ОШИБКА: Размер элемента должен быть больше нуля!\n!\n");
            break;
        case 5:
            printf("Неправильный выбор! Выберите действие из представленных в меню!\n");
            break;
        case 6:
            printf("ОШИБКА: Указанный номер не входит в диапозон размера!\n");
            break;
        case 7:
            printf("ОШИБКА: Отсутствует i в комплексном числе!\n");
            break;
        case 8:
            printf("ОШИБКА: Для сложения матрицы должны быть одинаковой размерности!\n");
            break;
        case 9:
            printf("ОШИБКА: Для произведения количество столбцов первой матрицы должно быть равно количеству строк второй матрицы!\n");
            break;
        case 10:
            printf("ОШИБКА: Номер строки должен быть больше нуля!\n");
            break;
        case 11:
            printf("ОШИБКА: Номер строки не может быть больше максимального номера строки матрицы!\n");
            break;
    }
}

void int_input(Matrix* mat)
{
    int value;
    printf("Введите элементы:\n");
    for(int i = 0; i < mat -> razm; i++){
        for(int j = 0; j < mat -> razm; j++){
            scanf("%d", &value);
            push_el_matrix(mat, &value, i, j);
        }
    }
}

void float_input(Matrix* mat)
{
    float value;
    printf("Введите элементы:\n");
    for(int i = 0; i < mat -> razm; i++){
        for(int j = 0; j < mat -> razm; j++){
            scanf("%f", &value);
            push_el_matrix(mat, &value, i, j);
        }
    }
}

void complex_input(Matrix* mat)
{
    int re, im;
    char sign, i_char;
    printf("Введите элементы в формате a+bi: \n");
    for(int i = 0; i < mat -> razm; i++){
        for(int j = 0; j < mat -> razm; j++){
            scanf("%d%c%d%c", &re, &sign, &im, &i_char);
            if(sign == '-'){
                im *= -1;
            }
            if(i_char != 'i'){
                error_print(7);
            }
            Complex c = complex_create(re, im);
            push_el_matrix(mat, &c, i, j);
            
        }
    }
}

void process(int choice, Matrix* mat_1, Matrix* mat_2)
{
    if(choice == 0){
        error_print(1);
        return;
    }

    switch (choice)
    {
        case 0:
            error_print(1);
            return;
        case 1:
            Matrix* sum = matrix_add(mat_1, mat_2);
            printf("\nПолученная Матрица: \n");
            print_matrix(sum);
            matrix_free(mat_1);
            matrix_free(mat_2);
            matrix_free(sum);
            break;
        case 2:
            Matrix* mult = matrix_mult(mat_1, mat_2);
            printf("\nПолученная Матрица: \n");
            print_matrix(mult);
            matrix_free(mat_1);
            matrix_free(mat_2);
            matrix_free(mult);
            break;
        case 3:
            Matrix* transp = matrix_transp(mat_1);
            printf("\nПолученная Матрица: \n");
            print_matrix(transp);
            matrix_free(mat_1);
            matrix_free(transp);
            break;
        case 4:
            int alpha;
            printf("На какое число умножить?\n");
            scanf("%d", &alpha);
            matrix_multiply_const(mat_1, alpha);
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

    if(type != 4 && type != 0){
        print_menu();
        scanf("%d", &choice);
        if(choice == 0){
            type = 0;
        }
        else{
            printf("Введите размерность квадратной матрицы\n");
            scanf("%d", &razm);
        }
    }

    switch(type)
    {
        case 0:
            error_print(1);
            return type;
        case 1:
            mat_1 = create_int_matrix(razm);
            int_input(mat_1);
            printf("\nМатрица: \n");
            print_matrix(mat_1);
            if(choice >= 1 && choice <= 2){
                printf("Введите размерность квадратной матрицы\n");
                scanf("%d", &razm);
                mat_2 = create_int_matrix(razm);
                int_input(mat_2);
                printf("\nВторая Матрица: \n");
                print_matrix(mat_2);
            }
            break;
        case 2:
            mat_1 = create_float_matrix(razm);
            float_input(mat_1);
            printf("\nМатрица: \n");
            print_matrix(mat_1);
            if(choice >= 1 && choice <= 2){
                printf("Введите размерность квадратной матрицы\n");
                scanf("%d", &razm);
                mat_2 = create_float_matrix(razm);
                float_input(mat_2);
                printf("\nВторая Матрица: \n");
                print_matrix(mat_2);
            }
            break;
        case 3:
            mat_1 = create_complex_matrix(razm);
            complex_input(mat_1);
            printf("\nМатрица: \n");
            print_matrix(mat_1);
            if(choice >= 1 && choice <= 2){
                printf("Введите размерность квадратной матрицы\n");
                scanf("%d", &razm);
                mat_2 = create_complex_matrix(razm);
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
            break;
    }

    process(choice, mat_1, mat_2);
    return type;
}