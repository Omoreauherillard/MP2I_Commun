#include "Complex.h"
#include "maths/functions/Trigonometry.h"

//////  Functions

Complex* createComplex(float re, float im)
{
    Complex* z = malloc(sizeof(Complex));

    z->re = re;
    z->im = im;

    return z;
}

////////////// Operation

Complex multiply(Complex z1, Complex z2);
Complex divide(Complex z1, Complex z2);
Complex add(Complex z1, Complex z2);
Complex substract(Complex z1, Complex z2);


//////////////



float mod(Complex z);


float arg(Complex z){
    if(z.re == 0)
    {
        return PI/2 * (2 * ((z.im > 0) - 0.5f));
    } else if (z.im > 0)
    {
        return 
    }

}


///// Others

void printComplex(Complex const z)
{
    printf("%.3f + i * %.3f ", z.re, z.im);
}