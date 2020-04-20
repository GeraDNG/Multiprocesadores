/*
----------------------------------------------------------------

* Multiprocesadores: Actividad 04, TBB

* Archivo: Solución secuencial

* Fecha: 17-Octubre-2019

* Autor: A01209499, Gerardo Daniel Naranjo Gallegos

--------------------------------------------------------------
*/

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "cppheader.h"

using namespace std;

const int SIZE = 10;

void rellenarMatrizCeros (int resultado[SIZE][SIZE]) {
  srand(time(NULL));
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      resultado[i][j] = 0;
    }
  }
}

void rellenarMatrizRandom (int matriz[SIZE][SIZE]) {
  srand(time(NULL));
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      matriz[i][j] = rand()%(2-0);
    }
  }
}

void gameOfLife (int matriz[SIZE][SIZE], int resultado[SIZE][SIZE]) {
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      // Calcular los vecinos vivos:
      int vecinosVivos = 0;
      for (int k = -1; k < 2; k++) {
        for (int l = -1; l < 2; l++) {
          vecinosVivos += matriz[i+k][j+l];
        }
      }
      vecinosVivos -= matriz[i][j];
      // Condiciones para la futura generación:
      if (matriz[i][j] == 1) {
        if (vecinosVivos == 2 || vecinosVivos == 3) {
          resultado[i][j] = 1;
        }
        else {
          resultado[i][j] = 0;
        }
      }
      else {
        if (vecinosVivos == 3) {
          resultado[i][j] = 1;
        }
        else {
          resultado[i][j] = matriz[i][j];
        }
      }
    }
  }
}

void imprimirMatrices (int matriz[SIZE][SIZE], int resultado[SIZE][SIZE]) {
  std::cout << "matriz:" << '\n';
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      std::cout << matriz[i][j];
    }
    std::cout << '\n';
  }
  std::cout << '\n' << "resultado:" << '\n';
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      std::cout << resultado[i][j];
    }
    std::cout << '\n';
  }
}

void imprimirTiempo (double ms) {
  std::cout << '\n' << "avg time = " << ms << " ms" << '\n';
}

int main (int argc, char* argv[]) {

  double ms;
  Timer t;
  int resultado[SIZE][SIZE], matriz[SIZE][SIZE];

  rellenarMatrizCeros(resultado); // Rellena la matriz con ceros
  rellenarMatrizRandom(matriz);   // Rellena la matriz con números random entre 0 y 1

  t.start();
  gameOfLife(matriz, resultado);  // Aplica las reglas del juego de la vida a la matriz y regresa matriz resultante
  ms = t.stop();

  imprimirMatrices(matriz, resultado); // Imprime ambas matrices
  imprimirTiempo(ms);             // Imprime el tiempo de ejecución de GOF

  return 0;
}
