#include "usual.h"

#include "constants_maths.h"



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

/* calcul exp par DL */
double exp(double x){ 
    
    if(x < 0){
        return 1/exp(-x);
    }
    double term = 1;
    double result = term;
    double n = 1;
    while (abs(term) > 1e-12){
        term *= x/n;
        result += term;
        n += 1;
    }
    return result;
}

/* 
 * Donne la congruence de `x` modulo `mod` sur [0, mod]
 */
double modulo_real(double x, double mod) {
    x -= mod * ((long)(x / mod));
    
    // Ajustement pour obtenir un résultat dans [0, mod]
    if (x < 0) {
        x += mod;
    }
    return x;
}