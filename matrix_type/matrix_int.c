#include <stdio.h>
#include "../include/matrix/matrix.h"
#include "../include/matrix/matrix_int.h"

static TypeInfo* INT_TYPE_INFO = NULL;

void print_int(void* element) {
    printf("%3d", *(int *)element);
}

void add_int(void* result, void* a, void* b) {
    *(int *)result = *(int *)a + *(int *)b;
}

void mult_int(void* result, void* a, void* b) {
    *(int *)result = (*(int *)a * *(int *)b);
}

void mult_int_const(void* result, void* a, int b) {
    *(int *)result = (*(int *)a * b);
}

TypeInfo* GetIntTypeInfo() {
    if (INT_TYPE_INFO == NULL) {
        INT_TYPE_INFO = (TypeInfo*)malloc(sizeof(TypeInfo));
        INT_TYPE_INFO->size = sizeof(int);
        INT_TYPE_INFO->add = add_int;
        INT_TYPE_INFO->multiply = mult_int; 
        INT_TYPE_INFO->mult_const = mult_int_const;
        INT_TYPE_INFO->print = print_int;
    }
    return INT_TYPE_INFO;
}