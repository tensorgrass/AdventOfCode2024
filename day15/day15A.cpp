#include <iostream>     // std::cout
#include <vector>       // std::vector
#include <string>
#include <chrono>       // std::chrono
#include <cstdlib>      // std::strtoull

using namespace std;

// #define LOG_OPERACIONES_BASICAS
// #define LOG_ERROR_ENCONTRADO
// #define LOG_INTERMEDIO
// #define LOG_CUADRANTES
// #define LOG_CHECK


#define PATH_FICHERO "input.txt"
// #define PATH_FICHERO "testA1.txt"
// #define PATH_FICHERO "testA1_6.txt"
// #define PATH_FICHERO "testA2.txt"

bool mueve_elemento(int linea, int columna, char movimiento, std::vector<std::vector<char>> &map);

int main()
{
    auto start = std::chrono::steady_clock::now();
    freopen(PATH_FICHERO, "r", stdin);
    string line;
    unsigned long long total = 0;
    int num_lineas = 0;
    int num_columnas = 0;
    vector<vector<char>> map;
    vector<char> mov;
    int robot_linea = 0;
    int robot_columna = 0;

  
    while(getline(cin, line))  {
        num_lineas++;
        #ifdef LOG_OPERACIONES_BASICAS
            printf("Linea %i: %s\n", num_lineas, line.c_str());
        #endif
        int line_size = line.size();
        if (num_columnas <= 0) {
            num_columnas = line_size;
        }
        if (line_size > 0) {
            if (line[0] == '#') {
                vector<char> mapa_columna(line_size, '.');
                for (int i = 0; i < line_size; i++) {
                    mapa_columna[i] = line[i];
                    if (line[i] == '@') {
                        robot_linea = num_lineas - 1;
                        robot_columna = i;
                    }
                }
                map.push_back(mapa_columna);
            }
            else {
                for (char c: line) {
                    mov.push_back(c);
                }
            }
        }
    }
    // cerrar el fichero
    fclose(stdin);
    std::cout << "Lectura fichero: " << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;

    #ifdef LOG_OPERACIONES_BASICAS
        printf("Mapa:\n");
        for (int i = 0; i < map.size(); i++) {
            for (int j = 0; j < map[i].size(); j++) {
                printf("%c", map[i][j]);
            }
            printf("\n");
        }
        printf("Movimientos:\n");
        for (int i = 0; i < mov.size(); i++) {
            printf("%c", mov[i]);
        }
        printf("\n");
    #endif

    int num_mov = 0;
    for (char movimiento : mov) {
        num_mov++;
        #ifdef LOG_INTERMEDIO
            printf("Movimiento %d: %c\n", num_mov, movimiento);
        #endif

        if (mueve_elemento(robot_linea, robot_columna, movimiento, map)) {
            if (movimiento == '>') {
                robot_columna++;
            }
            else if (movimiento == '<') {
                robot_columna--;
            }
            else if (movimiento == '^') {
                robot_linea--;
            }
            else if (movimiento == 'v') {
                robot_linea++;
            }
        }
    }

    #ifdef LOG_CHECK
        printf("Mapa final:\n");
        for (int i = 0; i < map.size(); i++) {
            for (int j = 0; j < map[i].size(); j++) {
                printf("%c", map[i][j]);
            }
            printf("\n");
        }
    #endif

    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (map[i][j] == 'O') {
                total += (i * 100) + j;
            }
        }
    }
    std::cout << "Total: " << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;
    cout << "Total robots: " << total << endl;
    //SOLUCION: 1516281 
    //test1: 2028
    //test2: 10092
}

bool mueve_elemento(int linea, int columna, char movimiento, std::vector<std::vector<char>> &map)
{
    int linea_siguiente = linea;
    int columna_siguiente = columna;
    bool permite_movimiento = false;
    if (movimiento == '>') {
        columna_siguiente++;
    }
    else if (movimiento == '<') {
        columna_siguiente--;
    }
    else if (movimiento == '^') {
        linea_siguiente--;
    }
    else if (movimiento == 'v') {
        linea_siguiente++;
    }
    else {
    #ifdef LOG_ERROR_ENCONTRADO
        printf("Error: Movimiento no reconocido: %c\n", movimiento);
    #endif
    }

    if (map[linea_siguiente][columna_siguiente] == '#') {
    #ifdef LOG_INTERMEDIO
        printf("Movimiento no permitido pared encontrada: %c\n", movimiento);
    #endif
    }
    else if (map[linea_siguiente][columna_siguiente] == 'O') {
        permite_movimiento = mueve_elemento(linea_siguiente, columna_siguiente, movimiento, map);
        if (permite_movimiento) {
            map[linea_siguiente][columna_siguiente] = map[linea][columna];
            map[linea][columna] = '.';
        }
    }
    else if (map[linea_siguiente][columna_siguiente] == '.') {
        map[linea_siguiente][columna_siguiente] = map[linea][columna];
        map[linea][columna] = '.';
        permite_movimiento = true;
    }
    else {
        #ifdef LOG_ERROR_ENCONTRADO
            printf("ERROR: Movimiento no permitido: %c\n", movimiento);
        #endif
    }
    return permite_movimiento;
}
