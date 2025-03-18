/* But :
 *    • Dichotomie pour calculer une valeur de ln
 * Auteurs :   Oscar   
 * Version :   1.0  
 * Date    :   17/03/25 
 */


 #include <stdio.h>
 #include <assert.h>
 #include <math.h>
 #include <stdlib.h>
 
 
 
 /////////////////////////////////////////// STRUCTURES | ENUMERATION //////////////////////////////////////////
 
 
 ///////////////////////////////////////////////// PROTOTYPES //////////////////////////////////////////////////
 
 
 ///////////////////////////////////////////// CORPS DES FONCTIONS /////////////////////////////////////////////
 
 double absolute(double x){
     return x*(x>=0)-x*(x<0);
 }
 
 double log_np(double x, float precision){
     float a = -1000000., b = 1000000., m;
     while (a<=b){
         m = (a+b)/2;
         if (absolute(exp(m)-x)<=precision){
             return m;
         }
         else if (exp(m)<x){
             a = m;
         }
         else {
             b = m;
         }
     }
 }
 
 /////////////////////////////////////////////// TESTS UNITAIRES ///////////////////////////////////////////////
 
 
 ///////////////////////////////////////////////// ENTRY POINT /////////////////////////////////////////////////
 int main(int argc, char** argv) {
     return 0;
 }