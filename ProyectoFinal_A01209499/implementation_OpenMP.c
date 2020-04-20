/*------------------------------------------------------------------------------

*

* Multiprocesadores: Proyecto final.

* Fecha: 01 de diciembre del 2019.

* Autor: Gerardo Daniel Naranjo Gallegos, A01209499.

* Implementación: OpenMP.

*

*-----------------------------------------------------------------------------*/


// ---------------------------------------------------------------------------//
//																LIBRERÍAS																		//
// ---------------------------------------------------------------------------//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils/cheader.h"

// ---------------------------------------------------------------------------//
//										DEFINIR VARIABLES QUE NO CAMBIAN												//
// ---------------------------------------------------------------------------//

#define SIZE 100000000

// ---------------------------------------------------------------------------//
//																FUNCIÓN																		  //
// ---------------------------------------------------------------------------//

void calculate_vectors(int *resta, int *suma, int *vector1, int *vector2, int size) {
	#pragma omp parallel for shared(resta, suma, vector1, vector2, size)
	for (int i = 0; i < size; i++) {
		suma[i] = vector1[i] + vector2[i];
		resta[i] = vector1[i] - vector2[i];
	}
}

// ---------------------------------------------------------------------------//
//																	MAIN																			//
// ---------------------------------------------------------------------------//

int main(int argc, char const *argv[]) {
	// Definir variables a utilizar:
	int *vector1, *vector2, *suma, *resta;
	double ms = 0.0, result = 0.0;

	// Inicializar variables:
	vector1 = (int *) malloc(sizeof(int) * SIZE);
	vector2 = (int *) malloc(sizeof(int) * SIZE);
	suma = (int *) malloc(sizeof(int) * SIZE);
	resta = (int *) malloc(sizeof(int) * SIZE);

	// Rellenar vectores utilizados:
	random_array(vector1, SIZE);
	fill_array(vector2, SIZE);

	// Mostrar ambos vectores:
	display_array("vector1", vector1);
	display_array("vector2", vector2);

	// Imprimir mensaje de inicio:
	printf("Iniciando...\n");

	// Método FOR para ejecutar la parte en paralelo:
	for (int j = 0; j < N; j++) {
		start_timer();
		calculate_vectors(resta, suma, vector1, vector2, SIZE);
		ms += stop_timer();
	}

	// Imprimir/Mostrar en la terminal los vectores resultantes:
	display_array("suma", suma);
	display_array("resta", resta);

	// Imprimir/Mostrar en terminal el tiempo de ejecución del programa:
	printf("Tiempo de ejecución = %.5lf ms\n", (ms / N));

	// Liberar la memoria utilizada por las variables:
	free(vector1);
	free(vector2);
	free(suma);
	free(resta);

	// Fin del programa:
	return 0;
}
