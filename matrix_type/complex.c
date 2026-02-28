#include <stdio.h>

#include "../include/complex.h"

Complex complex_create(int real, int imag) {
    Complex c;
    c.real = real;
    c.imag = imag;
    return c;
}

Complex complex_add(Complex a, Complex b) {
    return complex_create(a.real + b.real, a.imag + b.imag);
}

Complex complex_mul(Complex a, Complex b) {
    return complex_create(a.real * b.real - a.imag * b.imag, a.real * b.imag + b.real * a.imag);
}

void complex_print(Complex c) {
    if (c.imag >= 0) {
        printf("%.d + %.di", c.real, c.imag);
    } else {
        printf("%.d - %.di", c.real, -c.imag);
    }
}