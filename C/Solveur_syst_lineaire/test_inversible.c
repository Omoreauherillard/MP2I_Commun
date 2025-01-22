#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>



void normalize_line(double** M, int len, int line){
    double facteur = 1/(M[line][line]);
    for(int k = line; k < len; k++){
        M[line][k] *= facteur; 
    }
}

void permuter_line(double** M, int len, int l1, int l2){

    double tempol2[len]; 
    for (int col = 0; col < len; col++){
        tempol2[col] = M[l2][col];
        M[l2][col] = M[l1][col];
        M[l1][col] = tempol2[col];                 
    }

}

void traiter_ligne(double** M, int len, int start, int stop, int diag){
    for(int l = start; l < stop ; l++){
        double factor  = M[l][diag];
        if(factor == 0){
            continue;
        }
        for(int col = diag; col < stop ; col++){
            M[l][col] -= factor * M[diag][col];
        }
    }
}



void freeMat(double** Mat, int len) {
    for(int i = 0; i < len; i++) {
        free(Mat[i]);
    }
    free(Mat);
}





bool testMatrice(const double** Me, int len){
    
    printf("%lf\n", Me[0][0]);

    double** M = malloc(sizeof(double*) * len);

    for (int i = 0; i < len; i++){
        double* line = malloc(sizeof(double) * len);
        for (int j = 0; j < len; j++){
            line[j] = Me[i][j];   
        }
        M[i] = line;
    }

    for (int i = 0;i < len;i++){
        if(M[i][i] != 1){
            if(M[i][i] != 0){
                normalize_line(M, len, i);
                break;
            }
            else if (i == len){
                return false;
            }
            int n = i + 1;
            while(n < len + 1 && M[n][i] == 0){
                n++;
            }
            if(n == len + 1){
                return false;
            }
            permuter_line(M, len, i, n);
            normalize_line(M, len, i);
            break;
        }
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

    }
    
    freeMat(M, len);
    return true;

}

int main(void){
    
    printf("Hello world !\n");
    
    const double Val[4][4] = {
        { 0.0, 0.0, 0.0, 0.0},
        { 1.0, 0.0, 2.0, 4.0},
        { 0.0, 2.0, 1.0, 3.0},
        { 3.0, 6.0, 5.0, 0.0}
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
