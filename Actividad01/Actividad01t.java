/*----------------------------------------------------------------

*

* Multiprocesadores: Threads en Java.

* Fecha: 9-Sep-2015

* Autores: A01209499 GERARDO DANIEL NARANJO GALLEGOS
           A01205336 CESAR EDUARDO GUERRERO ALBORES

*

*----------------------------------------------------------*/

public class Actividad01t extends Thread {
	
	private int a[],result, start, end; ;
	private int sum;

	public Actividad01t(int a[], int start, int end) 
	{
			this.result = 0;
			this.a = a;
			this.start = start;
			this.end = end;
	}
	
	public int getResult() 
	{
		return result;
	}


	public void run() 
	{

			for(int i=start;i<end;i++)
			{
				sum = 0;
				for(int j=i; j<end;j++)
				{
					sum+=a[j];
					if(result < sum)
					{
						result = sum;
					}
				}
			}
	}

	public static void main(String args[]) {
		final int SIZE = 10_000_000;
		long startTime, stopTime;
		double acum = 0;
		int c, cAnt;
		int block;
		Actividad01t threads[];
		
		block = SIZE / Utils.MAXTHREADS;
		threads = new Actividad01t[Utils.MAXTHREADS];
		
		int a[] = new int[SIZE];
		Utils.fillArray(a);
		
		for (int i = 0; i < threads.length; i++) 
		{
			if( i != threads.length-1)
			{
				threads[i] = new Actividad01t(a, (i * block), ((i + 1) * block));
			}
			else 
			{
				threads[i] = new Actividad01t(a, (i * block), SIZE);
			}
			
		}
		
		startTime = System.currentTimeMillis();
		for(int i = 0; i < threads.length; i++)
		{
			threads[i].start();
		}
		for (int i = 0; i < threads.length; i++) 
		{
			try 
			{
				threads[i].join();
			} 
			catch (InterruptedException e) 
			{
				e.printStackTrace();
			}
		}
		stopTime = System.currentTimeMillis();
		acum +=  (stopTime - startTime);
		c= threads[0].getResult();
		cAnt = 0 ;
		for (int i = 1; i < threads.length; i++) 
		{
			c= threads[i].getResult();
			cAnt = threads[i-1].getResult();
			if(c < cAnt)
			{
				c =cAnt;
			}				
		}

		System.out.printf("Max sum = "+c);
		System.out.printf("avg time = %.5f\n", (acum / Utils.N));
	}

}
