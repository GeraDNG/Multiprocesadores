/*------------------------------------------------------------------------------

*

* Multiprocesadores: Proyecto final.

* Fecha: 01 de diciembre del 2019.

* Autor: Gerardo Daniel Naranjo Gallegos, A01209499.

* Implementación: TBB.

*

*-----------------------------------------------------------------------------*/


// ---------------------------------------------------------------------------//
//																LIBRERÍAS																		//
// ---------------------------------------------------------------------------//

#include <iostream>
#include <tbb/task_scheduler_init.h>
#include <tbb/parallel_for.h>
#include <tbb/blocked_range.h>
#include "utils/cppheader.h"

// ---------------------------------------------------------------------------//
//															DEFINIR NAMESPACE															//
// ---------------------------------------------------------------------------//

using namespace std;
using namespace tbb;

// ---------------------------------------------------------------------------//
//										DEFINIR VARIABLES QUE NO CAMBIAN												//
// ---------------------------------------------------------------------------//

const int SIZE = 100000000;
const int GRAIN = 10000;

// ---------------------------------------------------------------------------//
//																FUNCIÓN																		  //
// ---------------------------------------------------------------------------//

class calculate_vectors {
private:
	int *vector1, *vector2, *suma, *resta;

public:
	calculate_vectors(int *arrayD, int *arrayC, int *arrayA, int *arrayB)
		: resta(arrayD), suma(arrayC), vector1(arrayA), vector2(arrayB) {}

	void operator() (const blocked_range<int> &r) const {
		for (int i = r.begin(); i != r.end(); i++) {
			suma[i] = vector1[i] + vector2[i];
			resta[i] = vector1[i] - vector2[i];
		}
	}
};

// ---------------------------------------------------------------------------//
//																	MAIN																			//
// ---------------------------------------------------------------------------//

int main(int argc, char const *argv[]) {
	// Definir variables a utilizar:
	Timer t;
	double ms = 0.0;

	// Inicializar variables:
	int *vector1 = new int[SIZE];
	int *vector2 = new int[SIZE];
	int *suma = new int[SIZE];
	int *resta = new int[SIZE];

	// Rellenar vectores utilizados:
	random_array(vector1, SIZE);
	fill_array(vector2, SIZE);

	// Mostrar ambos vectores:
	display_array("vector1", vector1);
	display_array("vector2", vector2);

	// Imprimir mensaje de inicio:
	cout << "Iniciando..." << endl;

	// Método FOR para ejecutar la parte en paralelo:
	for (int i = 0; i < N; i++) {
		t.start();
		parallel_for(blocked_range<int>(0, SIZE, GRAIN),
		  calculate_vectors(resta, suma, vector1, vector2));
		ms += t.stop();
	}

	// Imprimir/Mostrar en la terminal los vectores resultantes:
	display_array("suma", suma);
	display_array("resta", resta);

	// Imprimir/Mostrar en terminal el tiempo de ejecución del programa:
	cout << "Tiempo de ejecución = " << (ms/N) << " ms" << endl;

	// Liberar la memoria utilizada por las variables:
	delete [] vector1;
	delete [] vector2;
	delete [] suma;
	delete [] resta;

	// Fin del programa:
	return 0;
}
