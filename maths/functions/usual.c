#include "usual.h"

float abs_f(float x){
    return (x > 0)*x + (x < 0)*x;
}


uint abs(int x){
    return (x > 0)*x + (x < 0)*x;
}

double abs_d(double x) {
    return (x > 0)*x + (x < 0)*x;
}