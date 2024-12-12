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
// #define LOG_VALLAS
// #define LOG_VALLAS_ENCONTRADAS

#define PATH_FICHERO "input.txt"
// #define PATH_FICHERO "testA1.txt"
// #define PATH_FICHERO "testA2.txt"
// #define PATH_FICHERO "testA3.txt"


struct Nodo {
    int num_campos;
    vector<int> vallas;
};

struct Valla {
    int fila;
    int columna;
};

void calcula_vallas(std::vector<std::vector<bool>> &mapa_pasado, int i, int j, Nodo &campo, std::vector<std::vector<char>> &mapa, int num_lines, int num_columns, vector<vector<Valla>> &vallas);

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

    vector<vector<Valla>> vallas;
    int num_valla = -1;
    for (int i = 0; i < num_lines; i++) {
        #ifdef LOG_VALLAS
            printf("Fila superior %d\n", i);
        #endif
        for (int j = 0; j < num_columns; j++) {
            bool tiene_valla = false;
            bool nueva_valla = false;
            //Primera fila
            if (i == 0) {
                tiene_valla = true;
                if (j == 0 || mapa[i][j] != mapa[i][j - 1]) {
                    nueva_valla = true;
                }
            }
            // Diferente al superior
            else if (mapa[i][j] != mapa[i - 1][j]) {
                tiene_valla = true;
                //es el primero
                if (j == 0) {
                    nueva_valla = true;
                }
                // diferente al anterior
                else if (mapa[i][j] != mapa[i][j - 1]) {
                    nueva_valla = true;
                }
                //igual al anterior y el anterior tiene el superior igual
                else if (mapa[i][j - 1] == mapa[i - 1][j - 1]) {
                    nueva_valla = true;
                }
            }

            if (tiene_valla) {
                Valla v1 = {i, j};
                if (nueva_valla) {
                    vector<Valla> valla;
                    num_valla++;
                    valla.push_back(v1);
                    vallas.push_back(valla);
                    #ifdef LOG_VALLAS
                        printf("Valla nueva %d %d num valla %d\n", i, j, num_valla);
                    #endif
                }
                else {
                    vallas[num_valla].push_back(v1);
                    #ifdef LOG_VALLAS
                        printf("Valla anterior%d %d num valla %d\n", i, j, num_valla);
                    #endif
                }
            }
            else {
                #ifdef LOG_VALLAS
                    printf("No valla %d %d\n", i, j);
                #endif
            }
        }
    }

    for (int i = 0; i < num_lines; i++) {
        #ifdef LOG_VALLAS
            printf("Fila inferior %d\n", i);
        #endif
        for (int j = 0; j < num_columns; j++) {
            bool tiene_valla = false;
            bool nueva_valla = false;
            //Ultima fila
            if (i == num_lines - 1) {
                tiene_valla = true;
                if (j == 0 || mapa[i][j] != mapa[i][j - 1]) {
                    nueva_valla = true;
                }
            }
            // Diferente al superior
            else if (mapa[i][j] != mapa[i + 1][j]) {
                tiene_valla = true;
                //es el primero
                if (j == 0) {
                    nueva_valla = true;
                }
                // diferente al anterior
                else if (mapa[i][j] != mapa[i][j - 1]) {
                    nueva_valla = true;
                }
                //igual al anterior y el anterior tiene el superior igual
                else if (mapa[i][j - 1] == mapa[i + 1][j - 1]) {
                    nueva_valla = true;
                }
            }

            if (tiene_valla) {
                Valla v1 = {i, j};
                if (nueva_valla) {
                    vector<Valla> valla;
                    num_valla++;
                    valla.push_back(v1);
                    vallas.push_back(valla);
                    #ifdef LOG_VALLAS
                        printf("Valla nueva %d %d num valla %d\n", i, j, num_valla);
                    #endif
                }
                else {
                    vallas[num_valla].push_back(v1);
                    #ifdef LOG_VALLAS
                        printf("Valla anterior%d %d num valla %d\n", i, j, num_valla);
                    #endif
                }
            }
            else {
                #ifdef LOG_VALLAS
                    printf("No valla %d %d\n", i, j);
                #endif
            }
        }
    }

    for (int j = 0; j < num_columns; j++) {
        #ifdef LOG_VALLAS
            printf("Columna izquierda %d\n", j);
        #endif
        for (int i = 0; i < num_lines; i++) {
            bool tiene_valla = false;
            bool nueva_valla = false;
            //Primera columna
            if (j == 0) {
                tiene_valla = true;
                if (i == 0 || mapa[i][j] != mapa[i - 1][j]) {
                    nueva_valla = true;
                }
            }
            // Diferente al anterior
            else if (mapa[i][j] != mapa[i][j - 1]) {
                tiene_valla = true;
                //es la primera
                if (i == 0) {
                    nueva_valla = true;
                }
                // diferente al superior
                else if (mapa[i][j] != mapa[i - 1][j]) {
                    nueva_valla = true;
                }
                //igual al superior y el superior tiene el anterior igual
                else if (mapa[i - 1][j] == mapa[i - 1][j - 1]) {
                    nueva_valla = true;
                }
            }

            if (tiene_valla) {
                Valla v1 = {i, j};
                if (nueva_valla) {
                    vector<Valla> valla;
                    num_valla++;
                    valla.push_back(v1);
                    vallas.push_back(valla);
                    #ifdef LOG_VALLAS
                        printf("Valla nueva %d %d\n", i, j);
                    #endif
                }
                else {
                    vallas[num_valla].push_back(v1);
                    #ifdef LOG_VALLAS
                        printf("Valla anterior%d %d\n", i, j);
                    #endif
                }
            }
            else {
                #ifdef LOG_VALLAS
                    printf("No valla %d %d\n", i, j);
                #endif
            }
        }
    }

    for (int j = 0; j < num_columns; j++) {
        #ifdef LOG_VALLAS
            printf("Columna derecha %d\n", j);
        #endif
        for (int i = 0; i < num_lines; i++) {
            bool tiene_valla = false;
            bool nueva_valla = false;
            //Primera columna
            if (j == num_columns - 1) {
                tiene_valla = true;
                if (i == 0 || mapa[i][j] != mapa[i - 1][j]) {
                    nueva_valla = true;
                }
            }
            // Diferente al anterior
            else if (mapa[i][j] != mapa[i][j + 1]) {
                tiene_valla = true;
                //es la primera
                if (i == 0) {
                    nueva_valla = true;
                }
                // diferente al superior
                else if (mapa[i][j] != mapa[i - 1][j]) {
                    nueva_valla = true;
                }
                //igual al superior y el superior tiene el anterior igual
                else if (mapa[i - 1][j] == mapa[i - 1][j + 1]) {
                    nueva_valla = true;
                }
            }

            if (tiene_valla) {
                Valla v1 = {i, j};
                if (nueva_valla) {
                    vector<Valla> valla;
                    num_valla++;
                    valla.push_back(v1);
                    vallas.push_back(valla);
                    #ifdef LOG_VALLAS
                        printf("Valla nueva %d %d\n", i, j);
                    #endif
                }
                else {
                    vallas[num_valla].push_back(v1);
                    #ifdef LOG_VALLAS
                        printf("Valla anterior%d %d\n", i, j);
                    #endif
                }
            }
            else {
                #ifdef LOG_VALLAS
                    printf("No valla %d %d\n", i, j);
                #endif
            }
        }
    }
    std::cout << "Generacion estructura: " << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;

    #ifdef LOG_VALLAS_ENCONTRADAS
        printf("\nINICIO PROCESO\n\n");
    #endif
    for (int i = 0; i < num_lines; i++) {
        for (int j = 0; j < num_columns; j++) {
            Nodo campo = {0};
            calcula_vallas(mapa_pasado, i, j, campo, mapa, num_lines, num_columns, vallas);

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

void calcula_vallas(std::vector<std::vector<bool>> &mapa_pasado, int i, int j, Nodo &campo, std::vector<std::vector<char>> &mapa, int num_lines, int num_columns, vector<vector<Valla>> &vallas)
{
    if (!mapa_pasado[i][j])
    {
        mapa_pasado[i][j] = true;
        campo.num_campos++;
        int subtotal = 0;
        char valor = mapa[i][j];
        for (int k = 0; k < vallas.size(); k++) {
            for (int l = 0; l < vallas[k].size(); l++) {
                if (vallas[k][l].fila == i && vallas[k][l].columna == j) {
                    bool valla_encontrada = false;
                    for (int m = 0; m < campo.vallas.size(); m++) {
                        if (campo.vallas[m] == k) {
                            valla_encontrada = true;
                            break;
                        }
                    }
                    if (!valla_encontrada) {
                        #ifdef LOG_VALLAS_ENCONTRADAS
                            printf("Valla encontrada %d %d numero valla: %d\n", i, j, k);
                        #endif
                        campo.vallas.push_back(k);
                    }
                    break;
                }
            }
        }


        if (i > 0) {
            if (mapa[i - 1][j] == valor) {
                calcula_vallas(mapa_pasado, i - 1, j, campo, mapa, num_lines, num_columns, vallas);
            }
        }

        if (i < num_lines - 1) {
            if (mapa[i + 1][j] == valor) {
                calcula_vallas(mapa_pasado, i + 1, j, campo, mapa, num_lines, num_columns, vallas);
            }
        }

        if (j > 0) {
            if (mapa[i][j - 1] == valor) {
                calcula_vallas(mapa_pasado, i, j - 1, campo, mapa, num_lines, num_columns, vallas);
            }
        }

        if (j < num_columns - 1) {
            if (mapa[i][j + 1] == valor) {
                calcula_vallas(mapa_pasado, i, j + 1, campo, mapa, num_lines, num_columns, vallas);
            }
        }
    }
}
