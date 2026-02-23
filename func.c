#include <stdio.h>

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
    }
}

void process(int choice)
{
    switch (choice)
    {
        case 0:
            error_print(1);
            return;
        case 1:
            break;
        case 2:
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

void choice_type(int choice, int type)
{
    switch(type)
    {
        case 0:
            error_print(1);
            return;
        case 1:
            printf("Выбран целый\n");
            process(choice);
            break;
        case 2:
            printf("Выбран вещественный\n");
            process(choice);
            break;
        case 3:
            printf("Выбран комплексный\n");
            process(choice);
            break;
        default:
            error_print(5);
            break;
    }
}