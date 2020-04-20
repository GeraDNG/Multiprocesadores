/*----------------------------------------------------------------

*

* Multiprocesadores: OpenMP

* Fecha: 2-Sep-2015

* Autor: A01209499, Gerardo Naranjo
         A01209351, Iván Ochoa

*

*--------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include "cheader.h"

#define  COLUMS 10000
#define  ROWS 1000

void multi_vector_matrix(int *vector,int *result, int **matrix){

    int i,j;
    for (i = 0; i < ROWS ; i++){
        int acum = 0;
        #pragma omp prallel for shared(vector, matrix, i) reduction(+:acum)
        for( j = 0; j < COLUMS;j++){
            acum += vector[j] * matrix[i][j];
        }
        result[i] = acum;
    }
}

int main(int argc, char* argv[]){

    int i,*result,*vector, **matrix;
    double ms;

    vector = (int *) malloc(sizeof(int) * COLUMS);
    result = (int *) malloc(sizeof(int) * COLUMS);
    matrix = (int **) malloc(sizeof(int *) * ROWS); 
    for(i = 0; i < ROWS; i++){
        matrix[i] = (int *)malloc(sizeof(int) * COLUMS);
    }

    fill_array(vector, COLUMS);
    for (i = 0; i < ROWS; i++)
    {
        fill_array(matrix[i],COLUMS);
    }

    printf("starting ... \n");
    ms = 0.0;

    start_timer();
    multi_vector_matrix(vector,result,matrix);

    ms = stop_timer();

    display_array("resultado",result);

    printf("avg time = %.5lf ms\n", (ms));



    free(vector);
    free(result);
    for (i = 0; i < ROWS; i++)
    {
        free(matrix[i]);
    }
    free(matrix);

}
