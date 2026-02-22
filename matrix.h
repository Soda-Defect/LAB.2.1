#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>

// Типы данных
typedef enum {
    TYPE_INT,
    TYPE_DOUBLE
} DataType;

// Структура для хранения элемента матрицы
typedef struct {
    DataType type;
    union {
        int int_value;
        double double_value;
    } data;
} MatrixElement;

typedef struct{
    MatrixElement** data; //элементы
    int rows; //количество строк
    int cols; //количество столбцов
} Matrix;

Matrix* matrix_create(int rows, int cols, int type);

#endif //MATRIX_H