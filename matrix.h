#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>

typedef struct{
    void* data;
    int rows;
    int cols;
} Matrix;

#endif //MATRIX_H