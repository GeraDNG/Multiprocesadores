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

int main (int argc, char* argv[]) {

  int resultado[SIZE][SIZE];
  int matriz[SIZE][SIZE] = {{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                            { 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 },
                            { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
                            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                            { 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 },
                            { 0, 0, 1, 1, 0, 0, 0, 0, 0, 0 },
                            { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
                            { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
                            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }};

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

  std::cout << "matriz:" << '\n';
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      std::cout << matriz[i][j];
    }
    std::cout << '\n';
  }
  std::cout << "resultado:" << '\n';
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      std::cout << resultado[i][j];
    }
    std::cout << '\n';
  }

  return 0;
}
