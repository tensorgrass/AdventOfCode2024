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
// #define LOG_VERTICES

#define PATH_FICHERO "input.txt"
// #define PATH_FICHERO "testA1.txt"
// #define PATH_FICHERO "testA2.txt"
// #define PATH_FICHERO "testA3.txt"

struct Valla {
    int fila;
    int columna;
};

struct Nodo {
    int num_campos;
    vector<Valla> vallas;
};

void calcula_vallas(std::vector<std::vector<bool>> &mapa_pasado, int i, int j, Nodo &campo, std::vector<std::vector<char>> &mapa, int num_lines, int num_columns);

void guarda_vertice(Nodo &campo, int i, int j);

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

    vector<vector<bool>> mapa_pasado(num_lines, vector<bool>(num_columns, false));
    for (int i = 0; i < num_lines; i++) {
        for (int j = 0; j < num_columns; j++) {
            Nodo campo = {0};
            int direccion = 0;
            calcula_vallas(mapa_pasado, i, j, campo, mapa, num_lines, num_columns);
            #ifdef LOG_PARCIAL
                printf("Nodo %d %d %c: %d %d\n", i, j, mapa[i][j], campo.num_campos, campo.vallas.size());
            #endif
            total += campo.num_campos * campo.vallas.size();
        }
    }
 
        
    std::cout << "Total: " << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;
    cout << "Total vallas: " << total << endl;
    //SOLUCION: 814302
}

void calcula_vallas(std::vector<std::vector<bool>> &mapa_pasado, int i, int j, Nodo &campo, std::vector<std::vector<char>> &mapa, int num_lines, int num_columns)
{
    if (!mapa_pasado[i][j])
    {
        mapa_pasado[i][j] = true;
        campo.num_campos++;
        char valor = mapa[i][j];

        bool vertice1 = false;
        bool vertice2 = false;
        bool vertice3 = false;
        bool vertice4 = false;

        if (i == 0 || valor != mapa[i-1][j]) {
            if (j == 0 || valor != mapa[i][j-1]) {
                vertice1 = true;
            }
            else if (i > 0 && j > 0 && mapa[i][j-1] == mapa[i-1][j-1]) {
                vertice1 = true;
            }

            if (j == num_columns - 1 || valor != mapa[i][j+1]) {
                vertice2 = true;
            }
            else if (i > 0 && j < num_columns - 1 && mapa[i][j+1] == mapa[i-1][j+1]) {
                vertice2 = true;
            }
        }

        if (i == num_lines - 1 || valor != mapa[i + 1][j]) {
            if (j == 0 || valor != mapa[i][j-1]) {
                vertice4 = true;
            }
            else if (i < num_lines - 1 && j > 0 && mapa[i][j-1] == mapa[i+1][j-1]) {
                vertice4 = true;
            }

            if (j == num_columns - 1 || valor != mapa[i][j+1]) {
                vertice3 = true;
            }
            else if (i < num_lines -1 && j < num_columns - 1 && mapa[i][j+1] == mapa[i+1][j+1]) {
                vertice3 = true;
            }
        }

        if (j == 0 || valor != mapa[i][j-1]) {
            // if (i == 0 || valor != mapa[i-1][j]) {//No hace falta ya esta verificado con anterioridad
            //     vertice1 = true;
            // }
            // else 
            if (i > 0 && j > 0 && mapa[i-1][j] == mapa[i-1][j-1]) {
                vertice1 = true;
            }

            // if (i == num_lines - 1 || valor != mapa[i + 1][j]) { //No hace falta ya esta verificado con anterioridad
            //     vertice4 = true;
            // }
            // else 
            if (i < num_lines - 1 && j > 0 && mapa[i + 1][j] == mapa[i+1][j-1]) {
                vertice4 = true;
            }
        }

        if (j == num_columns - 1 || valor != mapa[i][j+1]) {
            // if (i == 0 || valor != mapa[i-1][j]) {//No hace falta ya esta verificado con anterioridad
            //     vertice2 = true;
            // }
            // else 
            if (i > 0 && j < num_columns - 1 && mapa[i-1][j] == mapa[i-1][j+1]) {
                vertice2 = true;
            }

            // if (i == num_lines - 1 || valor != mapa[i + 1][j]) {//No hace falta ya esta verificado con anterioridad
            //     vertice3 = true;
            // }
            // else 
            if (i < num_lines - 1 && j < num_columns - 1 && mapa[i + 1][j] == mapa[i+1][j+1]) {
                vertice3 = true;
            }
        }

        if (vertice1) {
            guarda_vertice(campo, i, j);
        }
        if (vertice2) {
            guarda_vertice(campo, i, j + 1);
        }
        if (vertice3) {
            guarda_vertice(campo, i + 1, j + 1);
        }
        if (vertice4) {
            guarda_vertice(campo, i + 1, j);
        }


        if (i > 0 && mapa[i - 1][j] == valor) {
            calcula_vallas(mapa_pasado, i - 1, j, campo, mapa, num_lines, num_columns);
        }

        if (i < num_lines - 1 && mapa[i + 1][j] == valor) {
            calcula_vallas(mapa_pasado, i + 1, j, campo, mapa, num_lines, num_columns);
        }

        if (j > 0 && mapa[i][j - 1] == valor) {
            calcula_vallas(mapa_pasado, i, j - 1, campo, mapa, num_lines, num_columns);
        }

        if (j < num_columns - 1 && mapa[i][j + 1] == valor) {
            calcula_vallas(mapa_pasado, i, j + 1, campo, mapa, num_lines, num_columns);
        }
    }
}

void guarda_vertice(Nodo &campo, int i, int j)
{
    bool valla_duplicada = false;
    for (int m = 0; m < campo.vallas.size(); m++)
    {
        if (campo.vallas[m].fila == i && campo.vallas[m].columna == j)
        {
            valla_duplicada = true;
            break;
        }
    }
    if (!valla_duplicada)
    {
        Valla valla = {i, j};
        campo.vallas.push_back(valla);
    }
}
