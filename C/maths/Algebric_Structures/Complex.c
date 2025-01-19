#include "Complex.h"

#include "maths/functions/Trigonometry.h"


#include <stdlib.h>

//////  Functions

Complex* createComplex(float re, float im)
{
    Complex* z = malloc(sizeof(Complex));

    z->re = re;
    z->im = im;

    return z;
}

void freeComplex(Complex* const z) {
    free(z);
}

////////////// Operation

Complex multiply(Complex z1, Complex z2)  {
    Complex z = {z1.re * z2.re - z1.im * z2.im,   z1.re * z2.im + z1.im * z2.re};
    return z;
}

/* Compute z1/z2    ////////////    Completer pour check la division par 0*/
Complex divide(Complex z1, Complex z2) {

    Complex z = multiply(z1, conjugate(z2));

    double denom = z2.re * z2.re   +   z2.im * z2.im;

    z.re /= denom;
    z.im /= denom;

    return z;
}

Complex add(Complex z1, Complex z2) {
    Complex z = {z1.re + z2.re, z1.im + z2.im};
    return z;
}

Complex substract(Complex z1, Complex z2) {
    Complex z = {z1.re - z2.re, z1.im - z2.im};
}





//////////////



float mod(Complex z);


float arg(Complex z){
    if(z.re == 0)
    {
        return PI/2 * (2 * ((z.im > 0) - 0.5f));
    } else if (z.re > 0)
    {
        return atan(z.im / z.re);
    } else
    {

    }

}


Complex conjugate(Complex z) {
    Complex z2 = {z.re, -z.im};
    return z2;
}

///// Others

void printComplex(Complex const z)
{
    printf("%.3f + i * %.3f ", z.re, z.im);
}