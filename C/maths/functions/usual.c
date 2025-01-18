#include "usual.h"

float abs_f(float x){
    return (x > 0)*x + (x < 0)*x;
}

uint32_t abs(int x){
    return (x > 0)*x + (x < 0)*x;
}

double abs_d(double x) {
    return (x > 0)*x + (x < 0)*x;
}



int sgn(int x){
    return 2 * (0.5f - (float)(x < 0));
}

int sgn_f(float x){
    return 2.0f * (0.5f - (float)(x < 0));
}

int sgn_d(float x){
    return 2.0f * (0.5f - (float)(x < 0));
}