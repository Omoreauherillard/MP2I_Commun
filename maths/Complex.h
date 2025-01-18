#pragma once

#include "constants_maths.h"

typedef struct {
    float re;
    float im;
} Complex;


//////  Functions

Complex* createComplex(float re, float im);

Complex multiply(Complex z1, Complex z2);
Complex divide(Complex z1, Complex z2);
Complex add(Complex z1, Complex z2);
Complex substract(Complex z1, Complex z2);
float mod(Complex z);
float arg(Complex z);

void printComplex(Complex const z);
