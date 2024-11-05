#include <iostream>
#include <vector>

class Barco {
   public:
    int x;
    int y;
    int lon;
    bool horizontal;

    Barco(int xpos, int ypos, int longitud, bool hori)
        : x(xpos), y(ypos), lon(longitud), horizontal(hori) {}
};

class Lancha : public Barco {
   public:
    Lancha(int xpos, int ypos, bool hori)
        : Barco(xpos, ypos, 2, hori) {}
};

class Destructor : public Barco {
   public:
    Destructor(int xpos, int ypos, bool hori)
        : Barco(xpos, ypos, 3, hori) {}
};

class Crucero : public Barco {
   public:
    Crucero(int xpos, int ypos, bool hori)
        : Barco(xpos, ypos, 4, hori) {}
};

class Acorazado : public Barco {
   public:
    Acorazado(int xpos, int ypos, bool hori)
        : Barco(xpos, ypos, 5, hori) {}
};
int const SIZE = 10;

int tablero[SIZE][SIZE];
int probabilidades[SIZE][SIZE];

void calcularProbabilidades(int tablero[SIZE][SIZE], int probabilidades[SIZE][SIZE], int longitudBarco) {
    // Horizontalmente: verificamos celdas libres en cada fila
    for (int i = 0; i < SIZE; ++i) {
        int celdasLibres = 0;

        // Primer barrido para acumulación de celdas libres
        for (int j = 0; j < SIZE; ++j) {
            if (tablero[i][j] == 0) { // Celda no disparada
                ++celdasLibres;
            } else {
                celdasLibres = 0; // Reseteamos si hay un disparo
            }

            // Si tenemos suficientes celdas libres para el barco
            if (celdasLibres >= longitudBarco) {
                // Incrementamos el rango actual para todas las celdas posibles
                for (int k = j - longitudBarco + 1; k <= j; ++k) {
                    probabilidades[i][k]++;
                }
            }
        }
    }

    // Verticalmente: verificamos celdas libres en cada columna
    for (int j = 0; j < SIZE; ++j) {
        int celdasLibres = 0;

        // Primer barrido para acumulación de celdas libres
        for (int i = 0; i < SIZE; ++i) {
            if (tablero[i][j] == 0) { // Celda no disparada
                ++celdasLibres;
            } else {
                celdasLibres = 0; // Reseteamos si hay un disparo
            }

            // Si tenemos suficientes celdas libres para el barco
            if (celdasLibres >= longitudBarco) {
                // Incrementamos el rango actual para todas las celdas posibles
                for (int k = i - longitudBarco + 1; k <= i; ++k) {
                    probabilidades[k][j]++;
                }
            }
        }
    }
}


int main() {
    int tablero[SIZE][SIZE] = {0};       // Inicializamos el tablero con 0 (sin disparos)
    int probabilidades[SIZE][SIZE] = {0}; // Inicializamos el tablero de probabilidades con 0
    int longitudBarco = 3; // Ejemplo: barcos de longitud 3

    // Calculamos probabilidades
    calcularProbabilidades(tablero, probabilidades, longitudBarco);

    // Imprimimos el tablero de probabilidades
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            std::cout << probabilidades[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}