#include <stdio.h>
#include <locale.h>
#include "include/func.h"


int main(void) {
    char *locale = setlocale(LC_ALL, "");

    int type, choice;
    do {
        print_type();
        scanf("%d", &type);
        if(type == 0){
            error_print(1);
            return 0;
        }
        print_menu();
        scanf("%d", &choice);
        choice_type(choice, type);
    } while (choice != 0 && type != 0);
}