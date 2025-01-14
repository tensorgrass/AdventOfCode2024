
#include <iostream>     // std::cout
#include <vector>       // std::vector
#include <string>
#include <chrono>       // std::chrono
#include <cstdlib>      // std::strtoull
#include <assert.h>
#include <unordered_map>
#include <algorithm>    // std::sort

using namespace std;


#define LOG_OPERACIONES_BASICAS
#define LOG_INTERMEDIO

#define PATH_FICHERO "input.txt"
// #define PATH_FICHERO "testA1.txt"
// #define PATH_FICHERO "testA2.txt"


int main()
{
    auto start = std::chrono::steady_clock::now();
    freopen(PATH_FICHERO, "r", stdin);
    string line;
    unsigned long long total = 0;

    int num_fila = 0;
    int num_columnas = 0;

    vector<vector<int>> cerraduras;
    int num_cerradura = -1;
    vector<vector<int>> llaves;
    int num_llave = -1;
    bool is_llave = false;
    while(getline(cin, line))  {
        num_fila++;
        #ifdef LOG_OPERACIONES_BASICAS
            std::cout << "Linea " << num_fila << ": " << line << endl;
        #endif
        if (line.length() == 0) {
            num_fila = 0;
        }
        else {
            if (num_fila == 1) {
                vector<int> c = {0,0,0,0,0};
                if (line[0] == '#') {
                    is_llave = false;
                    num_cerradura++;
                    cerraduras.push_back(c);
                }
                else {
                    is_llave = true;
                    num_llave++;
                    llaves.push_back(c);
                }
            }
            else if (num_fila == 7) {
                continue;
            }
            else {
                for (int c = 0; c < line.length(); c++) {
                    if (line[c] == '#') {
                        if (!is_llave) {
                            cerraduras[num_cerradura][c]++;
                        }
                        else {
                            llaves[num_llave][c]++;
                        }
                    }
                }
            }
        }
    }
    // cerrar el fichero
    fclose(stdin);
    std::cout << "Lectura fichero: " << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;

    #ifdef LOG_OPERACIONES_BASICAS
        std::cout << "Cerraduras" << endl;
        for (int i = 0; i < cerraduras.size(); i++) {
            for (int j = 0; j < cerraduras[i].size(); j++) {
                std::cout << cerraduras[i][j] << " ";
            }
            std::cout << endl;
        }
        std::cout << "Llaves" << endl;
        for (int i = 0; i < llaves.size(); i++) {
            for (int j = 0; j < llaves[i].size(); j++) {
                std::cout << llaves[i][j] << " ";
            }
            std::cout << endl;
        }
    #endif

    for (vector<int> cerradura : cerraduras) {
        for (vector<int> llave : llaves) {
            bool overlap = false;
            for (int i = 0; i < 5; i++) {
                if (cerradura[i] + llave[i] > 5) {
                    overlap = true;
                    break;
                }
            }
            if (!overlap) {
                total++;
            }
        }
    }
            

    std::cout << "Total: " << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;
    std::cout << "Resultado: " << total << endl;
    //SOLUCION: 1437
}


