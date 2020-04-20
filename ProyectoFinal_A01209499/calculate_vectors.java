/*------------------------------------------------------------------------------

*

* Multiprocesadores: Proyecto final.

* Fecha: 01 de diciembre del 2019.

* Autor: Gerardo Daniel Naranjo Gallegos, A01209499.

* Implementación: JAVA.

*

*-----------------------------------------------------------------------------*/

// ---------------------------------------------------------------------------//
//																FUNCIÓN																		  //
// ---------------------------------------------------------------------------//


public class calculate_vectors {
	private int vector1[], vector2[], suma[], resta[];

	public calculate_vectors(int resta[], int suma[], int vector1[], int vector2[]) {
		this.resta = resta;
		this.suma = suma;
		this.vector1 = vector1;
		this.vector2 = vector2;
	}

	public void calculate() {
		for (int i = 0; i < suma.length; i++) {
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
		long startTime = 0;
		long stopTime = 0;
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

		// Llamada a la función:
		calculate_vectors e = new calculate_vectors(resta, suma, vector1, vector2);

		// Método FOR para ejecutar la función:
		for (int i = 0; i < Utils.N; i++) {
			startTime = System.currentTimeMillis();
			e.calculate();
			stopTime = System.currentTimeMillis();
			acum += (stopTime - startTime);
		}

		// Imprimir/Mostrar en la terminal los vectores resultantes:
		Utils.displayArray("suma", suma);
		Utils.displayArray("resta", resta);

		// Imprimir/Mostrar en terminal el tiempo de ejecución del programa:
		System.out.printf("Tiempo de ejecución = %.5f", (acum / Utils.N));
		System.out.printf(" ms \n");
	}
}
