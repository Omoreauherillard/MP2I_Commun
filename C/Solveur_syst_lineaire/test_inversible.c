#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


//double abs_d(

typedef struct squared_matrix_double {
    double** data;
    size_t length;
} sMat_d;

typedef struct matrix_double {
    double** data;
    size_t rows;
    size_t columns;
} Mat_d;


sMat_d* build_sMat_d(size_t len);
void free_sMat_d(sMat_d* mat);


Mat_d* build_Mat_d(size_t n, size_t m);
void freeMat_d(Mat_d* mat);
double** CopyMat_d(const Mat_d* mat);
void free_data(double** data, size_t rows, size_t cols);
double** Id_mat_d(int len);




void print_line_mat_d(double* line, int len);
//void afficheMat_d(const Mat_d* M);

double** get_data_sMat_d(sMat_d* matrix);





Mat_d* build_Mat_d(size_t n, size_t m) {
    Mat_d* M = malloc(sizeof(Mat_d));
    double** mat = malloc(sizeof(double*) * n);
    
    for(size_t i = 0; i < n; i++) {
        double* lines = malloc(sizeof(double) * m);
        mat[i] = lines;
    }
    
    M->data = mat;
    M->rows = n;
    M->columns = m;
    
    return M;
}

void freeMat_d(Mat_d* mat) {
    for(size_t i = 0; i < mat->rows; i++) {
        free((mat->data)[i]);
    }
    free(mat);
}

double** CopyMat_d(const Mat_d* M) {
    
    double** dest = malloc(sizeof(double*) * M->rows);

    for (size_t i = 0; i < M->rows; i++){
        double* line = malloc(sizeof(double) * M->columns);
        for (size_t j = 0; j < M->columns; j++){
            line[j] = (M->data)[i][j];   
        }
        dest[i] = line;
    }
    
    return dest;
}





void free_data(double** data, size_t rows, size_t cols) {
    for(size_t i = 0; i < rows; i++) {
        free(data[i]);
    }
    
    free(data);
}


double** Id_mat_d(int len) {
    double** Id = malloc(sizeof(double*) * len);
    
    for(size_t i = 0; i < len; i++){
        double* line = malloc(sizeof(double) * len);
        for(size_t j = 0; j < len; j++){
            line[j] = (i == j);
        }
        Id[i] = line;
    }
    
    return Id;
}




double** get_data_mat_d(Mat_d* matrix){
    double** dest = malloc(sizeof(double*) * matrix->rows);

    for (size_t i = 0; i < matrix->rows; i++){
        double* line = malloc(sizeof(double) * matrix->columns);
        for (size_t j = 0; j < matrix->columns; j++){
            line[j] = (matrix->data)[i][j];   
        }
        dest[i] = line;
    }
    
    return dest;
}




void print_line_d(double* line, int len) {
    printf("[ ");
    for(size_t i = 0; i < len; i++) {
        printf("%.3f ", line[i]);
    }
    printf("]");
}

void afficheMat_d(const Mat_d* M) {
    for(size_t i = 0; i < M->rows; i++)
    {
        print_line_d((M->data)[i], M->columns);
        printf("\n");
    }
    printf("\n");
}




void free_sMat_d(sMat_d* mat) {
    for(size_t i = 0; i < mat->length; i++) {
        free((mat->data)[i]);
    }
    
    free(mat->data);
    free(mat);
}



sMat_d* build_sMat_d(size_t len) {
    sMat_d* M = malloc(sizeof(sMat_d));
    
    M->length = len;
    
    double** mat = malloc(sizeof(double*) * len);
    
    for(size_t i = 0; i < len; i++) {
        double* line = malloc(sizeof(double) * len);
        mat[i] = line;
    }
    
    M->data = mat;
    
    return M;
}

void affiche_sMat_d(sMat_d* M) {
    for(size_t i = 0; i < M->length; i++)
    {
        print_line_d((M->data)[i], M->length);
        printf("\n");
    }
    printf("\n");
}






void normalize_line(Mat_d* M, int line){
    /*printf("\nligne %d avant normalisation\n", line + 1);
    print_line(M[line], len);*/

    double facteur = 1/((M->data)[line][line]);
    //printf("facteur : %.3f\n", facteur);
    
    for(size_t k = line; k < M->columns; k++){
        (M->data)[line][k] *= facteur; 
    }
    
    /*printf("\nligne %d normalisee\n", line + 1);
    print_line(M[line], len);
    printf("\n\n");*/
}

void permuter_line(Mat_d* M, int l1, int l2){

    double tempol2[M->columns]; 
    for (size_t col = 0; col < M->columns; col++){
        tempol2[col] = (M->data)[l2][col];
        (M->data)[l2][col] = (M->data)[l1][col];
        (M->data)[l1][col] = tempol2[col];                 
    }

    //printf("ligne %d permutee avec ligne %d\n", l1 + 1, l2 + 1);
}

void traiter_ligne(Mat_d* M, int start, int stop, int diag){
    
    //printf("\n**************\nTraitement des lignes de %d a %d\n", start + 1, stop);

    // on boucle sur chaque lignes
    for(size_t l = start; l < stop ; l++){
        double factor = (M->data)[l][diag];
        //printf("L%d <-- L%d - %.3f * L%d\n", l+1, l+1, factor, diag+1);
        if(factor == 0){
            //printf("factor 0, we pass\n");
            continue;
        }
        /*printf("Line %d before traitement:\n", l+1);
        print_line(M[l], len);*/
        
        for(size_t col = diag; col < M->columns ; col++){
            (M->data)[l][col] -= factor * (M->data)[diag][col];
        }
        
        /*printf("\n\nLine %d after traitement:\n", l+1);
        print_line(M[l], len);
        printf("\n\n");*/
    }
    //printf("Fin du traitement des lignes de %d a %d\n**************\n", start + 1, stop);
}




bool InverseMatrice(const sMat_d* Me){

    //printf("\n***** Test Matrice ****\n");
    
    const size_t len = Me->length;
    //////// Creating the matrix to work on
    
    // création d'une matrice systeme M pour effectuer les opérations dessus
    Mat_d* M = build_Mat_d(len, 2 * len);
    
    for(size_t i = 0; i < Me->length; i++) {
    
        // copy data
        for(size_t j = 0; j < Me->length; j++) {
            (M->data)[i][j] = (Me->data)[i][j];
        }
        
        // place identity matrix to the side
        for(size_t j = 0; j < Me->length; j++) {
            (M->data)[i][j + Me->length] = (i == j);
        }
    }
    
    
    /*printf("columns of M : %lld\n\n", M->columns);
    printf("rows of M : %lld\n\n", M->rows);*/
    
    /////// search for inverse
    for (size_t i = 0;i < len;i++){
        /*printf("\ndebut algo ligne %d\n", i + 1);
        printf("\nAvant changements\n");
        afficheMat_d(M);
    
        printf("Valeur testee : %.3f\n", abs((M->data)[i][i]));
        printf("a gauche %.3f\n", fabs((M->data)[i][i]-1));
        printf("result test : %d\n", fabs((M->data)[i][i]-1) > 1e-8);*/
        if(fabs((M->data)[i][i]-1) > 1e-8){
            //printf("Debut algo normalisation\n");
            if(fabs((M->data)[i][i]) > 1e-12){
                normalize_line(M, i);
                //printf("cas 1\n");
            }
            else if (i == len - 1){
                /*printf("retourne false, ligne de 0 en %d\n", i + 1);
                printf("\n****Fin test matrice****\n\n");*/
                //printf("Cas 2\n");
                freeMat_d(M);
                return false;
            }
            else {
                //printf("Cas 3\n");
                int n = i + 1;
                while((n < len) && (abs((M->data)[n][i]) < 1e-12)){
                    n++;
                }
                // on a n = len ou M[n][i] != 0
                if(n == len){
                    /*printf("retourne false, colonne de 0 en %d\n", i + 1);
                    printf("\n****Fin test matrice****\n\n");*/
                    freeMat_d(M);
                    return false;
                }
                // on a alors n < len et M[n][i] != 0
                // on peut donc permuter la ligne i avec la ligne n
                permuter_line(M, i, n);
                
                /*printf("Apres permutation\n");
                afficheMat_d(M);*/
                
                normalize_line(M, i);
            }
            
            //printf("Fin algo normalisation\n");
        }
        
        /*printf("\nApres normalisation\n");
        afficheMat_d(M);*/
        
        // la ligne i est normalisée (M[i][i] = 1) 
        if(i == 0){
            traiter_ligne(M, 1, len, i);
        }
        else if(i == len - 1){
            traiter_ligne(M, 0, len - 1, i);
        }
        else{
            traiter_ligne(M, 0, i, i);
            traiter_ligne(M, i+1, len, i);
        }
        
        /*printf("\nApres traitements ligne %d\n", i + 1);
        afficheMat_d(M);
        
        printf("\t******\n\n");*/

    }
    
    /*printf("\nFinal :\n");
    afficheMat_d(M);*/
    
    ////// we fetch the matrix's inverse from the big matrix M
    sMat_d* inverse = build_sMat_d(len);
    
    for(size_t i = 0; i < len; i++) {
        for(size_t j = len; j < 2*len; j++){
            (inverse->data)[i][j - len] = (M->data)[i][j];
        }
    }
    
    
    printf("\n\nInverse :\n");
    affiche_sMat_d(inverse);
    fflush(stdout);
    
    // we don't need M anymore
    freeMat_d(M);
    free_sMat_d(inverse);
    //printf("\n****Fin test matrice****\n\n");
    return true;

}

int main(void){
    
    const size_t len = 5;
    
    const double Val[len][len] = {
        { 0.0, 3.0, 0.0, 1.0, 8.5},
        { 6.0, 0.7, 2.6, 4.0, 71},
        { 0.01, 7.0, 1.0, 3.0, 92},
        { 3.0, 0.0, 5.0, 8.7, -52.8},
        { 4.0, 76, 54, -965, 0.7}
    };


    sMat_d* M = build_sMat_d(len);

    for(size_t i = 0; i < len; i++) {
        for(size_t j = 0; j < len; j++) {
            (M->data)[i][j] = Val[i][j];
        }
    }
    
    
    printf("Matrice :\n");
    affiche_sMat_d(M);

    bool test = InverseMatrice(M);

    if (test){
        printf("inversible\n");
    }
    else {
        printf("non inversible\n");
    }
    
    free_sMat_d(M);

    return 0; 
}