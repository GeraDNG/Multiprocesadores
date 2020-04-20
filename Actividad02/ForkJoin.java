/*----------------------------------------------------------------

*

* Multiprocesadores: Actividad 02. Fork Join

* Fecha: 26-Sep-2019

* Autores: A01209499 Gerardo Naranjo
           A01209351 Iván Ochoa

*

*--------------------------------------------------------------*/

// Importar librerías necesarias (también se requiere Utils):
import java.util.concurrent.RecursiveAction;
import java.util.concurrent.ForkJoinPool;

public class ForkJoin extends RecursiveAction {
	// Declaración de variables:
	private static final int filas = 10_000;
	private static final int columnas = 1_000;
	private int matriz[][] = new int[filas][columnas];
	private int vector[] = new int[filas];
	private int resultado[] = new int[filas];
	private int start, end;

	// Método de inicialización:
	public ForkJoin(int start, int end, int resultado[], int matriz[][], int vector[]) {
		this.start= start;
		this.end = end;
		this.resultado = resultado;
		this.matriz = matriz;
		this.vector = vector;
	}

	// Método para hacer el cálculo, multiplicar matriz por vector, lo que se va a replicar:
	protected void computeDirectly() {
		for ( int i = start; i < end; i++ ) {
			int auxiliar = 0;
			for ( int j = 0; j < matriz[0].length; j++ ) {
				auxiliar += matriz[i][j] * vector[j];
			}
			resultado[i] = auxiliar;
		}
	}

	// Método para determinar tipo de cálculo (directo o multiples):
	@Override
	protected void compute() {
		if ( (end - start) <= columnas ) {
			computeDirectly();
		} else {
			int mid = start + ( (end - start) / 2 );
			invokeAll(
				new ForkJoin(start, mid, resultado, matriz, vector),
				new ForkJoin(mid, end, resultado, matriz, vector)
			);
		}
	}

	// Método MAIN:
	public static void main(String args[]) {
		// Declaración de variables:
		ForkJoinPool pool;
		long startTime, stopTime;
		double acum = 0;

		// Iniciar las variables (llenar con número aleatorios):
		int matriz[][] = new int [filas][columnas];
		for (int i = 0; i < matriz.length; i++ ) {
			Utils.randomArray(matriz[i]);
		}
		int vector[] = new int [filas];
		Utils.randomArray(vector);
		int resultado[] = new int [filas];

		acum = 0;
		for (int i = 0; i < Utils.N; i++) {
			startTime = System.currentTimeMillis();
			pool = new ForkJoinPool(Utils.MAXTHREADS);
			pool.invoke(new ForkJoin(0, filas, resultado, matriz, vector));
			stopTime = System.currentTimeMillis();
			acum += (stopTime - startTime);
		}

		// Imprimir resultados:
		Utils.displayArray("resultado", resultado);
		System.out.printf("avg time = %.5f\n", (acum / Utils.N));
	}
}
