/*----------------------------------------------------------------

*

* Multiprocesadores: Threads en Java.

* Fecha: 9-Sep-2015

* Autores: A01209499 GERARDO DANIEL NARANJO GALLEGOS
           A01205336 CESAR EDUARDO GUERRERO ALBORES

*

*----------------------------------------------------------*/
//import Utils;

public class Actividad01  {

	public Actividad01() {}

		public int concurrentSum(int Size)
		{
			int result=0;
			int sum;
			int a[] = new int[Size];
			Utils.fillArray(a);
			for(int i=0;i<Size;i++)
			{
				sum = 0;
				for(int j=i; j<Size;j++)
				{
					sum+=a[j];
					if(result < sum)
					{
						result = sum;
					}
				}
			}
			return result;

		}


	public void run() {
	}

	public static void main(String args[]) {
		final int SIZE = 10_000_000;
		long startTime, stopTime;
		double acum = 0;
		int c;



		acum = 0;
			Actividad01 exem = new Actividad01();

			startTime = System.currentTimeMillis();
			c= exem.concurrentSum(SIZE);
			stopTime = System.currentTimeMillis();
			acum +=  (stopTime - startTime);


		System.out.printf("Max sum = "+c+ "\n");
		System.out.printf("avg time = %.5f\n", (acum));
	}

}
