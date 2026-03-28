#include <stdio.h>
#include <locale.h>
#include "../include/func.h"
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