#include <iostream>     // std::cout
#include <vector>       // std::vector
#include <string>
#include <chrono>       // std::chrono
#include "day10A.h"

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
    // freopen("testA1.txt", "r", stdin);
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
        //imprimir el listado de tipos de antenas

    #endif


    std::cout << "Lectura fichero: " << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;
    vector<vector<vector<vector<bool>>>> mapa_origen;
    for (int i = 0; i < num_lines; i++) {
        vector<vector<vector<bool>>> mapa_origen_xp;
        for (int j = 0; j < num_columns; j++) {
            vector<vector<bool>> mapa_origen_xp_yp;
            for (int xp = 0; xp < num_lines; xp++) {
                vector<bool> mapa_origen_xp_yp_zp;
                for (int yp = 0; yp < num_columns; yp++) {
                    mapa_origen_xp_yp_zp.push_back(false);
                }
                mapa_origen_xp_yp.push_back(mapa_origen_xp_yp_zp);
            }
            mapa_origen_xp.push_back(mapa_origen_xp_yp);
        }
        mapa_origen.push_back(mapa_origen_xp);
    }
    std::cout << "Prepara vector: " << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;

    for (int i = 0; i < num_lines; i++) {
        for (int j = 0; j < num_columns; j++) {
            int altura = 0;
            if (mapa[i][j] == altura) {
                #ifdef LOG_ENCONTRADO
                    printf("Inicio camino en %i %i\n", i, j);
                #endif
                busca_camino(i, num_lines, j, num_columns, mapa, altura + 1, total, mapa_origen, i, j);
            }
        }  
    }
        
    std::cout << "Total: " << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;
    printf("Total paths: %d\n", total);
    cout << "Total paths: " << total << endl;
    //SOLUCION: 760


}

void busca_camino(int i, int num_lines, int j, int num_columns, std::vector<std::vector<int>> &mapa, int altura, long &total, std::vector<std::vector<std::vector<std::vector<bool>>>> &mapa_origen, int fila_origen, int columna_origen)
{
    int fila_inicial = i - 1;
    if (fila_inicial >= 0) {
        if (mapa[fila_inicial][j] == altura) {
            #ifdef LOG_PARCIAL
                printf("Camino parcial en %i %i con altura %i\n", fila_inicial, j, altura);
            #endif
            if (altura == 9) {
                if (mapa_origen[fila_inicial][j][fila_origen][columna_origen]) {
                    #ifdef LOG_ERROR_ENCONTRADO
                        printf("Camino con origen ya encontrado en %i %i\n", fila_inicial, j);
                    #endif
                }
                else {
                    #ifdef LOG_ENCONTRADO
                        printf("Camino encontrado en %i %i\n", fila_inicial, j);
                    #endif
                    total++;
                    mapa_origen[fila_inicial][j][fila_origen][columna_origen] = true;
                }

            }
            else {
                busca_camino(fila_inicial, num_lines, j, num_columns, mapa, altura + 1, total, mapa_origen, fila_origen, columna_origen);
            }
        }
    }
    int fila_final = i + 1;
    if (fila_final < num_lines) {
        if (mapa[fila_final][j] == altura) {
            #ifdef LOG_PARCIAL
                printf("Camino parcial en %i %i con altura %i\n", fila_final, j, altura);
            #endif
            if (altura == 9) {
                if (mapa_origen[fila_final][j][fila_origen][columna_origen]) {
                    #ifdef LOG_ERROR_ENCONTRADO
                        printf("Camino con origen ya encontrado en %i %i\n", fila_final, j);
                    #endif
                }
                else {
                    #ifdef LOG_ENCONTRADO
                        printf("Camino encontrado en %i %i\n", fila_final, j);
                    #endif
                    total++;
                    mapa_origen[fila_final][j][fila_origen][columna_origen] = true;
                }
            }
            else {
                busca_camino(fila_final, num_lines, j, num_columns, mapa, altura + 1, total, mapa_origen, fila_origen, columna_origen);
            }
        }
    }

    int columna_inicial = j - 1;
    if (columna_inicial >= 0) {
        if (mapa[i][columna_inicial] == altura) {
            #ifdef LOG_PARCIAL
                printf("Camino parcial en %i %i con altura %i\n", i, columna_inicial, altura);
            #endif
            if (altura == 9) {
                if (mapa_origen[i][columna_inicial][fila_origen][columna_origen]) {
                    #ifdef LOG_ERROR_ENCONTRADO
                        printf("Camino con origen ya encontrado en %i %i\n", i, columna_inicial);
                    #endif
                }
                else {
                    #ifdef LOG_ENCONTRADO
                        printf("Camino encontrado en %i %i\n", i, columna_inicial);
                    #endif
                    total++;
                    mapa_origen[i][columna_inicial][fila_origen][columna_origen] = true;
                }
            }
            else {
                busca_camino(i, num_lines, columna_inicial, num_columns, mapa, altura + 1, total, mapa_origen, fila_origen, columna_origen);
            }
        }
    }
    int columna_final = j + 1;
    if (columna_final < num_columns) {
        if (mapa[i][columna_final] == altura) {
            #ifdef LOG_PARCIAL
                printf("Camino parcial en %i %i con altura %i\n", i, columna_final, altura);
            #endif
            if (altura == 9) {
                if (mapa_origen[i][columna_final][fila_origen][columna_origen]) {
                    #ifdef LOG_ERROR_ENCONTRADO
                        printf("Camino con origen ya encontrado en %i %i\n", i, columna_final);
                    #endif
                }
                else {
                    #ifdef LOG_ENCONTRADO
                        printf("Camino encontrado en %i %i\n", i, columna_final);
                    #endif
                    total++;
                    mapa_origen[i][columna_final][fila_origen][columna_origen] = true;
                }
            }
            else {
                busca_camino(i, num_lines, columna_final, num_columns, mapa, altura + 1, total, mapa_origen, fila_origen, columna_origen);
            }
        }
    }
}
