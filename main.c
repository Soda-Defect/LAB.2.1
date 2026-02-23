#include <stdio.h>
#include <locale.h>
#include "include/func.h"


int main(void) {
    char *locale = setlocale(LC_ALL, "");

    int choice_type, choice;
    do {
        print_type();
        scanf("%d", &choice_type);
        print_menu();
        scanf("%d", &choice);
        process(choice, choice_type);
    } while (choice != 0 && choice_type != 0);
}