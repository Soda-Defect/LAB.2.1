#include <stdio.h>
#include <locale.h>
#include "../include/func.h"

void print_message(char* msg){
    printf("%s\n", msg);
}

int main(void) {
    char *locale = setlocale(LC_ALL, "");

    int type, choice;
    do {
        print_message(print_type());
        type = int_input_value("Ваш выбор: ");
        if(type == 0){
            print_message(error_print(1));
        }
        else if(type > 0 && type < 5){
            print_message(print_menu());
            choice = int_input_value("Ваш выбор: ");
            if(choice == 0){
                print_message(error_print(1));
            }
            else if(choice > 0 && choice < 5){
                process_types(type, choice);
            }
            else{
                print_message(error_print(5));
            }
        }else{
            print_message(error_print(5));
        }
    } while (type != 0 && choice != 0);
}