#include <stdio.h>
#include "../include/matrix/matrix.h"
#include "../include/matrix/matrix_float.h"

static TypeInfo* FLOAT_TYPE_INFO = NULL;

void print_float(void* element) {
    printf("%6.2f", *(float *)element);
}

void add_float(void* result, void* a, void* b) {
    *(float *)result = *(float *)a + *(float *)b;
}

void mult_float(void* result, void* a, void* b) {
    *(float *)result = (*(float *)a * *(float *)b);
}

void mult_float_const(void* result, void* a, int b) {
    *(float *)result = (*(float *)a * b);
}

TypeInfo* GetFloatTypeInfo() {
    if (FLOAT_TYPE_INFO == NULL) {
        FLOAT_TYPE_INFO = (TypeInfo*)malloc(sizeof(TypeInfo));
        FLOAT_TYPE_INFO->size = sizeof(float);
        FLOAT_TYPE_INFO->add = add_float;
        FLOAT_TYPE_INFO->multiply = mult_float; 
        FLOAT_TYPE_INFO->mult_const = mult_float_const;
        FLOAT_TYPE_INFO->print = print_float;
    }
    return FLOAT_TYPE_INFO;
}