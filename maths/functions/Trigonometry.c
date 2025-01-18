#include "Trigonometry.h"
#include "../constants_maths.h"
#include "usual.h"


float atan(float x)
{
    return (x*PI/4)-(x*(abs_f(x)-1)*(0.2447 + 0.0663*abs_f(x)))/(1+0.2447 * abs_f(x) + 0.0663 * x *x);
}