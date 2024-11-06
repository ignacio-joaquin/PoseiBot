#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <vector>
#include "engineCore.hpp"

#define RESET "\033[0m"
#define BLUE "\033[34m"
#define GREEN "\033[32m"
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"


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

    bool colocarBarco(Barco barco) {
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
        return true;
    }

    bool disparar(int x, int y) {
        if (x < 0 || x >= SIZE || y < 0 || y >= SIZE || matrizPublica[x][y] == 2 || matrizPublica[x][y] == 3) {
            std::cout << "Disparo inválido.\n";
            return false;
        }
        if (matrizPrivada[x][y] == 1) {
            matrizPublica[x][y] = 3;  // Marcamos como disparo acertado en el tablero público
            std::cout << "¡Barco tocado!\n";
            return true;
        } else {
            matrizPublica[x][y] = 2;  // Marcamos como disparo fallido en el tablero público
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
            std::cout << "║     " << CYAN << "Tablero Privado" << RESET << "     ║" << std::endl;
            std::cout << "╚══════════════════════════╝" << std::endl;
        } else {
            std::cout << "╔══════════════════════════╗" << std::endl;
            std::cout << "║     " << CYAN << "Tablero Público" << RESET << "     ║" << std::endl;
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
                } else {
                    // Imprimimos el tablero público
                    if (matrizPublica[i][j] == 0)
                        std::cout << BLUE << "~ " << RESET;  // Agua
                    else if (matrizPublica[i][j] == 2)
                        std::cout << YELLOW << "O " << RESET;  // Disparo fallado
                    else if (matrizPublica[i][j] == 3)
                        std::cout << RED << "X " << RESET;  // Disparo acertado
                }
            }
            std::cout << "│" << std::endl;  // End of row
        }

        std::cout << "   ───────────────────────" << std::endl;
    }
};

// Colocar barcos aleatoriamente en el tablero
void inicializarTableroAleatorio(Tablero &tablero) {
    srand(time(0));
    std::vector<int> longitudes = {2, 3, 3, 4, 5};  // Longitudes de los barcos

    for (int lon : longitudes) {
        bool colocado = false;
        while (!colocado) {
            int x = rand() % SIZE;
            int y = rand() % SIZE;
            bool horizontal = rand() % 2;
            Barco barco(x, y, lon, horizontal);
            colocado = tablero.colocarBarco(barco);
        }
    }
}

// Función para colocar barcos de manera interactiva para el jugador
void colocarBarcosJugador(Tablero &tablero) {
    std::vector<int> longitudes = {2, 3, 3, 4, 5};  // Longitudes de los barcos
    for (int lon : longitudes) {
        bool colocado = false;
        while (!colocado) {
            int x, y;
            bool horizontal;
            std::cout << "Coloca un barco de longitud " << lon << ". Ingresa las coordenadas (x y) y orientación (0 para horizontal, 1 para vertical): ";
            std::cin >> x >> y >> horizontal;
            Barco barco(x, y, lon, horizontal);
            colocado = tablero.colocarBarco(barco);
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
    Tablero jugador, bot;
    int probabilidades[SIZE][SIZE] = {0};
    // Colocar los barcos del jugador manualmente
    colocarBarcosJugador(jugador);

    // Colocar los barcos del bot aleatoriamente
    inicializarTableroAleatorio(bot);

    // Comienza el juego
    while (bot.quedanBarcos() && jugador.quedanBarcos()) {
        int x, y;
        system("clear");  // Limpia la consola en Linux/macOS
        // system("cls");  // Para Windows

        // Mostrar tableros
        jugador.imprimirTablero(false);  // Muestra el tablero del jugador sin barcos

        calcularProbabilidades(bot.matrizPublica, probabilidades, 3);
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
        auto [botX, botY] = disparoAleatorio();
        std::cout << "El bot dispara en (" << botX << ", " << botY << ")\n";
        jugador.disparar(botX, botY);

        if (!jugador.quedanBarcos()) {
            std::cout << "El bot ha hundido todos tus barcos. ¡Game over!\n";
            break;
        }
    }

    return 0;
}
