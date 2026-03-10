#include <stdio.h>
#include <string.h>
#include "../include/tests.h"
#include "../include/complex.h"
#include "../include/matrix/matrix.h"
#include "../include/matrix/matrix_int.h"
#include "../include/matrix/matrix_float.h"
#include "../include/matrix/matrix_complex.h"

char* print_type()
{
    char* text = (char*)malloc(500); 
    if (text == NULL){
        return NULL;
    }
    strcpy(text, "\n===================================\n");
    strcat(text, "        КОНСОЛЬНОЕ МЕНЮ            \n");
    strcat(text, "===================================\n");
    strcat(text, "           ТИПЫ ДАННЫХ             \n");
    strcat(text, "1. Работа с матрицей целых чисел.\n");
    strcat(text, "2. Работа с матрицей вещественных чисел.\n");
    strcat(text, "3. Работа с матрицей комплексных чисел.\n");
    strcat(text, "4. Запуск тестов со всеми типами.\n");
    strcat(text, "0. Выход.\n");
    strcat(text, "===================================\n");
    return text;
}

char* print_menu()
{
    char* text = (char*)malloc(500); 
    if (text == NULL){
        return NULL;
    }
    strcpy(text, "\n===================================\n");
    strcat(text, "        КОНСОЛЬНОЕ МЕНЮ            \n");
    strcat(text, "===================================\n");
    strcat(text, "       Квадратная матрица          \n");
    strcat(text, "1. Сложение матриц\n");
    strcat(text, "2. Произведение матриц\n");
    strcat(text, "3. Транспонирование матрицы\n");
    strcat(text, "4. Умножение на скаляр\n");
    strcat(text, "0. Выход.\n");
    strcat(text, "===================================\n");
    return text;
}

const char* error_print(int error)
{
    switch(error)
    {
        case 1:
            return "Выход из программы!\n";
        case 2:
            return "ОШИБКА: Размер матрицы должен быть положительным!\n";
        case 3:
            return "Ошибка выделения памяти для матрицы!\n";
        case 4:
            return "ОШИБКА: Размер элемента должен быть больше нуля!\n";
        case 5:
            return "Неправильный выбор! Выберите действие из представленных в меню!\n";
        case 6:
            return "ОШИБКА: Указанный номер не входит в диапазон размера!\n";
        case 7:
            return "ОШИБКА: Отсутствует i в комплексном числе!\n";
        case 8:
            return "ОШИБКА: Для сложения матрицы должны быть одинаковой размерности!\n";
        case 9:
            return "ОШИБКА: Для произведения размерности матриц должны быть одинаковы!\n";
        case 10:
            return "ОШИБКА: Номер строки должен быть больше нуля!\n";
        case 11:
            return "ОШИБКА: Номер строки не может быть больше максимального номера строки матрицы!\n";
        case 12:
            return "ОШИБКА: Нужно вводить целое число!\n";
        case 13:
            return "ОШИБКА: Нужно вводить вещественное число!\n";
        case 14:
            return "ОШИБКА: Нужно вводить комплексное в формате a+bi число!\n";
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

const char* process(int choice, Matrix* mat_1, Matrix* mat_2)
{
    if(choice == 0){
        return error_print(1);
    }

    switch (choice)
    {
        case 0:
            return error_print(1);
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
            alpha = int_input_value("На какое число умножить?\n");
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

int process_types(int type, int choice)
{
    int razm;
    Matrix* mat_1 = NULL;
    Matrix* mat_2 = NULL;

    switch(type)
    {
        case 0:
            return error_print(1);
        case 1:
            razm = int_input_value("Введите размерность квадратной матрицы\n");
            mat_1 = create_int_matrix(razm);
            int_input(mat_1);
            printf("\nМатрица: \n");
            print_matrix(mat_1);
            if(choice >= 1 && choice <= 2){
                razm = int_input_value("Введите размерность второй квадратной матрицы\n");
                mat_2 = create_int_matrix(razm);
                int_input(mat_2);
                printf("\nВторая Матрица: \n");
                print_matrix(mat_2);
            }
            break;
        case 2:
            razm = int_input_value("Введите размерность квадратной матрицы\n");
            mat_1 = create_float_matrix(razm);
            float_input(mat_1);
            printf("\nМатрица: \n");
            print_matrix(mat_1);
            if(choice >= 1 && choice <= 2){
                razm = int_input_value("Введите размерность второй квадратной матрицы\n");
                mat_2 = create_float_matrix(razm);
                float_input(mat_2);
                printf("\nВторая Матрица: \n");
                print_matrix(mat_2);
            }
            break;
        case 3:
            razm = int_input_value("Введите размерность квадратной матрицы\n");
            mat_1 = create_complex_matrix(razm);
            complex_input(mat_1);
            printf("\nМатрица: \n");
            print_matrix(mat_1);
            if(choice >= 1 && choice <= 2){
                razm = int_input_value("Введите размерность второй квадратной матрицы\n");
                mat_2 = create_complex_matrix(razm);
                complex_input(mat_2);
                printf("\nВторая Матрица: \n");
                print_matrix(mat_2);
            }
            break;
        case 4:
            run_all_matrix();
        default:
            return error_print(5);
    }

    return process(choice, mat_1, mat_2);
}