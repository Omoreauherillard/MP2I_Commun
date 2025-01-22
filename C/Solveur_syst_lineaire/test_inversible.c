#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


void freeMat(double** Mat, int len) {
    for(int i = 0; i < len; i++) {
        free(Mat[i]);
    }
    free(Mat);
}

void print_line(double* line, int len) {
    printf("[ ");
    for(int i = 0; i < len; i++) {
        printf("%.3f ", line[i]);
    }
    printf("]");
}

void afficheMat(double** Mat, int len) {
    for(int i = 0; i < len; i++)
    {
        print_line(Mat[i], len);
        printf("\n");
    }
    printf("\n");
}


void normalize_line(double** M, int len, int line){
    printf("\nligne %d avant normalisation\n", line + 1);
    print_line(M[line], len);

    double facteur = 1/(M[line][line]);
    for(int k = line; k < len; k++){
        M[line][k] *= facteur; 
    }
    
    printf("\nligne %d normalisee\n", line + 1);
    print_line(M[line], len);
    printf("\n\n");
    
}

void permuter_line(double** M, int len, int l1, int l2){

    double tempol2[len]; 
    for (int col = 0; col < len; col++){
        tempol2[col] = M[l2][col];
        M[l2][col] = M[l1][col];
        M[l1][col] = tempol2[col];                 
    }

    printf("ligne %d permutee avec ligne %d\n", l1 + 1, l2 + 1);
}

void traiter_ligne(double** M, int len, int start, int stop, int diag){
    
    printf("\n**************\nTraitement des lignes de %d a %d\n", start + 1, stop);

    for(int l = start; l < stop ; l++){
        double factor = M[l][diag];
        printf("L%d <-- L%d - %.3f * L%d\n", l+1, l+1, factor, diag+1);
        if(factor == 0){
        printf("factor 0, we pass\n");
            continue;
        }
        
        printf("Line %d before traitement:\n", l+1);
        print_line(M[l], len);
        
        for(int col = diag; col < len ; col++){
            M[l][col] -= factor * M[diag][col];
        }
        
        printf("\n\nLine %d after traitement:\n", l+1);
        print_line(M[l], len);
        printf("\n\n");
    }
    
    printf("Fin du traitement des lignes de %d a %d\n**************\n", start + 1, stop);
}




bool testMatrice(const double** Me, int len){

    printf("\n***** Test Matrice ****\n");
    
    double** M = malloc(sizeof(double*) * len);

    for (int i = 0; i < len; i++){
        double* line = malloc(sizeof(double) * len);
        for (int j = 0; j < len; j++){
            line[j] = Me[i][j];   
        }
        M[i] = line;
    }

    for (int i = 0;i < len;i++){
        printf("\ndebut algo ligne %d\n", i + 1);
        printf("\nAvant changements\n");
        afficheMat(M, len);
    
        if(abs(M[i][i]-1) > 1e-12){
            printf("Debut algo normalisation\n");
            if(abs(M[i][i]) > 1e-12){
                normalize_line(M, len, i);
            }
            else if (i == len - 1){
                printf("retourne false, ligne de 0 en %d\n", i + 1);
                printf("\n****Fin test matrice****\n\n");
                return false;
            }
            else {
                int n = i + 1;
                while((n < len) && (abs(M[n][i]) < 1e-12)){
                    n++;
                }
                // on a n = len ou M[n][i] != 0
                if(n == len){
                    printf("retourne false, colonne de 0 en %d\n", i + 1);
                    printf("\n****Fin test matrice****\n\n");
                    return false;
                }
                // on a alors n < len et M[n][i] != 0
                // on peut donc permuter la ligne i avec la ligne n
                permuter_line(M, len, i, n);
                
                printf("Apres permutation\n");
                afficheMat(M, len);
                
                normalize_line(M, len, i);
            }
            
            printf("Fin algo normalisation\n");
        }
        printf("\nApres normalisation\n");
        afficheMat(M, len);
        // la ligne i est normalisée (M[i][i] = 1) 
        if(i == 0){
            traiter_ligne(M, len, 1, len, i);
        }
        else if(i == len - 1){
            traiter_ligne(M, len, 0, len - 1, i);
        }
        else{
            traiter_ligne(M, len, 0, i, i);
            traiter_ligne(M, len, i+1, len, i);
        }
        
        printf("\nApres traitements ligne %d\n", i + 1);
        afficheMat(M, len);
        
        printf("\t******\n\n");

    }
    
    printf("\nFinal :\n");
    afficheMat(M, len);
    
    freeMat(M, len);
    
    printf("\n****Fin test matrice****\n\n");
    return true;

}

int main(void){
    
    const double Val[4][4] = {
        { 0.0, 0.0, 0.0, 1.0},
        { 6.0, 0.0, 2.0, 4.0},
        { 0.0, 7.0, 1.0, 3.0},
        { 3.0, 0.0, 5.0, 8.7}
    };


    const double** M = malloc(sizeof(double*) * 4);
    
    for(int i = 0; i < 4; i++) {
        double* line = malloc(sizeof(double) * 4);
        for(int j = 0; j < 4; j++) {
            line[j] = Val[i][j];
        }
        M[i] = (const double*)line;
    }
    
    
    

    bool test = testMatrice(M, 4);

    if (test){
        printf("invesible\n");
    }
    else {
        printf(" tg \n");
    }
    
    freeMat(M, 4);

    return 0; 
}
