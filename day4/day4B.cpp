#include <iostream>     // std::cout
#include <vector>       // std::vector
#include <string>
#include <algorithm>    // std::sort1

using namespace std;

#define LOG_OPERACIONES_BASICAS
#define LOG_OPERACIONES_BASICAS_MAS_MAS
#define LOG_OPERACIONES_BASICAS_SAM_SAM
#define LOG_OPERACIONES_BASICAS_MAS_SAM
#define LOG_OPERACIONES_BASICAS_SAM_MAS

#define LOG_TOTALES_INTERMEDIOS

int main()
{
    freopen("input.txt", "r", stdin);
    // freopen("error1.txt", "r", stdin);
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
    // cerrar el fichero
    fclose(stdin);
    
    int total_mas_mas = 0;
    int total_sam_sam = 0;
    int total_mas_sam = 0;
    int total_sam_mas = 0;
    for (int i = 0; i < v.size() - 2; i++) {
        for (int j = 0; j < v[i].size() - 2; j++) {
            if (v[i][j] == 'M' && v[i+1][j + 1] == 'A' && v[i + 2][j + 2] == 'S' &&
                v[i][j+2] == 'M' && v[i + 1][j + 1] == 'A' && v[i + 2][j] == 'S') {
                total_mas_mas++;
                #ifdef LOG_OPERACIONES_BASICAS_MAS_MAS
                  printf("Encontrado MAS MAS en la linea %d posicion %d con total %d\n", i, j, total_mas_mas);
                #endif
            }
            if (v[i][j] == 'S' && v[i + 1][j + 1] == 'A' && v[i+ 2][j + 2] == 'M' &&
                v[i][j+2] == 'S' && v[i + 1][j + 1] == 'A' && v[i+ 2][j] == 'M') {
                total_sam_sam++;
                #ifdef LOG_OPERACIONES_BASICAS_SAM_SAM
                  printf("Encontrado SAM SAM en la linea %d posicion %d con total %d\n", i, j, total_sam_sam);
                #endif
            }
            if (v[i][j] == 'M' && v[i + 1][j + 1] == 'A' && v[i+ 2][j + 2] == 'S' &&
                v[i][j+2] == 'S' && v[i + 1][j + 1] == 'A' && v[i+ 2][j] == 'M') {
                total_mas_sam++;
                #ifdef LOG_OPERACIONES_BASICAS_MAS_SAM
                  printf("Encontrado MAS SAM en la linea %d posicion %d con total %d\n", i, j, total_mas_sam);
                #endif
            }
            if (v[i][j] == 'S' && v[i + 1][j + 1] == 'A' && v[i+ 2][j + 2] == 'M' &&
                v[i][j+2] == 'M' && v[i + 1][j + 1] == 'A' && v[i+ 2][j] == 'S') {
                total_sam_mas++;
                #ifdef LOG_OPERACIONES_BASICAS_SAM_MAS
                  printf("Encontrado SAM MAS en la linea %d posicion %d con total %d\n", i, j, total_sam_mas);
                #endif
            }
        }
    }
    total += total_mas_mas + total_sam_sam + total_mas_sam + total_sam_mas;
    #ifdef LOG_TOTALES_INTERMEDIOS
        printf("Total de XMAS mas mas: %d, sam sam: %d mas sam: %d sam mas: %d con total %d\n", total_mas_mas, total_sam_sam, total_mas_sam, total_sam_mas, total);
    #endif

    printf("Total de XMAS: %d\n", total);
    //SOLUCION: 1992
}