#include <unistd.h>

#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <tuple>
#include <vector>

#include "engineCore.hpp"

#define PESO_ED2 3

#define RESET "\033[0m"
#define BLUE "\033[34m"
#define GREEN "\033[32m"
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"

std::vector<int> longitudes = {2, 3, 3, 4, 5};  // Longitudes de los barcos

using namespace std;

class Barco {
   public:
    int x, y, lon;
    bool horizontal;
    std::vector<std::pair<int, int>> posiciones;  // Posiciones del barco en el tablero

    Barco(int xpos, int ypos, int longitud, bool hori)
        : x(xpos), y(ypos), lon(longitud), horizontal(hori) {
        for (int i = 0; i < lon; i++) {
            posiciones.push_back(horizontal ? std::make_pair(x, y + i) : std::make_pair(x + i, y));
        }
    }
};

class Tablero {
   public:
    int matrizPrivada[SIZE][SIZE] = {0};  // Tablero privado con barcos
    int matrizPublica[SIZE][SIZE] = {0};  // Tablero público (0 = agua, 2 = disparo fallado, 3 = disparo acertado)
    std::vector<Barco> barcos;

    bool colocarBarco(Barco barco, bool mostrarBarcos = false) {
        for (auto pos : barco.posiciones) {
            int i = pos.first, j = pos.second;
            if (i >= SIZE || j >= SIZE || matrizPrivada[i][j] != 0) {
                return false;  // Fuera de límites o posición ocupada
            }
        }
        for (auto pos : barco.posiciones) {
            matrizPrivada[pos.first][pos.second] = 1;  // Colocamos el barco en el tablero privado
        }
        barcos.push_back(barco);

        // Imprime el tablero solo si mostrarBarcos es true
        if (mostrarBarcos) {
            imprimirTablero(true);
        }
        return true;
    }

    bool disparar(int x, int y) {
        if (x < 0 || x >= SIZE || y < 0 || y >= SIZE || matrizPublica[x][y] == 2 || matrizPublica[x][y] == 3) {
            std::cout << "Disparo inválido.\n";
            return false;
        }
        if (matrizPrivada[x][y] == 1) {
            matrizPublica[x][y] = 3;  // Marcamos como disparo acertado en el tablero público
            matrizPrivada[x][y] = 3;  // Marcamos también en el tablero privado
            std::cout << "¡Barco tocado!\n";
            return true;
        } else {
            matrizPublica[x][y] = 2;
            matrizPrivada[x][y] = 2;  // Marcamos como disparo fallido en el tablero público
            std::cout << "Agua...\n";
            return false;
        }
    }

    bool quedanBarcos() {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (matrizPrivada[i][j] == 1) return true;  // Revisamos el tablero privado
            }
        }
        return false;
    }
    void imprimirTablero(bool mostrarBarcos = false) const {
        if (mostrarBarcos) {
            std::cout << "╔══════════════════════════╗" << std::endl;
            std::cout << "║     " << CYAN << "Tablero Privado " << RESET << "     ║" << std::endl;
            std::cout << "╚══════════════════════════╝" << std::endl;
        } else {
            std::cout << "╔══════════════════════════╗" << std::endl;
            std::cout << "║     " << CYAN << "Tablero Público " << RESET << "     ║" << std::endl;
            std::cout << "╚══════════════════════════╝" << std::endl;
        }

        std::cout << "     ";
        for (int i = 0; i < SIZE; ++i)
            std::cout << i << " ";  // Aligning column numbers
        std::cout << "\n   ───────────────────────" << std::endl;

        for (int i = 0; i < SIZE; ++i) {
            std::cout << std::setw(2) << i << " │ ";  // Aligning row numbers
            for (int j = 0; j < SIZE; ++j) {
                if (mostrarBarcos) {
                    // Imprimimos el tablero privado
                    if (matrizPrivada[i][j] == 0)
                        std::cout << BLUE << "~ " << RESET;  // Agua
                    else if (matrizPrivada[i][j] == 1)
                        std::cout << GREEN << "B " << RESET;  // Barco
                    else if (matrizPrivada[i][j] == 2)
                        std::cout << YELLOW << "O " << RESET;  // Disparo fallido
                    else if (matrizPrivada[i][j] == 3)
                        std::cout << RED << "X " << RESET;  // Disparo acertado
                } else {
                    // Imprimimos el tablero público
                    if (matrizPublica[i][j] == 0)
                        std::cout << BLUE << "~ " << RESET;  // Agua
                    else if (matrizPublica[i][j] == 2)
                        std::cout << YELLOW << "O " << RESET;  // Disparo fallido
                    else if (matrizPublica[i][j] == 3)
                        std::cout << RED << "X " << RESET;  // Disparo acertado
                }
            }
            std::cout << "│" << std::endl;  // End of row
        }

        std::cout << "   ───────────────────────" << std::endl;
    }
};

void inicializarTablero(int tablero[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            tablero[i][j] = 0;
        }
    }
}

// Función para calcular el peso horizontal y vertical en una posición
void calcularPesos(int tablero[SIZE][SIZE], int x, int y, int longitudBarco, int &pesoHorizontal, int &pesoVertical) {
    // Inicializar pesos con 0
    pesoHorizontal = 0;
    pesoVertical = 0;

    // Verificar espacio para colocar el barco horizontalmente
    if (y + longitudBarco <= SIZE) {
        bool espacioLibre = true;
        for (int j = y; j < y + longitudBarco; ++j) {
            if (tablero[x][j] != 0) {
                espacioLibre = false;
                break;
            }
        }
        if (espacioLibre) {
            pesoHorizontal = 1;
            if (x == 0 || x == SIZE - 1) {  // Si estamos en el borde superior o inferior
                pesoHorizontal += PESO_ED2;
            }
        }
    }

    // Verificar espacio para colocar el barco verticalmente
    if (x + longitudBarco <= SIZE) {
        bool espacioLibre = true;
        for (int i = x; i < x + longitudBarco; ++i) {
            if (tablero[i][y] != 0) {
                espacioLibre = false;
                break;
            }
        }
        if (espacioLibre) {
            pesoVertical = 1;
            if (y == 0 || y == SIZE - 1) {  // Si estamos en el borde izquierdo o derecho
                pesoVertical += PESO_ED2;
            }
        }
    }
}

// Función para colocar un barco aleatoriamente en el tablero con pesos
void colocarBarcoBot(Tablero &tablero, int longitudBarco) {
    vector<pair<int, int>> posicionesValidas;
    vector<int> pesos;

    // Iterar por cada posición posible y calcular pesos

    int pesoHorizontal = 0, pesoVertical = 0;

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            pesoHorizontal = 0;
            pesoVertical = 0;
            calcularPesos(tablero.matrizPrivada, i, j, longitudBarco, pesoHorizontal, pesoVertical);

            if (pesoHorizontal > 0 || pesoVertical > 0) {
                posicionesValidas.push_back({i, j});
                pesos.push_back(pesoHorizontal + pesoVertical);
            }
        }
    }

    // Elegir una posición basada en los pesos
    int sumaPesos = 0;
    for (int peso : pesos) {
        sumaPesos += peso;
    }
    int randomPeso = rand() % sumaPesos;

    int indiceElegido = 0;
    for (int k = 0; k < pesos.size(); ++k) {
        if (randomPeso < pesos[k]) {
            indiceElegido = k;
            break;
        }
        randomPeso -= pesos[k];
    }

    int x = posicionesValidas[indiceElegido].first;
    int y = posicionesValidas[indiceElegido].second;

    calcularPesos(tablero.matrizPrivada, x, y, longitudBarco, pesoHorizontal, pesoVertical);
    bool horizontal = (pesoHorizontal >= pesoVertical);

    Barco barco(x, y, longitudBarco, horizontal);
    tablero.colocarBarco(barco);
}

// Función para colocar barcos de manera interactiva para el jugador
void colocarBarcosJugador(Tablero &tablero) {
    for (int lon : longitudes) {
        bool colocado = false;
        while (!colocado) {
            int x, y;
            bool horizontal;
            std::cout << "Coloca un barco de longitud " << lon << ". Ingresa las coordenadas (x y) y orientación (0 para horizontal, 1 para vertical): ";
            std::cin >> x >> y >> horizontal;
            system("clear");
            Barco barco(x, y, lon, horizontal);
            colocado = tablero.colocarBarco(barco, true);
            if (!colocado) {
                std::cout << "Posición inválida. Intenta de nuevo.\n";
            }
        }
    }
}

// Generar disparos aleatorios para el bot
std::pair<int, int> disparoAleatorio() {
    return {rand() % SIZE, rand() % SIZE};
}

int main() {
    srand(time(0));
    int x, y;
    Tablero jugador, bot;
    int probabilidades[SIZE][SIZE] = {0};
    // Colocar los barcos del jugador manualmente
    colocarBarcosJugador(jugador);

    // Colocar los barcos del bot aleatoriamente

    for (const int &longitudBarco : longitudes) {
        colocarBarcoBot(bot, longitudBarco);
    }

    tuple<int, int> coordenadas;
    // Comienza el juego
    while (bot.quedanBarcos() && jugador.quedanBarcos()) {
        system("clear");  // Limpia la consola en Linux/macOS
        // system("cls");  // Para Windows

        // Mostrar tableros
        jugador.imprimirTablero(true);  // Muestra el tablero del jugador sin barcos
        memset(probabilidades, 0, sizeof(int) * SIZE * SIZE);
        calcularProbabilidades(jugador.matrizPublica, probabilidades, longitudes);

        mostrarHeatMapEscalado(probabilidades);

        bot.imprimirTablero(false);  // Muestra el tablero del bot sin barcos

        // Turno del jugador
        std::cout << "\nIntroduce coordenadas para disparar (x y): ";
        std::cin >> x >> y;
        bot.disparar(x, y);

        if (!bot.quedanBarcos()) {
            std::cout << "¡Felicidades, hundiste todos los barcos del bot!\n";
            break;
        }

        // Turno del bot

        coordenadas = calcularDisparo(probabilidades);
        jugador.disparar(get<0>(coordenadas), get<1>(coordenadas));
        std::cout << "El bot dispara en (" << get<0>(coordenadas) << ", " << get<1>(coordenadas) << ")\n";

        if (!jugador.quedanBarcos()) {
            std::cout << "El bot ha hundido todos tus barcos. ¡Game over!\n";
            break;
        }
    }

    return 0;
}
