#include <stdio.h>
#include <locale.h>
#include "../include/interface.h"
#include "../include/matrix/matrix_error.h"


int main(void) {
    char *locale = setlocale(LC_ALL, "");
    MatrixErrors error;

    int type;
    do {
        print_type();
        type = int_input_value("Ваш выбор: ");
        type = process_types(type);
    } while (type != 0);
}

//убрать транслиты из названий
//корректные названия файлов и функций (func.c - название не отражает сути файла)
//в тестах очень избыточное количество проверок на ошибку (особенно во вложенных циклах, но и не только)
