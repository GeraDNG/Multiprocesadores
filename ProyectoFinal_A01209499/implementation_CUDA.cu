/*------------------------------------------------------------------------------

*

* Multiprocesadores: Proyecto final.

* Fecha: 01 de diciembre del 2019.

* Autor: Gerardo Daniel Naranjo Gallegos, A01209499.

* Implementación: CUDA.

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

#define MIN(vector1,vector2) (vector1<vector2?vector1:vector2)
#define SIZE	100000000
#define THREADS	256
#define BLOCKS	MIN(32, (SIZE + THREADS - 1)/ THREADS)

// ---------------------------------------------------------------------------//
//																FUNCIÓN																		  //
// ---------------------------------------------------------------------------//

__global__ void calculate(int *resta, int *suma, int *vector1, int *vector2) {
	int i = threadIdx.x + (blockIdx.x * blockDim.x);
	if (i < SIZE) {
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
	int *device_vector1, *device_vector2, *device_suma, *device_resta;
	double ms = 0.0;

	// Inicializar variables:
	vector1 = (int *) malloc(sizeof(int) * SIZE);
	vector2 = (int *) malloc(sizeof(int) * SIZE);
	suma = (int *) malloc(sizeof(int) * SIZE);
	resta = (int *) malloc(sizeof(int) * SIZE);

	// Rellenar vectores utilizados:
	random_array(vector1, SIZE);
	fill_array(vector2, SIZE);

	// Mostrar ambos vectores:
	display_array("a", vector1);
	display_array("b", vector2);

	// Asignar memoria a las variables en el dispositivo (GPU):
	cudaMalloc((void**) &device_vector1, SIZE * sizeof(int));
	cudaMalloc((void**) &device_vector2, SIZE * sizeof(int));
	cudaMalloc((void**) &device_suma, SIZE * sizeof(int));
	cudaMalloc((void**) &device_resta, SIZE * sizeof(int));

	// Copiar vectores a vectores en el dispositivo (GPU):
	cudaMemcpy(device_vector1, vector1, SIZE * sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(device_vector2, vector2, SIZE * sizeof(int), cudaMemcpyHostToDevice);

	// Imprimir mensaje de inicio:
	printf("Iniciando...\n");

	// Método FOR para ejecutar la parte en paralelo en la GPU:
	for (int j = 0; j < N; j++) {
		start_timer();
		calculate<<<BLOCKS, THREADS>>>(device_resta, device_suma, device_vector1, device_vector2);
		ms += stop_timer();
	}

	// Copiar vectores resultantes del GPU al CPU:
	cudaMemcpy(suma, device_suma, SIZE * sizeof(int), cudaMemcpyDeviceToHost);
	cudaMemcpy(resta, device_resta, SIZE * sizeof(int), cudaMemcpyDeviceToHost);

	// Imprimir/Mostrar en la terminal los vectores resultantes:
	display_array("c", suma);
	display_array("d", resta);

	// Imprimir/Mostrar en terminal el tiempo de ejecución del programa:
	printf("Tiempo de ejecución = %.5lf ms\n", (ms / N));

	// Liberar la memoria utilizada en el GPU por las variables:
	cudaFree(device_vector1);
	cudaFree(device_vector2);
	cudaFree(device_suma);
	cudaFree(device_resta);

	// Liberar la memoria del CPU utilizada por las variables:
	free(vector1);
	free(vector2);
	free(suma);
	free(resta);

	// Fin del programa:
	return 0;
}
