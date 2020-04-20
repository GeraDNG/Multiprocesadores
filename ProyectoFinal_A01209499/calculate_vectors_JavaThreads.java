/*------------------------------------------------------------------------------

*

* Multiprocesadores: Proyecto final.

* Fecha: 01 de diciembre del 2019.

* Autor: Gerardo Daniel Naranjo Gallegos, A01209499.

* Implementación: THREADS.

*

*-----------------------------------------------------------------------------*/


// ---------------------------------------------------------------------------//
//																FUNCIÓN																		  //
// ---------------------------------------------------------------------------//

public class calculate_vectors_JavaThreads extends Thread {
	private int vector1[], vector2[], suma[], resta[], inicio, fin;

	public calculate_vectors_JavaThreads(int resta[], int suma[], int vector1[], int vector2[], int inicio, int fin) {
		this.vector1 = vector1;
		this.vector2 = vector2;
		this.suma = suma;
		this.resta = resta;
		this.inicio = inicio;
		this.fin = fin;
	}

	public void run() {
		for (int i = inicio; i < fin; i++) {
			suma[i] = vector1[i] + vector2[i];
			resta[i] = vector1[i] - vector2[i];
		}
	}

// ---------------------------------------------------------------------------//
//																	MAIN																			//
// ---------------------------------------------------------------------------//

	public static void main(String args[]) {
		// Definir variables a utilizar:
		final int SIZE = 100_000_000;
		calculate_vectors_JavaThreads threads[];
		int block;
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

		// Asignación del tamaño del bloque, según el número de threads disponibles en el dispositivo:
		block = SIZE / Utils.MAXTHREADS;
		threads = new calculate_vectors_JavaThreads[Utils.MAXTHREADS];

		// Método FOR para ejecutar la parte en paralelo:
		for (int j = 1; j <= Utils.N; j++) {
			for (int m = 0; m < threads.length; m++) {
				if (m != threads.length - 1) {
					threads[m] = new calculate_vectors_JavaThreads(resta, suma, vector1, vector2, (m * block), ((m + 1) * block));
				} else {
					threads[m] = new calculate_vectors_JavaThreads(resta, suma, vector1, vector2, (m * block), Utils.N);
				}
			}

			inicioTiempo = System.currentTimeMillis();
			for (int k = 0; k < threads.length; k++) {
				threads[k].start();
			}
			for (int l = 0; l < threads.length; l++) {
				try {
					threads[l].join();
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
			finTiempo = System.currentTimeMillis();
			acum +=  (finTiempo - inicioTiempo);
		}

		// Imprimir/Mostrar en la terminal los vectores resultantes:
		Utils.displayArray("suma", suma);
		Utils.displayArray("resta", resta);

		// Imprimir/Mostrar en terminal el tiempo de ejecución del programa :
		System.out.printf("Tiempo de ejecución = %.5f ms \n", (acum / Utils.N));
	}
}
