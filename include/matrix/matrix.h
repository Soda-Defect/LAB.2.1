#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>

typedef struct {
    void* data;               // Непрерывный блок памяти для всех элементов
    size_t element_size;      // Размер одного элемента
    size_t rows;              // Количество строк
    size_t cols;              // Количество столбцов
    
    // Функции для работы с элементами
    void (*print_element)(void*);                    // Печать элемента
    void (*add_elements)(void*, void*, void*);       // Сложение элементов
    void (*multiply_elements)(void*, void*, void*);  // Умножение элементов
} Matrix;

Matrix* matrix_create(size_t rows, size_t cols, size_t element_size,
                      void (*print_element)(void*),
                      void (*add_elements)(void*, void*, void*),
                      void (*multiply_elements)(void*, void*, void*));
void push_back(Matrix* mat, void* item, int row, int col);
void* element_get(Matrix* mat, int row, int col);
void print_matrix(Matrix* mat);
void matrix_free(Matrix* mat);

#endif //MATRIX_H