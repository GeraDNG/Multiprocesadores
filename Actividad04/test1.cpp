/*
----------------------------------------------------------------

* Multiprocesadores: TBB

* Fecha: 17-Octubre-2019

* Autor: A01209499, Gerardo Daniel Naranjo Gallegos

--------------------------------------------------------------
*/

#include <iostream>
#include <cmath>
#include "cppheader.h"

const int SIZE = 10;

using namespace std;

class GOL {
private:
	int *myMatriz, mySize;

public:
	GOL(int **matriz, int size) : myMatriz(matriz), mySize(size) {}

	void calculate() {
		int futuraGeneracion[10][10];
		for (int l = 0; l < 10; l++) {
			for (int m = 0; m < 10; m++) {
				//Find number of live neighbours:
				int aliveNeighbours = 0;
				for (int i = -1; i <= 1; i++) {
					for (int j = -1; j <= 1; j++) {
						aliveNeighbours += myMatriz[l+i, m+j];
					}
				}

				aliveNeighbours -= myMatriz[l, m];

				// Cell is lonely and dies
				if ((myMatriz[l,m] == 1) && (aliveNeighbours < 2))
        	futuraGeneracion[l,m] = 0;

        // Cell dies due to over population
        else if ((myMatriz[l,m] == 1) && (aliveNeighbours > 3))
          futuraGeneracion[l,m] = 0;

        // A new cell is born
        else if ((myMatriz[l,m] == 0) && (aliveNeighbours == 3))
        	futuraGeneracion[l,m] = 1;

        // Remains the same
        else
        	futuraGeneracion[l,m] = myMatriz[l,m];
			}
		}
	}
};

int main(int argc, char* argv[]) {
	double ms;
	Timer t;
	int **matriz;

	matriz = new int[SIZE][SIZE];
	matriz = {
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 },
            { 0, 0, 1, 1, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };

	ms = 0;
	GOL obj(matriz, SIZE);
	cout << "Starting..." << endl;
	for (int i = 0; i < N; i++) {
		t.start();
		obj.calculate();
		ms += t.stop();
	}
	//cout << "sum = " << obj.getResult() << endl;
	cout << "avg time = " << (ms / N) << " ms" << endl;

	delete [] matriz;
	return 0;
}
