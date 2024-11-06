#ifndef PROBABILIDADES_HPP
#define PROBABILIDADES_HPP

#include <iostream>
#include <vector>
#include <iomanip>


const int SIZE = 10;

extern int tablero[SIZE][SIZE];          // Tablero global
extern int probabilidades[SIZE][SIZE];   // Matriz de probabilidades

void calcularProbabilidades(int tablero[SIZE][SIZE], int probabilidades[SIZE][SIZE], int longitudBarco);
void mostrarHeatMapEscalado(int probabilidades[SIZE][SIZE]);

#endif // PROBABILIDADES_HPP
