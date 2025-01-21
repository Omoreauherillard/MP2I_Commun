#include "Trigonometry.h"
#include "../constants_maths.h"
#include "usual.h"
#include <stdint.h>


/*
 * Calcul d'une approximation de l'arc-tangente à l'aide de la Série de Maclaurin
 *
 *      - epsilon est le Critère d'arrêt :
 *          Il correspond à un seuil de la valeur absolu des termes de la série (on ne prend que les termes qui impactes le résulat)
 *          (valeur recommandée : 1e-10)
 * 
 *      - x est la valeur à laquelle on estime l'arc-tangente
 *
 *      - On utilise le fait que 
 *          Pour tout x réel, Arctan(x) = sgn(x)*pi/2 - Arctan(1/x)         (on montre que la somme est constante en dérivant l'expression)
 *          
 *          Ainsi, puisque la série de MacLaurin converge pour -1 <= x <= 1, si x est trop grand en valeur absolue, 1/x est dans [-1, 1]
 *
 * // pas testé
 */
double atan(double x)
{
    // on vérifie que x est dans [-1, 1]
    if (abs_f(x) > 1) {
        return sgn_f(x) * (PI / 2) - atan(1/x);
    }

    double term = x;        // le premier terme de la série
    double result = term;
    uint16_t n = 1;
    double x2 = x * x;   // on précalcul x² pour éviter les puissances répétées

    // Maclaurin's Series
    while (abs_d(term) > 1e-15) {
        term *= -x2;
        result += term / (2*n + 1);
        n++;
    }

    return result;
}

/* Calcul de  asin par DL */

double asin(double x){
    if (abs(x) != 1){
        x = x - (int)x;
    }
    else if(x == 1){
        return PI / 2;
    }
    else{
        return  -PI/2;
    }

    double term = x;
    double result = term;
    double x2 = x*x;
    double n = 1;

    while(abs(term)>1e-15){
        term *= x2 * ((2*n - 1) * (2*n)) / (4*n*n);
        result += term / (2*n + 1);
        n += 1;
    }
    return result;
}


/* Calcul acos par rapport a asin */

double acos(double x){
    return PI/2 - asin(x);
}



/* Calcul de la tangente (tan(x) = sin(x) / cos(x))*/
double tan(double x) {
    return sin(x) / cos(x);
}

/* 
 * Approximation du sinus par la série de Maclaurin
 *
 * Algo :
 *      - réduction de la plage de x sur [0, 2pi]
 *      - calcul des termes de la série jusqu'à ce qu'ils soient négligeables
 *
 * 
 * // pas testé
 */
double sin(double x) {
    // réduction de plage par la périodicité du cosinus
    x = modulo_real(x, 2*PI);

    double term = x;        // premier terme de la série
    double result = term;
    uint16_t n = 1;

    // les termes de la série sont des puissances impair, on stock le carre pour accélérer les calculs
    double x2 = x * x;

    // calcul de la série
    while (abs_d(term) > 1e-15) {
        term *= -x2 / ((2*n) * (2*n + 1));
        result += term;
        n++;
    }

    return result;
}

double cos(double x) {
    // réduction de plage par la périodicité du cosinus
    x = modulo_real(x, 2*PI);

    double term = x;        // premier terme de la série
    double result = term;
    uint16_t n = 1;

    // les termes de la série sont des puissances impair, on stock le carre pour accélérer les calculs
    double x2 = x * x;

    // calcul de la série
    while (abs_d(term) > 1e-15) {
        term *= -x2 / ((2*n - 1) * (2*n));
        result += term;
        n++;
    }

    return result;
}

/* fonction hyperboliques */

double ch(double x){
    return (exp(x)+exp(-x))/2;
}

double sh(double x){
    return (exp(x)-exp(-x))/2;
}

double th(double x){
    return sh(x)/ch(x);
}