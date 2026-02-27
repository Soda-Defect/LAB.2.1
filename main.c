#include <stdio.h>
#include <locale.h>
#include "include/func.h"


int main(void) {
    char *locale = setlocale(LC_ALL, "");

    int type;
    do {
        print_type();
        scanf("%d", &type);
        type = process_types(type);
    } while (type != 0);
}