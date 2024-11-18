#include "engineCore.hpp"
#define HIT_BONUS 12
#define BORDE_BONUS 4

#include <tuple>

using namespace std;

void calcularProbabilidades(int tablero[SIZE][SIZE], int probabilidades[SIZE][SIZE], vector<int> vectorLon) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (i == SIZE - 1 || j == SIZE - 1 || i == 0 || j == 0) {
                probabilidades[i][j] += BORDE_BONUS;
            }

            if (tablero[i][j] == 3) {
                if (i + 1 < SIZE && tablero[i + 1][j] == 0) {
                    probabilidades[i + 1][j] += HIT_BONUS;
                }
                if (i - 1 >= 0 && tablero[i - 1][j] == 0) {
                    probabilidades[i - 1][j] += HIT_BONUS;
                }
                if (j + 1 < SIZE && tablero[i][j + 1] == 0) {
                    probabilidades[i][j + 1] += HIT_BONUS;
                }
                if (j - 1 >= 0 && tablero[i][j - 1] == 0) {
                    probabilidades[i][j - 1] += HIT_BONUS;
                }
            }
        }
    }

    for (const int &longitudBarco : vectorLon) {
        // Horizontalmente: verificamos celdas libres en cada fila
        for (int i = 0; i < SIZE; ++i) {
            int celdasLibres = 0;

            // Primer barrido para acumulación de celdas libres
            for (int j = 0; j < SIZE; ++j) {
                if (tablero[i][j] == 0) {  // Celda no disparada
                    ++celdasLibres;
                } else {
                    celdasLibres = 0;  // Reseteamos si hay un disparo
                }

                // Si tenemos suficientes celdas libres para el barco
                if (celdasLibres >= longitudBarco) {
                    // Incrementamos el rango actual para todas las celdas posibles
                    for (int k = j - longitudBarco + 1; k <= j; ++k) {
                        // Verificamos que la celda no haya sido disparada
                        if (k >= 0 && k < SIZE && tablero[i][k] == 0) {
                            probabilidades[i][k]++;
                        }
                    }
                }
            }
        }

        // Verticalmente: verificamos celdas libres en cada columna
        for (int j = 0; j < SIZE; ++j) {
            int celdasLibres = 0;

            // Primer barrido para acumulación de celdas libres
            for (int i = 0; i < SIZE; ++i) {
                if (tablero[i][j] == 0) {  // Celda no disparada
                    ++celdasLibres;
                } else {
                    celdasLibres = 0;  // Reseteamos si hay un disparo
                }

                // Si tenemos suficientes celdas libres para el barco
                if (celdasLibres >= longitudBarco) {
                    // Incrementamos el rango actual para todas las celdas posibles
                    for (int k = i - longitudBarco + 1; k <= i; ++k) {
                        // Verificamos que la celda no haya sido disparada
                        if (k >= 0 && k < SIZE && tablero[i][k] == 0) {
                            probabilidades[k][j]++;
                        }
                    }
                }
            }
        }
    }
}

void encontrarMinMax(int probabilidades[SIZE][SIZE], int &minVal, int &maxVal) {
    minVal = probabilidades[0][0];
    maxVal = probabilidades[0][0];
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            minVal = std::min(minVal, probabilidades[i][j]);
            maxVal = std::max(maxVal, probabilidades[i][j]);
        }
    }
}

// Función para mostrar el "heat map" con escalado de colores ANSI
void mostrarHeatMapEscalado(int probabilidades[SIZE][SIZE]) {
    int minVal, maxVal;
    encontrarMinMax(probabilidades, minVal, maxVal);
    int rango = maxVal - minVal;

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            int valor = probabilidades[i][j];
            int escala;

            // Normalizamos el valor en el rango de 0 a 4 para los colores
            if (rango > 0) {
                escala = (valor - minVal) * 4 / rango;
            } else {
                escala = 0;  // En caso de que el rango sea cero, todo es el mismo color
            }

            // Asignamos colores basados en la escala normalizada
            switch (escala) {
                case 4:
                    std::cout << "\033[1;41m " << std::setw(2) << valor << " \033[0m";
                    break;  // Rojo (alta probabilidad)
                case 3:
                    std::cout << "\033[1;43m " << std::setw(2) << valor << " \033[0m";
                    break;  // Amarillo
                case 2:
                    std::cout << "\033[1;42m " << std::setw(2) << valor << " \033[0m";
                    break;  // Verde
                case 1:
                    std::cout << "\033[1;44m " << std::setw(2) << valor << " \033[0m";
                    break;  // Azul
                default:
                    std::cout << "\033[1;47m " << std::setw(2) << valor << " \033[0m";
                    break;  // Blanco (baja probabilidad)
            }
            std::cout << " ";
        }
        std::cout << std::endl;
    }
}

std::tuple<int, int> calcularDisparo(int probabilidades[SIZE][SIZE]) {
    int maxX, maxY, maxN = -1;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (probabilidades[i][j] > maxN) {
                maxX = i;
                maxY = j;
                maxN = probabilidades[i][j];
            }
        }
    }
    return std::make_tuple(maxX, maxY);
}
