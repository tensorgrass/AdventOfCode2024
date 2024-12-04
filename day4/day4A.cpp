#include <iostream>     // std::cout
#include <vector>       // std::vector
#include <string>
#include <algorithm>    // std::sort1

using namespace std;

#define LOG_OPERACIONES_BASICAS
#define LOG_OPERACIONES_BASICAS_HORIZONTALES
#define LOG_OPERACIONES_BASICAS_VERTICALES
#define LOG_OPERACIONES_BASICAS_DIAGONALES_ABAJO
#define LOG_OPERACIONES_BASICAS_DIAGONALES_ARRIBA

#define LOG_TOTALES_INTERMEDIOS

int main()
{
    freopen("input.txt", "r", stdin);
    // freopen("error41.txt", "r", stdin);
    string line;
    int total = 0;
    
    vector<string> v;    
    while(getline(cin, line))
    {
        #ifdef LOG_OPERACIONES_BASICAS
            printf("Linea: %s\n", line.c_str());
        #endif
        v.push_back(line);
    }
    // close the file
    fclose(stdin);
    
    int total_horizontal = 0;
    int total_horizontal_invertido = 0;
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v[i].size() - 3; j++) {
            if (v[i][j] == 'X' && v[i][j + 1] == 'M' && v[i][j + 2] == 'A' && v[i][j + 3] == 'S') {
                total_horizontal++;
                #ifdef LOG_OPERACIONES_BASICAS_HORIZONTALES
                  printf("Encontrado XMAS en la linea %d posicion %d con total %d\n", i, j, total);
                #endif
            }
            if (v[i][j] == 'S' && v[i][j + 1] == 'A' && v[i][j + 2] == 'M' && v[i][j + 3] == 'X') {
                total_horizontal_invertido++;
                #ifdef LOG_OPERACIONES_BASICAS_HORIZONTALES
                  printf("Encontrado SAMX en la linea %d posicion %d con total %d\n", i, j, total);
                #endif
            }
        }
    }
    total += total_horizontal + total_horizontal_invertido;
    #ifdef LOG_TOTALES_INTERMEDIOS
        printf("Total de XMAS horizontal: %d, horizontal invertido: %d con total %d\n", total_horizontal, total_horizontal_invertido, total);
    #endif


    int total_vertical = 0;
    int total_vertical_invertido = 0;
    for (int i = 0; i < v.size() - 3; i++) {
        for (int j = 0; j < v[i].size(); j++) {
            if (v[i][j] == 'X' && v[i + 1][j] == 'M' && v[i + 2][j] == 'A' && v[i + 3][j] == 'S') {
                total_vertical++;
                #ifdef LOG_OPERACIONES_BASICAS_VERTICALES
                  printf("Encontrado XMAS en la linea %d posicion %d con total %d\n", i, j, total);
                #endif
            }
            if (v[i][j] == 'S' && v[i + 1][j] == 'A' && v[i + 2][j] == 'M' && v[i + 3][j] == 'X') {
                total_vertical_invertido++;
                #ifdef LOG_OPERACIONES_BASICAS_VERTICALES
                  printf("Encontrado SAMX en la linea %d posicion %d con total %d\n", i, j, total);
                #endif
            }
        }
    }
    total += total_vertical + total_vertical_invertido;
    #ifdef LOG_TOTALES_INTERMEDIOS
        printf("Total de XMAS vertical: %d, vertical invertido: %d con total %d\n", total_vertical, total_vertical_invertido, total);
    #endif

    int total_diagonal_abajo = 0;
    int total_diagonal_abajo_invertido = 0;
    for (int i = 0; i < v.size() - 3; i++) {
        for (int j = 0; j < v[i].size() - 3; j++) {
            if (v[i][j] == 'X' && v[i + 1][j + 1] == 'M' && v[i + 2][j + 2] == 'A' && v[i + 3][j + 3] == 'S') {
                total_diagonal_abajo++;
                #ifdef LOG_OPERACIONES_BASICAS_DIAGONALES_ABAJO
                  printf("Encontrado XMAS en la linea %d posicion %d con total %d\n", i, j, total);
                #endif
            }
            if (v[i][j] == 'S' && v[i + 1][j + 1] == 'A' && v[i + 2][j + 2] == 'M' && v[i + 3][j + 3] == 'X') {
                total_diagonal_abajo_invertido++;
                #ifdef LOG_OPERACIONES_BASICAS_DIAGONALES_ABAJO
                  printf("Encontrado SAMX en la linea %d posicion %d con total %d\n", i, j, total);
                #endif
            }
        }
    }
    total += total_diagonal_abajo + total_diagonal_abajo_invertido;
    #ifdef LOG_TOTALES_INTERMEDIOS
        printf("Total de XMAS diagonal abajo: %d, diagonal abajo invertido: %d con total %d\n", total_diagonal_abajo, total_diagonal_abajo_invertido, total);
    #endif

    int total_diagonal_arriba = 0;
    int total_diagonal_arriba_invertido = 0;
    for (int i = 3; i < v.size(); i++) {
        for (int j = 0; j < v[i].size() - 3; j++) {
            if (v[i][j] == 'X' && v[i-1][j+1] == 'M' && v[i-2][j+2] == 'A' && v[i-3][j+3] == 'S') {
                total_diagonal_arriba++;
                #ifdef LOG_OPERACIONES_BASICAS_DIAGONALES_ARRIBA
                  printf("Encontrado XMAS en la linea %d posicion %d con total %d\n", i, j, total);
                #endif
            }
            if (v[i][j] == 'S' && v[i-1][j+1] == 'A' && v[i-2][j+2] == 'M' && v[i-3][j+3] == 'X') {
                total_diagonal_arriba_invertido++;
                #ifdef LOG_OPERACIONES_BASICAS_DIAGONALES_ARRIBA
                  printf("Encontrado SAMX en la linea %d posicion %d con total %d\n", i, j, total);
                #endif
            }
        }
    }
    total += total_diagonal_arriba + total_diagonal_arriba_invertido;
    #ifdef LOG_TOTALES_INTERMEDIOS
        printf("Total de XMAS diagonal arriba: %d, diagonal arriba invertido: %d con total %d\n", total_diagonal_arriba, total_diagonal_arriba_invertido, total);
    #endif

    printf("Total de XMAS: %d\n", total);
    //SOLUCION 2571
}