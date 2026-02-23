#include <stdio.h>
#include "include/matrix/matrix.h"
#include "include/matrix/matrix_int.h"
#include "include/matrix/matrix_float.h"
#include "include/matrix/matrix_complex.h"

void print_type()
{
    printf("\n===================================\n");
    printf("        КОНСОЛЬНОЕ МЕНЮ            \n");
    printf("===================================\n");
    printf("           ТИПЫ ДАННЫХ             \n");
    printf("1. Работа с матрицей целых чисел.\n");
    printf("2. Работа с матрицей дробных чисел.\n");
    printf("3. Работа с матрицей комплексных чисел.\n");
    printf("0. Выход.\n");
    printf("===================================\n");
    printf("Ваш выбор: ");
}

void print_menu()
{
    printf("\n===================================\n");
    printf("        КОНСОЛЬНОЕ МЕНЮ            \n");
    printf("===================================\n");
    printf("      Прямоугольная матрица        \n");
    printf("1. Сложение матриц\n");
    printf("2. Произведение матриц\n");
    printf("3. Транспонирование матрицы\n");
    printf("4. Прибавление к строке линейной комбинации других строк\n");
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
    }
}

void int_input(Matrix* mat)
{
    int value;
    printf("Введите элементы:\n");
    for(int i = 0; i < mat -> rows; i++){
        for(int j = 0; j < mat -> cols; j++){
            scanf("%d", &value);
            push_back(mat, &value, i, j);
        }
    }
}

void float_input(Matrix* mat)
{
    float value;
    printf("Введите элементы:\n");
    for(int i = 0; i < mat -> rows; i++){
        for(int j = 0; j < mat -> cols; j++){
            scanf("%f", &value);
            push_back(mat, &value, i, j);
        }
    }
}

void complex_input(Matrix* mat)
{
    double re, im;
    char sign, i_char;
    printf("Введите элементы в формате a+bi: \n");
    for(int i = 0; i < mat -> rows; i++){
        for(int j = 0; j < mat -> cols; j++){
            scanf("%lf%c%lf%c", &re, &sign, &im, &i_char);
            if(sign == '-'){
                im *= -1;
            }
            if(i_char != 'i'){
                error_print(7);
            }
            Complex c = complex_create(re, im);
            push_back(mat, &c, i, j);
            
        }
    }
}

void process(int choice, int type)
{
    int rows, cols;
    Matrix* mat_1 = NULL;
    Matrix* mat_2 = NULL;
    if(choice == 0){
        error_print(1);
        return;
    }

    printf("Введите количество строк матрицы\n");
    scanf("%d", &rows);
    printf("Введите количество столбцов матрицы\n");
    scanf("%d", &cols);

    switch(type)
    {
        case 1:
            mat_1 = create_int_matrix(rows, cols);
            int_input(mat_1);
            printf("\nМатрица: \n");
            print_matrix(mat_1);
            if(choice >= 1 && choice <= 2){
                printf("Введите количество строк матрицы\n");
                scanf("%d", &rows);
                printf("Введите количество столбцов матрицы\n");
                scanf("%d", &cols);
                mat_2 = create_int_matrix(rows, cols);
                int_input(mat_2);
                printf("\nВторая Матрица: \n");
                print_matrix(mat_2);
            }
            break;
        case 2:
            mat_1 = create_float_matrix(rows, cols);
            float_input(mat_1);
            printf("\nМатрица: \n");
            print_matrix(mat_1);
            if(choice >= 1 && choice <= 2){
                printf("Введите количество строк матрицы\n");
                scanf("%d", &rows);
                printf("Введите количество столбцов матрицы\n");
                scanf("%d", &cols);
                mat_2 = create_float_matrix(rows, cols);
                float_input(mat_2);
                printf("\nВторая Матрица: \n");
                print_matrix(mat_2);
            }
            break;
        case 3:
            mat_1 = create_complex_matrix(rows, cols);
            complex_input(mat_1);
            printf("\nМатрица: \n");
            print_matrix(mat_1);
            if(choice >= 1 && choice <= 2){
                printf("Введите количество строк матрицы\n");
                scanf("%d", &rows);
                printf("Введите количество столбцов матрицы\n");
                scanf("%d", &cols);
                mat_2 = create_complex_matrix(rows, cols);
                complex_input(mat_2);
                printf("\nВторая Матрица: \n");
                print_matrix(mat_2);
            }
            break;
        default:
            error_print(5);
            break;
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
            break;
        case 2:
            Matrix* mult = matrix_mult(mat_1, mat_2);
            printf("\nПолученная Матрица: \n");
            print_matrix(mult);
            break;
        case 3:
            break;
        case 4:
            break;
        default:
            error_print(5);
            break;
    }
}