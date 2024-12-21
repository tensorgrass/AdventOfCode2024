#include <iostream>     // std::cout
#include <vector>       // std::vector
#include <string>
#include <chrono>       // std::chrono
#include <cstdlib>      // std::strtoull
#include <algorithm>    // std::sort
#include <unordered_map>

using namespace std;

// #define LOG_OPERACIONES_BASICAS
// #define LOG_ERROR_ENCONTRADO
// #define LOG_INTERMEDIO
// #define LOG_CHECK
// #define LOG_COMB1
// #define LOG_COMB2
// #define LOG_COMB3


//input
#define PATH_FICHERO "input.txt"
// #define PATH_FICHERO "testA1.txt"
// #define PATH_FICHERO "testA2.txt"

#define TECLADO1_FILAS 4
#define TECLADO1_COLUMNAS 3
#define TECLADO2_FILAS 2
#define TECLADO2_COLUMNAS 3

struct Coordenadas
{
    int fila;
    int columna;
};

void calcular_keypad (std::vector<std::vector<char>> &teclado2, std::unordered_map<char, Coordenadas> &teclado2_mapa, std::vector<char> &teclado2_lista, int num_teclado, unordered_map<char, unordered_map<char, string>> &teclado2_camino)
{
    teclado2 = {
        {' ', '^', 'A'},
        {'<', 'v', '>'}};
    int num_tecla2 = 0;
    for (int i = 0; i < TECLADO2_FILAS; i++)
    {
        for (int j = 0; j < TECLADO2_COLUMNAS; j++)
        {
            teclado2_mapa[teclado2[i][j]] = {i, j};
            teclado2_lista[num_tecla2] = teclado2[i][j];
            num_tecla2++;
        }
    }
    for (char origen : teclado2_lista) {
        for (char destino : teclado2_lista) {
            int filas = teclado2_mapa[destino].fila - teclado2_mapa[origen].fila;
            int columnas = teclado2_mapa[destino].columna - teclado2_mapa[origen].columna;
            string filas_camino = "";
            if (filas > 0) {
                filas_camino = string(filas, 'v');
            } else if (filas < 0) {
                filas_camino = string(-filas, '^');
            }
            string columnas_camino = "";
            if (columnas > 0) {
                columnas_camino = string(columnas, '>');
            } else if (columnas < 0) {
                columnas_camino = string(-columnas, '<');
            }
            if ((origen == 'A' && columnas ==  -2) || (origen == '^' && columnas ==  -1)){
                teclado2_camino[origen][destino] = filas_camino + columnas_camino + "A";
            } else {
                teclado2_camino[origen][destino] = columnas_camino + filas_camino + "A";
            }
        }
    }
    #ifdef LOG_INTERMEDIO
        std::cout << "Teclado " << num_teclado << std::endl;
        for (const auto& origen : teclado2_camino) {
            for (const auto& destino : origen.second) {
                std::cout << "De " << origen.first << " a " << destino.first << ": "
                          << "Camino: " << destino.second << std::endl;
            }
        }
    #endif
}

bool valida_teclado1(std::string &movimiento)
{
    bool error = false;
    int fil = 3;
    int col = 2;
    for (char c : movimiento) {
        if (c == '^') {
            fil--;
        } else if (c == 'v') {
            fil++;
        } else if (c == '<') {
            col--;
        } else if (c == '>') {
            col++;
        }

        if (fil == 3 && col == 0) {
            #ifdef LOG_ERROR_ENCONTRADO
                std::cout << "ERROR en el movimiento1" << std::endl;
            #endif
            error = true;
        }
    }
    return !error;
}

bool valida_teclado2(std::string &movimiento)
{
    bool error = false;
    int fil = 0;
    int col = 2;
    for (char c : movimiento) {
        if (c == '^') {
            fil--;
        } else if (c == 'v') {
            fil++;
        } else if (c == '<') {
            col--;
        } else if (c == '>') {
            col++;
        }

        if (fil == 0 && col == 0) {
            #ifdef LOG_ERROR_ENCONTRADO
                std::cout << "ERROR en el movimiento2" << std::endl;
            #endif
            error = true;
            break;
        }
    }
    return !error;
}

void genera_combinaciones(std::string &mov1, std::vector<std::string> &combinaciones1)
{
    string mov = mov1.substr(0, mov1.size() - 1);
    vector<string> mov1_combinaciones;
    mov1_combinaciones.push_back(mov);

    string invertido = "";
    for (int i = mov.size() - 1; i >= 0; i--)
    {
        invertido += mov[i];
    }

    if (mov != invertido)
    {
        mov1_combinaciones.push_back(invertido);
    }

    vector<string> combinaciones1_tmp(combinaciones1);
    int num_combinaciones = combinaciones1.size();
    if (num_combinaciones == 0)
    {
        for (string comb : mov1_combinaciones)
        {
            combinaciones1.push_back(comb);
        }
    }
    else
    {
        for (string mov : combinaciones1_tmp)
        {
            for (string comb : mov1_combinaciones)
            {
                if (num_combinaciones > 0)
                {
                    combinaciones1[num_combinaciones - 1] = mov + comb;
                }
                else
                {
                    combinaciones1.push_back(mov + comb);
                }
                num_combinaciones--;
            }
        }
    }
    for (int i = 0; i < combinaciones1.size(); i++)
    {
        combinaciones1[i] += "A";
    }
}

int main()
{
    auto start = std::chrono::steady_clock::now();
    freopen(PATH_FICHERO, "r", stdin);
    string line;
    unsigned long long total = 0;
    int num_lineas = 0;
    int num_columnas = 0;


    vector<string> codigos;
    

    while(getline(cin, line))  {
        num_lineas++;
        #ifdef LOG_OPERACIONES_BASICAS
            printf("Linea %i: %s\n", num_lineas, line.c_str());
        #endif
        if (line.size() > 0) {
            codigos.push_back(line);
        }
    }
    // cerrar el fichero
    fclose(stdin);
    std::cout << "Lectura fichero: " << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;

    for (const auto& codigo : codigos) {
        std::cout << codigo << std::endl;
    }

    int num_teclado = 1;
    vector<vector<char>> teclado1 = {
        {'7', '8', '9'},
        {'4', '5', '6'},
        {'1', '2', '3'},
        {' ', '0', 'A'}
    };
    unordered_map<char, Coordenadas> teclado1_mapa;
    vector<char> teclado1_lista(TECLADO1_FILAS * TECLADO1_COLUMNAS);
    int num_tecla = 0;
    for (int i = 0; i < TECLADO1_FILAS; i++) {
        for (int j = 0; j < TECLADO1_COLUMNAS; j++) {
            teclado1_mapa[teclado1[i][j]] = {i, j};
            teclado1_lista[num_tecla] = teclado1[i][j];
            num_tecla++;
        }
    }
    // unordered_map<char, unordered_map<char, Coordenadas>> teclado1_combinaciones;
    unordered_map<char, unordered_map<char, string>> teclado1_camino;
    for (char origen : teclado1_lista) {
        for (char destino : teclado1_lista) {
            int filas = teclado1_mapa[destino].fila - teclado1_mapa[origen].fila;
            int columnas = teclado1_mapa[destino].columna - teclado1_mapa[origen].columna;
            // teclado1_combinaciones[origen][destino] = {
            //     filas,
            //     columnas
            // };
            string filas_camino = "";
            if (filas > 0) {
                filas_camino = string(filas, 'v');
            } else if (filas < 0) {
                filas_camino = string(-filas, '^');
            }
            string columnas_camino = "";
            if (columnas > 0) {
                columnas_camino = string(columnas, '>');
            } else if (columnas < 0) {
                columnas_camino = string(-columnas, '<');
            }
            // if (origen == 'A' || origen == '0') {
            //     teclado1_camino[origen][destino] = filas_camino + columnas_camino + "A";
            // } else {
            //     teclado1_camino[origen][destino] = columnas_camino + filas_camino + "A";
            // }
            teclado1_camino[origen][destino] = columnas_camino + filas_camino + "A";
        }
    }
    #ifdef LOG_INTERMEDIO
        std::cout << "Teclado " << num_teclado << std::endl;
        for (const auto& origen : teclado1_camino) {
            for (const auto& destino : origen.second) {
                std::cout << "De " << origen.first << " a " << destino.first << ": "
                          << "Camino: " << destino.second << std::endl;
            }
        }
    #endif

    num_teclado++;
    vector<vector<char>> teclado2(TECLADO2_FILAS, vector<char>(TECLADO2_COLUMNAS));
    unordered_map<char, Coordenadas> teclado2_mapa;
    vector<char> teclado2_lista(TECLADO2_FILAS * TECLADO2_COLUMNAS);
    unordered_map<char, unordered_map<char, string>> teclado2_camino;

    calcular_keypad (teclado2, teclado2_mapa, teclado2_lista, num_teclado, teclado2_camino);
    
    for (string code : codigos) {

        int movimiento3_min = 9999;

        vector<string> combinaciones1;
        string codigo = "A" + code;
        int valor_codigo = stoi(codigo.substr(1, codigo.size() - 2));
        #ifdef LOG_CHECK
            std::cout << "Codigo: " << codigo << std::endl;
        #endif
        
        for (int t1 = 1; t1 < codigo.size(); t1++) {
            char origen1 = codigo[t1 - 1];
            char destino1 = codigo[t1];
            string mov1 = teclado1_camino[origen1][destino1];
            bool todos_iguales = true;
            for (int i = 1; i < mov1.size() - 1; i++) {
                if (mov1[i] != mov1[i - 1]) {
                    todos_iguales = false;
                    break;
                }
            }
            genera_combinaciones(mov1, combinaciones1);

            #ifdef LOG_CHECK
                std::cout << "De Teclado1 " << origen1 << " a " << destino1 << ": " << mov1 << std::endl;
            #endif
        }
        #ifdef LOG_CHECK
            std::cout << "Movimiento1: " << movimiento1 << std::endl;
        #endif


        #ifdef LOG_COMB1
            for (const auto& comb : combinaciones1) {
                std::cout << "Combinacion1: " << comb << std::endl;
            }
        #endif

        for (string movimiento1 : combinaciones1) {
            if (valida_teclado1(movimiento1)) {
                movimiento1 = "A" + movimiento1;
                vector<string> combinaciones2;
                for (int t2 = 1; t2 < movimiento1.size(); t2++) {
                    char origen2 = movimiento1[t2 - 1];
                    char destino2 = movimiento1[t2];
                    string mov2 = teclado2_camino[origen2][destino2];

                    genera_combinaciones(mov2, combinaciones2);
                    // movimiento2 += mov2;
                    #ifdef LOG_CHECK
                        std::cout << "De Teclado2 " << origen2 << " a " << destino2 << ": " << mov2 << std::endl;
                    #endif
                }
                #ifdef LOG_CHECK
                    std::cout << "Movimiento2: " << movimiento2 << std::endl;
                #endif

                #ifdef LOG_COMB2
                    for (const auto& comb : combinaciones2) {
                        std::cout << "Combinacion2: " << comb << std::endl;
                    }
                #endif

                for (string movimiento2 : combinaciones2) {
                    if (valida_teclado2(movimiento2)) {
                        movimiento2 = "A" + movimiento2;
                        vector<string> combinaciones3;
                        for (int t3 = 1; t3 < movimiento2.size(); t3++) {
                            char origen3 = movimiento2[t3 - 1];
                            char destino3 = movimiento2[t3];
                            string mov3 = teclado2_camino[origen3][destino3];
                            genera_combinaciones(mov3, combinaciones3);
                            #ifdef LOG_CHECK
                                std::cout << "De Teclado3 " << origen3 << " a " << destino3 << ": " << mov3 << std::endl;
                            #endif
                        }
                        #ifdef LOG_CHECK
                            std::cout << "Movimiento3: " << movimiento3 << std::endl;
                        #endif
                        #ifdef LOG_COMB3
                            for (const auto& comb : combinaciones3) {
                                std::cout << "Combinacion3: " << comb << std::endl;
                            }
                        #endif

                        for (string movimiento3 : combinaciones3) {
                            if (valida_teclado2(movimiento3)) {
                                int movimiento3_size = movimiento3.size();
                                if (movimiento3_size < movimiento3_min) {
                                    movimiento3_min = movimiento3_size;
                                    std::cout << "Valor codigo: " << valor_codigo << std::endl;
                                    std::cout << "Tamaño de movimiento3: " << movimiento3_size << std::endl;
                                }
                            }
                        }
                    }
                }
            }
        }
        total += valor_codigo * movimiento3_min;
        cout << "Total intermedio: " << total << endl;
    }

    std::cout << "Total: " << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;
    cout << "Total sum: " << total << endl;
    //SOLUCION: 126384
    //HIGH 143256, 148460
    //LOW 
    //134887, 138764
}


