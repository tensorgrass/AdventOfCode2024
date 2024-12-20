#include <iostream>     // std::cout
#include <vector>       // std::vector
#include <string>
#include <chrono>       // std::chrono
#include <cstdlib>      // std::strtoull
#include <algorithm>    // std::sort
#include <unordered_map>

using namespace std;

struct Respuesta {
    bool encontrado;
    bool con_aciertos;
    int patron_size;
};

#define LOG_OPERACIONES_BASICAS
#define LOG_ERROR_ENCONTRADO
#define LOG_INTERMEDIO
// #define LOG_CHECK

//input
#define MIN_MEJORA 100
#define PATH_FICHERO "input.txt"

// #define MIN_MEJORA 6
// #define PATH_FICHERO "testA1.txt"
// #define PATH_FICHERO "testA2.txt"



void busca_camino(std::vector<std::string> &mapa, int f, int c, std::vector<std::vector<int>> &camino, int &num_lineas, int &num_columnas, int profundidad) {
    if (f < 0 || f >= num_lineas || c < 0 || c >= num_columnas || mapa[f][c] == '#' || camino[f][c] >= 0) {
        return;
    }
    camino[f][c] = profundidad;
    if (mapa[f][c] == 'E') {
        return;
    }

    int f_siguiente = f;
    int c_siguiente = c + 1;
    busca_camino(mapa, f_siguiente, c_siguiente, camino, num_lineas, num_columnas, profundidad + 1);
    f_siguiente = f + 1;
    c_siguiente = c;
    busca_camino(mapa, f_siguiente, c_siguiente, camino, num_lineas, num_columnas, profundidad + 1);
    f_siguiente = f;
    c_siguiente = c - 1;
    busca_camino(mapa, f_siguiente, c_siguiente, camino, num_lineas, num_columnas, profundidad + 1);
    f_siguiente = f - 1;
    c_siguiente = c;
    busca_camino(mapa, f_siguiente, c_siguiente, camino, num_lineas, num_columnas, profundidad + 1);
}

void busca_camino_con_atajo(std::vector<std::string> &mapa, int f, int c, std::vector<std::vector<int>> &camino, int &num_lineas, int &num_columnas, int profundidad, unsigned long long &total) {
    if (f < 0 || f >= num_lineas || c < 0 || c >= num_columnas || mapa[f][c] == '#' || camino[f][c] != profundidad) {
        return;
    }

    for (int i = 0; i < num_lineas ; ++i) {
        for (int j = 0; j < num_columnas; ++j) {
            int camino_atajo = abs(f - i) + abs(c - j);
            if (camino[i][j] > profundidad && camino_atajo <= 20) {
                int mejora = camino[i][j] - profundidad - camino_atajo;
                #ifdef LOG_CHECK
                    printf("Mejora derecha %i,%i: %i\n", f, c, mejora);
                #endif
                if (mejora >= MIN_MEJORA) {
                    total++;
                }
            }
        }
    }


    if (mapa[f][c] == 'E') {
        return;
    }

    int f_siguiente = f;
    int c_siguiente = c + 1;
    busca_camino_con_atajo(mapa, f_siguiente, c_siguiente, camino, num_lineas, num_columnas, profundidad + 1, total);
    f_siguiente = f + 1;
    c_siguiente = c;
    busca_camino_con_atajo(mapa, f_siguiente, c_siguiente, camino, num_lineas, num_columnas, profundidad + 1, total);
    f_siguiente = f;
    c_siguiente = c - 1;
    busca_camino_con_atajo(mapa, f_siguiente, c_siguiente, camino, num_lineas, num_columnas, profundidad + 1, total);
    f_siguiente = f - 1;
    c_siguiente = c;
    busca_camino_con_atajo(mapa, f_siguiente, c_siguiente, camino, num_lineas, num_columnas, profundidad + 1, total);
}

int main() {
    auto start = std::chrono::steady_clock::now();
    freopen(PATH_FICHERO, "r", stdin);
    string line;
    unsigned long long total = 0;
    int num_lineas = 0;
    int num_columnas = 0;


    vector<string> mapa;
    int s_fil = 0;
    int s_col = 0;
    int e_fil = 0;
    int e_col = 0;
    

    while(getline(cin, line))  {
        num_lineas++;
        #ifdef LOG_OPERACIONES_BASICAS
            printf("Linea %i: %s\n", num_lineas, line.c_str());
        #endif
        if (line.size() > 0) {
            if (num_columnas == 0) {
                num_columnas = line.size();
            }
            int s_col_tmp = line.find("S");
            if (s_col_tmp != string::npos) {
                s_col = s_col_tmp;
                s_fil = num_lineas - 1;
            }
            int e_col_tmp = line.find("E");
            if (e_col_tmp != string::npos) {
                e_col = e_col_tmp;
                e_fil = num_lineas - 1;
            }
            mapa.push_back(line);
        }
    }
    // cerrar el fichero
    fclose(stdin);
    std::cout << "Lectura fichero: " << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;


    #ifdef LOG_OPERACIONES_BASICAS
        std::cout << "Número de líneas: " << num_lineas << std::endl;
        std::cout << "Número de columnas: " << num_columnas << std::endl;
        std::cout << "S: " << s_fil << ", " << s_col << std::endl;
        std::cout << "E: " << e_fil << ", " << e_col << std::endl;
        for (const auto& row : mapa) {
            std::cout << row << std::endl;
        }
    #endif

    vector<vector<int>> camino(num_lineas, vector<int>(num_columnas, -1));

    int f = s_fil;
    int c = s_col;

    busca_camino(mapa, f, c, camino, num_lineas, num_columnas, 0);
    #ifdef LOG_OPERACIONES_BASICAS
        std::cout << "Camino encontrado:" << std::endl;
        for (int i = 0; i < num_lineas; ++i) {
            for (int j = 0; j < num_columnas; ++j) {
                if (camino[i][j] >= 0) {
                    std::cout << camino[i][j] % 10;
                } else {
                    std::cout << "#";
                }
            }
            std::cout << std::endl;
        }
    #endif
    busca_camino_con_atajo(mapa, f, c, camino, num_lineas, num_columnas, 0, total);

    std::cout << "Total: " << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;
    cout << "Total diseños correctos: " << total << endl;
    //SOLUCION: 
}


