#include <iostream>     // std::cout
#include <vector>       // std::vector
#include <string>
#include <chrono>       // std::chrono
#include "day10BB.h"

using namespace std;

// #define LOG_OPERACIONES_BASICAS
// #define LOG_ERROR_ENCONTRADO
// #define LOG_CALCULOS
// #define LOG_ENCONTRADO
// #define LOG_PARCIAL

struct Origen {
    int i;
    int j;
    bool visitado;
};

int main()
{
    auto start = std::chrono::steady_clock::now();
    freopen("input.txt", "r", stdin);
    // freopen("testA3.txt", "r", stdin);
    string line;
    long total = 0;
    int num_lines = 0;
    int num_columns = 0;
    vector<vector<int>> mapa;
    while(getline(cin, line))  {
        num_lines++;
        #ifdef LOG_OPERACIONES_BASICAS
            printf("Linea %i: %s\n", num_lines, line.c_str());
        #endif
        if (num_columns == 0) {
            num_columns = line.size();
        }
        vector<int> mapa_xp;
        for (int i = 0; i < num_columns; i++) {
            mapa_xp.push_back(line[i] - '0');
        }
        mapa.push_back(mapa_xp);
    }
    // cerrar el fichero
    fclose(stdin);
    #ifdef LOG_OPERACIONES_BASICAS
        printf("Numero de lineas: %i Numero de columnas: %i\n", num_lines, num_columns);
    #endif
    std::cout << "Lectura fichero: " << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;

    for (int i = 0; i < num_lines; i++) {
        for (int j = 0; j < num_columns; j++) {
            int altura = 0;
            if (mapa[i][j] == altura) {
                #ifdef LOG_ENCONTRADO
                    printf("Inicio camino en %i %i\n", i, j);
                #endif
                busca_camino(0, i, num_lines, j, num_columns, mapa, altura + 1, total);
            }
        }  
    }
        
    std::cout << "Total: " << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;
    printf("Total paths: %d\n", total);
    cout << "Total paths: " << total << endl;
    //SOLUCION: 1764
}

void busca_camino(int direccion, int fila, int num_lines, int columna, int num_columns, std::vector<std::vector<int>> &mapa, int altura, long &total)
{
    bool fuera_rango = false;
    int fila_siguiente = fila;
    int columna_siguiente = columna;
    int direccion_siguiente = direccion + 1;
    //switch direccion
    // 0: arriba
    // 1: abajo
    // 2: izquierda
    // 3: derecha
    switch (direccion) {
    case 0:
        if (fila_siguiente > 0) {
            fila_siguiente--;
        }
        else {
            fuera_rango = true; 
        }
        break;
    case 1:
        if (fila_siguiente < num_lines - 1) {
            fila_siguiente++;
        }
        else {
            fuera_rango = true;
        }
        break;
    case 2:
        if (columna_siguiente > 0) {
            columna_siguiente--;
        }
        else {
            fuera_rango = true;
        }
        break;
    case 3:
        if (columna_siguiente < num_columns - 1) {
            columna_siguiente++;
        }
        else {
            fuera_rango = true;
        }
        break;
    default:
        break;
    }

    #ifdef LOG_PARCIAL
        if (!fuera_rango) {
            printf("Camino en %i %i con altura %i\n", fila_siguiente, columna_siguiente, altura);
        }
    #endif
    if (!fuera_rango && mapa[fila_siguiente][columna_siguiente] == altura) {
        #ifdef LOG_PARCIAL
            printf("Camino parcial en %i %i con altura %i\n", fila_siguiente, columna_siguiente, altura);
        #endif
        if (altura == 9) {
            #ifdef LOG_ENCONTRADO
                printf("Camino encontrado en %i %i con total: %d\n", fila_siguiente, columna_siguiente, total + 1);
            #endif
            total++;
        }
        else {
            busca_camino(0, fila_siguiente, num_lines, columna_siguiente, num_columns, mapa, altura + 1, total);
        }
    }
    if (direccion_siguiente <= 3) {
        busca_camino(direccion_siguiente, fila, num_lines, columna, num_columns, mapa, altura, total);
    }

}
