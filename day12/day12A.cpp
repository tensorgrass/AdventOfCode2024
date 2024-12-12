#include <iostream>     // std::cout
#include <vector>       // std::vector
#include <string>
#include <chrono>       // std::chrono
#include <cstdlib>      // std::strtoull

using namespace std;

// #define LOG_OPERACIONES_BASICAS
// #define LOG_ERROR_ENCONTRADO
// #define LOG_ENCONTRADO
// #define LOG_PARCIAL
// #define LOG_CALCULOS

#define PATH_FICHERO "input.txt"
// #define PATH_FICHERO "testA1.txt"
// #define PATH_FICHERO "testA2.txt"
// #define PATH_FICHERO "testA3.txt"

#define PROFUNDIDAD 25

struct Nodo {
    int num_campos;
    int num_vallas;
};

void calcula_vallas(std::vector<std::vector<bool>> &mapa_pasado, int i, int j, Nodo &campo, std::vector<std::vector<char>> &mapa, int num_lines, int num_columns);

int main()
{
    auto start = std::chrono::steady_clock::now();
    freopen(PATH_FICHERO, "r", stdin);
    string line;
    unsigned long long total = 0;
    int num_lines = 0;
    int num_columns = 0;
    vector<vector<char>> mapa;
    
    while(getline(cin, line))  {
        num_lines++;
        #ifdef LOG_OPERACIONES_BASICAS
            printf("Linea %i: %s\n", num_lines, line.c_str());
        #endif
        if (num_columns == 0) {
            num_columns = line.size();
        } 
        vector<char> mapa_columnas;

        for (int i = 0; i < num_columns; i++) {
            mapa_columnas.push_back(line[i]);
        }
        mapa.push_back(mapa_columnas);
    }
    vector<vector<bool>> mapa_pasado(num_lines, vector<bool>(num_columns, false));

    // cerrar el fichero
    fclose(stdin);
    std::cout << "Lectura fichero: " << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;
    #ifdef LOG_OPERACIONES_BASICAS
        printf("Numero de lineas: %i Numero de columnas: %i, registro en mapa %d\n", num_lines, num_columns, mapa.size());
        
        for (int i = 0; i < num_lines; i++) {
            for (int j = 0; j < num_columns; j++) {
                printf("%c", mapa[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    #endif

    for (int i = 0; i < num_lines; i++) {
        for (int j = 0; j < num_columns; j++) {
            Nodo campo = {0, 0};
            int direccion = 0;
            calcula_vallas(mapa_pasado, i, j, campo, mapa, num_lines, num_columns);
            #ifdef LOG_PARCIAL
                printf("Nodo %d %d %c: %d %d\n", i, j, mapa[i][j], campo.num_campos, campo.num_vallas);
            #endif
            total += campo.num_campos * campo.num_vallas;
        }
    }
 
        
    std::cout << "Total: " << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;
    cout << "Total vallas: " << total << endl;
    //SOLUCION: 203609
}

void calcula_vallas(std::vector<std::vector<bool>> &mapa_pasado, int i, int j, Nodo &campo, std::vector<std::vector<char>> &mapa, int num_lines, int num_columns)
{
    if (!mapa_pasado[i][j])
    {
        mapa_pasado[i][j] = true;
        campo.num_campos++;
        int subtotal = 0;
        char valor = mapa[i][j];

        if (i > 0) {
            if (mapa[i - 1][j] != valor) {
                campo.num_vallas++;
            }
            else {
                calcula_vallas(mapa_pasado, i - 1, j, campo, mapa, num_lines, num_columns);
            }
        }
        else {
            campo.num_vallas++;
        }

        if (i < num_lines - 1) {
            if (mapa[i + 1][j] != valor) {
                campo.num_vallas++;
            }
            else {
                calcula_vallas(mapa_pasado, i + 1, j, campo, mapa, num_lines, num_columns);
            }
        }
        else {
            campo.num_vallas++;
        }

        if (j > 0) {
            if (mapa[i][j - 1] != valor) {
                campo.num_vallas++;
            }
            else {
                calcula_vallas(mapa_pasado, i, j - 1, campo, mapa, num_lines, num_columns);
            }
        }
        else {
            campo.num_vallas++;
        }

        if (j < num_columns - 1) {
            if (mapa[i][j + 1] != valor) {
                campo.num_vallas++;
            }
            else {
                calcula_vallas(mapa_pasado, i, j + 1, campo, mapa, num_lines, num_columns);
            }
        }
        else {
            campo.num_vallas++;
        }
    }
}
