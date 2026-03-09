#include <stdio.h>
#include <locale.h>
#include "../include/func.h"


int main(void) {
    char *locale = setlocale(LC_ALL, "");

    int type;
    do {
        print_type();
        type = int_input_value("Ваш выбор: ");
        type = process_types(type);
    } while (type != 0);
}