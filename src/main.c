#include <stdio.h>
#include <locale.h>
#include "../include/interface.h"


int main(void) {
    setlocale(LC_ALL, "");;

    int type;
    do {
        print_type();
        type = int_input_value("Ваш выбор: ");
        type = process_types(type);
    } while (type != 0);
}