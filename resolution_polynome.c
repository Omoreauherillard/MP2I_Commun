#include <stdio.h>
#include <math.h>
#include <stdarg.h>

typedef unsigned int uint;

/////////////// Libraries

#include "maths/Complex.h"




///////////////// STRUCTS - ENUMS


typedef struct {
    Complex* coefs;
} Poly;

//////////////// PROTOTYPES

Poly* createPoly(uint deg, ...);





/////////////// FUNCTIONS' BODY

Poly* createPoly(uint deg, ...){
    va_list list_args;

    Poly* p = malloc(sizeof(Complex) * (deg+1));


    // we retrieve the polynom's coefficients
   va_start(list_args, deg + 1);
   for(uint i=0; i<deg + 1; i++)
   {
        p->coefs[i] = va_arg(list_args, Complex);
   }
   va_end(list_args);

   return p;
}





int main(int argc, char** argv) {

}