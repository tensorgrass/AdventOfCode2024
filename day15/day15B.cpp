#include <iostream>     // std::cout
#include <vector>       // std::vector
#include <string>
#include <chrono>       // std::chrono
#include <cstdlib>      // std::strtoull

using namespace std;

// #define LOG_OPERACIONES_BASICAS
// #define LOG_ERROR_ENCONTRADO
// #define LOG_INTERMEDIO
// #define LOG_CHECK
// #define LOG_MAPA

#define PATH_FICHERO "input.txt"
// #define PATH_FICHERO "testB1.txt"
// #define PATH_FICHERO "testB1_10.txt"
// #define PATH_FICHERO "testB2.txt"

bool mueve_elemento(int linea, int columna, char movimiento, std::vector<std::vector<char>> &map, bool is_caja_horizontal, bool is_caja_vertical, bool test_mueve_caja_vertical);
void imprimir_mapa(std::vector<std::vector<char>> &map);

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
            num_columnas = line_size * 2;
        }
        if (line_size > 0) {
            if (line[0] == '#') {
                vector<char> mapa_columna;
                for (int i = 0; i < line_size; i++) {
                    if (line[i] == '#') {
                        mapa_columna.push_back('#');
                        mapa_columna.push_back('#');
                    }
                    else if (line[i] == 'O') {
                        mapa_columna.push_back('[');
                        mapa_columna.push_back(']');
                    }
                    else if (line[i] == '.') {
                        mapa_columna.push_back('.');
                        mapa_columna.push_back('.');
                    }
                    else if (line[i] == '@') {
                        mapa_columna.push_back('@');
                        mapa_columna.push_back('.');
                        robot_linea = num_lineas - 1;
                        robot_columna = i * 2;
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

        if (mueve_elemento(robot_linea, robot_columna, movimiento, map, false, false, false)) {
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
        imprimir_mapa(map);

        //Testear que no hay errores
        // bool error = false;
        // for (int i = 0; i < map.size(); i++) {
        //     for (int j = 0; j < map[i].size(); j++) {
        //         if (map[i][j] == '[' & map[i][j + 1] != ']' || map[i][j - 1] != '[' & map[i][j] == ']') {
        //             error = true;

        //         }
        //     }
        // }
        // if (error) {
        //     printf("Error en movimiento %d: %c\n", num_mov, movimiento);
        //     break;
        // }
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
            if (map[i][j] == '[') {
                total += (i * 100) + j;
            }
        }
    }
    std::cout << "Total: " << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;
    cout << "Total robots: " << total << endl;
    //SOLUCION: 1527969 
    //test1: 2028
    //test2: 10092
}



bool mueve_elemento(int linea, int columna, char movimiento, std::vector<std::vector<char>> &map, bool is_caja_horizontal, bool is_caja_vertical, bool test_mueve_caja_vertical)
{
    int linea_siguiente = linea;
    int linea_medio = linea;
    int columna_siguiente = columna;
    int columna_medio = columna;
    bool permite_movimiento = false;
    if (movimiento == '>') {
        columna_siguiente++;
        if (is_caja_horizontal) {
            columna_medio = columna_siguiente;
            columna_siguiente++;
        }
    }
    else if (movimiento == '<') {
        columna_siguiente--;
        if (is_caja_horizontal) {
            columna_medio = columna_siguiente;
            columna_siguiente--;
        }
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
    else if (map[linea_siguiente][columna_siguiente] == ']') {
        if (movimiento == '<') {
            permite_movimiento = mueve_elemento(linea_siguiente, columna_siguiente, movimiento, map, true, false, false);
            if (permite_movimiento) {
                if (is_caja_horizontal) {
                    map[linea_siguiente][columna_siguiente] = map[linea_medio][columna_medio];
                    map[linea_medio][columna_medio] = map[linea][columna];
                    map[linea][columna] = '.';
                }
                else {
                    map[linea_siguiente][columna_siguiente] = map[linea][columna];
                    map[linea][columna] = '.';
                }
            }
        }
        else if (movimiento == '^' || movimiento == 'v') {
            if (!is_caja_vertical || test_mueve_caja_vertical) {
                bool permite_movimiento_derecha = mueve_elemento(linea_siguiente, columna_siguiente, movimiento, map, false, true, true);
                bool permite_movimiento_izquierda = mueve_elemento(linea_siguiente, columna_siguiente - 1, movimiento, map, false, true, true);
                permite_movimiento = permite_movimiento_derecha && permite_movimiento_izquierda;
            }
            if (!test_mueve_caja_vertical && ((!is_caja_vertical && permite_movimiento) || (is_caja_vertical))) {
                mueve_elemento(linea_siguiente, columna_siguiente, movimiento, map, false, true, false);
                mueve_elemento(linea_siguiente, columna_siguiente - 1, movimiento, map, false, true, false);
                map[linea_siguiente][columna_siguiente] = map[linea][columna];
                map[linea][columna] = '.';
                // map[linea_siguiente][columna_siguiente - 1] = map[linea][columna - 1];
                // map[linea][columna] = '.';
            }
        }
    }
    else if (map[linea_siguiente][columna_siguiente] == '[') {
        if (movimiento == '>') {
            permite_movimiento = mueve_elemento(linea_siguiente, columna_siguiente, movimiento, map, true, false, false);
            if (permite_movimiento) {
                if (is_caja_horizontal) {
                    map[linea_siguiente][columna_siguiente] = map[linea_medio][columna_medio];
                    map[linea_medio][columna_medio] = map[linea][columna];
                    map[linea][columna] = '.';
                }
                else {
                    map[linea_siguiente][columna_siguiente] = map[linea][columna];
                    map[linea][columna] = '.';
                }
            }
        }
        else if (movimiento == '^' || movimiento == 'v') {
            if (!is_caja_vertical || test_mueve_caja_vertical) {
                bool permite_movimiento_derecha = mueve_elemento(linea_siguiente, columna_siguiente, movimiento, map, false, true, true);
                bool permite_movimiento_izquierda = mueve_elemento(linea_siguiente, columna_siguiente + 1, movimiento, map, false, true, true);
                permite_movimiento = permite_movimiento_derecha && permite_movimiento_izquierda;
            }
            if (!test_mueve_caja_vertical && ((!is_caja_vertical && permite_movimiento) || (is_caja_vertical))) {
                mueve_elemento(linea_siguiente, columna_siguiente, movimiento, map, false, true, false);
                mueve_elemento(linea_siguiente, columna_siguiente + 1, movimiento, map, false, true, false);
                map[linea_siguiente][columna_siguiente] = map[linea][columna];
                map[linea][columna] = '.';
                // map[linea_siguiente][columna_siguiente + 1] = map[linea][columna + 1];
                // map[linea][columna] = '.';
            }
        }
    }
    else if (map[linea_siguiente][columna_siguiente] == '.') {
        if (is_caja_horizontal) {
            map[linea_siguiente][columna_siguiente] = map[linea_medio][columna_medio];
            map[linea_medio][columna_medio] = map[linea][columna];
            map[linea][columna] = '.';
        }
        else {
            if (!test_mueve_caja_vertical) {
                map[linea_siguiente][columna_siguiente] = map[linea][columna];
                map[linea][columna] = '.';
            }
        }
        permite_movimiento = true;
    }
    else {
        #ifdef LOG_ERROR_ENCONTRADO
            printf("ERROR: Movimiento no permitido: %c\n", movimiento);
        #endif
    }
    return permite_movimiento;
}

void imprimir_mapa(std::vector<std::vector<char>> &map){
    #ifdef LOG_MAPA
        for (int i = 0; i < map.size(); i++) {
            for (int j = 0; j < map[i].size(); j++) {
                printf("%c", map[i][j]);
            }
            printf("\n");
        }
    #endif
}