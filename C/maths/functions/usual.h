#pragma once
#include <stdint.h>

float abs_f(float x);
uint32_t abs(int x);
double abs_d(double x);



/// renvoie le signe de x, 1 si x = 0
int sgn(int x);

// renvoie le signe de x, 1 si x = 0
int sgn_f(float x);

// renvoie le signe de x, 1 si x = 0
int sgn_d(float x);


/* 
 * Donne la congruence de `x` modulo `mod` sur [0, mod]
 */
double modulo_real(double x, double mod);