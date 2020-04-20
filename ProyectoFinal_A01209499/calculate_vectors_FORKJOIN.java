/*------------------------------------------------------------------------------

*

* Multiprocesadores: Proyecto final.

* Fecha: 01 de diciembre del 2019.

* Autor: Gerardo Daniel Naranjo Gallegos, A01209499.

* Implementación: FORK/JOIN.

*

*-----------------------------------------------------------------------------*/


// ---------------------------------------------------------------------------//
//																LIBRERÍAS																		//
// ---------------------------------------------------------------------------//

import java.util.concurrent.RecursiveAction;
import java.util.concurrent.ForkJoinPool;

// ---------------------------------------------------------------------------//
//																FUNCIÓN																		  //
// ---------------------------------------------------------------------------//

public class calculate_vectors_FORKJOIN extends RecursiveAction {
	// Variables que no cambian:
	private static final int SIZE = 100_000_000;
	private static final int MIN = 100_000;

	private int vector1[], vector2[], suma[], resta[], inicio, fin;

	public calculate_vectors_FORKJOIN(int inicio, int fin,int resta[], int suma[], int vector1[], int vector2[]) {
		this.inicio = inicio;
		this.fin = fin;
		this.resta = resta;
		this.suma = suma;
		this.vector1 = vector1;
		this.vector2 = vector2;
	}

	protected void computeDirectly() {
		for (int i = inicio; i < fin; i++) {
			suma[i] = vector1[i] + vector2[i];
			resta[i] = vector1[i] - vector2[i];
		}
	}

	@Override
	protected void compute() {
		if ( (fin - inicio) <= MIN ) {
			computeDirectly();
		} else {
			int mitad = inicio + ( (fin - inicio) / 2 );
			invokeAll(
				new calculate_vectors_FORKJOIN(inicio, mitad, resta, suma, vector1, vector2),
				new calculate_vectors_FORKJOIN(mitad, fin, resta, suma, vector1, vector2)
			);
		}
	}

// ---------------------------------------------------------------------------//
//																	MAIN																			//
// ---------------------------------------------------------------------------//

	public static void main(String args[]) {
		// Definir variables a utilizar:
		ForkJoinPool pool;
		long inicioTiempo, finTiempo;
		double acum = 0.0;

		// Inicializar variables:
		int vector1[] = new int[SIZE];
		int vector2[] = new int[SIZE];
		int suma[] = new int[SIZE];
		int resta[] = new int[SIZE];

		// Rellenar vectores utilizados:
		Utils.randomArray(vector1);
		Utils.fillArray(vector2);

		// Mostrar ambos vectores:
		Utils.displayArray("vector1", vector1);
		Utils.displayArray("vector2", vector2);

		// Método FOR para ejecutar la parte en paralelo:
		for (int j = 0; j < Utils.N; j++) {
			inicioTiempo = System.currentTimeMillis();
			pool = new ForkJoinPool(Utils.MAXTHREADS);
			pool.invoke(new calculate_vectors_FORKJOIN(0, Utils.N, resta, suma, vector1, vector2));
			finTiempo = System.currentTimeMillis();
			acum += (finTiempo - inicioTiempo);
		}

		// Imprimir/Mostrar en la terminal los vectores resultantes:
		Utils.displayArray("suma", suma);
		Utils.displayArray("resta", resta);

		// Imprimir/Mostrar en terminal el tiempo de ejecución del programa :
		System.out.printf("Tiempo de ejecución = %.5f ms \n", (acum / Utils.N));
	}
}
