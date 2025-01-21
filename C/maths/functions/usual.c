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



double pow2_d(long n) {
    if (n == 0) {
        return 1;
    } else if (n > 0) {
        double result = 1;
        for(int _ = 0; _ < n; _++)
        {
            result *= 2;
        }
        return result;
    } else {
        return 1 / pow2_d(-n);
    }
}




/* calcul d' exp par ....*/
double exp(double x) {
    double ln2 = 0.69314718055994530941723212145817656807550013436025525412068000949339362196;
    long k = (long)(x/ln2);
    double r = x - k * ln2;

    double term = 1;
    double p = term;
    int n = 1;

    while (abs_d(term) > 1e-16) {
        term *= r /n;
        n++;

        p += term;
    }
    return pow2_d(k) * p;
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
