#ifndef FUNC_H
#define FUNC_H

#include "matrix/matrix_error.h"

void print_type();
void error_print(int error);
int process_types(int type);
int int_input_value(const char* prompt);
void print_matrix_error(MatrixErrors error);


#endif //FUNC_H