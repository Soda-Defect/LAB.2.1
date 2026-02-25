#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>

typedef struct {
    void* data;               // Непрерывный блок памяти для всех элементов
    size_t element_size;      // Размер одного элемента
    size_t razm;              // Размерность квадратной матрицы
    
    // Функции для работы с элементами
    void (*print_element)(void*);                    // Печать элемента
    void (*add_elements)(void*, void*, void*);       // Сложение элементов
    void (*multiply_elements)(void*, void*, void*);  // Умножение элементов
} Matrix;

Matrix* matrix_create(size_t razm, size_t element_size,
                      void (*print_element)(void*),
                      void (*add_elements)(void*, void*, void*),
                      void (*multiply_elements)(void*, void*, void*));
void push_el_matrix(Matrix* mat, void* item, int row, int col);
void* element_get(Matrix* mat, int row, int col);
Matrix* matrix_add(Matrix* mat_1, Matrix* mat_2);
Matrix* matrix_mult(Matrix* mat_1, Matrix* mat_2);
Matrix* matrix_transp(Matrix* mat_1);
void matrix_add_line_comb(Matrix* mat_1, int rowIndex, int rowAlph, void* alhpa);
void print_matrix(Matrix* mat);
void matrix_free(Matrix* mat);

#endif //MATRIX_H