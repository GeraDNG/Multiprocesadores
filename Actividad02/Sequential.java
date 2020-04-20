/*----------------------------------------------------------------

*

* Multiprocesadores: Actividad 02. Sequential

* Fecha: 26-Sep-2019

* Autores: A01209499 Gerardo Naranjo
           A01209351 Iván Ochoa

*

*--------------------------------------------------------------*/

public class Sequential {
	// Declaración de variables:
	private static final int filas = 10_000;
	private static final int columnas = 1_000;
	private int matriz[][] = new int[filas][columnas];
  private int vector[] = new int[filas];
	private int resultado[] = new int[filas];

	// Método de inicialización:
	public Sequential(int matriz[][], int vector[]) {
		this.matriz = matriz;
    this.vector = vector;
	}

	// Método para obtener el resultado:
	public int[] getResult() {
		return resultado;
	}

	// Método para hacer el cálculo, multiplicar matriz por vector:
	public void calculate() {
		for (int i = 0; i < matriz.length; i++) {
      resultado[i] = 0;
			for (int j = 0; j < matriz[0].length; j++) {
        resultado[i] += vector[j] * matriz[i][j];
      }
		}
	}

	// Método MAIN:
	public static void main(String args[]) {
		// Declaración de variables:
		int matriz[][] = new int[filas][columnas];
    int vector[] = new int[filas];
		long startTime, stopTime;
		double acum = 0;

		// Iniciar (llenar) las variables:
    for (int i = 0; i < matriz.length; i++ ) {
      Utils.randomArray(matriz[i]);
    }
    Utils.randomArray(vector);

		/*
		// Procesos para debuggeo, para imprimir contenido de matriz y vector
		for (int i = 0; i < filas; i++ ) {
		    Utils.displayArray("matriz", matriz[0]);
    }
    Utils.displayArray("vector", vector);
		*/

		Sequential e = new Sequential(matriz, vector);
		acum = 0;
		for (int i = 0; i < Utils.N; i++) {
			startTime = System.currentTimeMillis();
			e.calculate();
			stopTime = System.currentTimeMillis();
			acum += (stopTime - startTime);
		}

		// Mostrar en pantalla el resultado y el tiempo:
    Utils.displayArray("resultado", e.getResult());
    System.out.printf("avg time = %.5f\n", (acum / Utils.N));
	}
}
