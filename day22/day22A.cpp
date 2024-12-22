#include <iostream>     // std::cout
#include <vector>       // std::vector
#include <string>
#include <chrono>       // std::chrono
#include <cstdlib>      // std::strtoull
#include <algorithm>    // std::sort
#include <unordered_map>
#include <map>
#include <set>

using namespace std;

// #define LOG_OPERACIONES_BASICAS
// #define LOG_ERROR_ENCONTRADO
// #define LOG_INTERMEDIO
#define LOG_CHECK

//input
#define PATH_FICHERO "input.txt"
// #define PATH_FICHERO "testA1.txt"
// #define PATH_FICHERO "testA2.txt"

#define PRUNE_VALUE 16777216

struct SecretBanana{
    unsigned long long secret_number;
    int num_bananas;
};

unsigned long long calcular_numero_secreto(unsigned long long &secret_number)
{
    secret_number = (secret_number ^ (secret_number * 64)) % PRUNE_VALUE;
    secret_number = (secret_number ^ (secret_number / 32)) % PRUNE_VALUE;
    secret_number = (secret_number ^ (secret_number * 2048)) % PRUNE_VALUE;
    return secret_number;
}

int main() {
    auto start = std::chrono::steady_clock::now();
    freopen(PATH_FICHERO, "r", stdin);
    string line;
    unsigned long long total = 0;
    int num_lineas = 0;
    int num_columnas = 0;

    vector<int> numeros;
    set<string> secuencias;
    while(getline(cin, line))  {
        num_lineas++;
        #ifdef LOG_OPERACIONES_BASICAS
            printf("Linea %i: %s\n", num_lineas, line.c_str());
        #endif
        if (line.size() > 0) {
            unsigned long long secret_number = std::stoull(line);
            for (int i = 0; i < 2000; i++) {
                secret_number = calcular_numero_secreto(secret_number);
                #ifdef LOG_INTERMEDIO
                    cout << "secret_number: " << secret_number << endl;
                #endif               
            }
            total += secret_number;
        }
    }
    // cerrar el fichero
    fclose(stdin);
    std::cout << "Lectura fichero: " << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;

    std::cout << "Total: " << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;
    cout << "Total diseños correctos: " << total << endl;
    //SOLUCION: 13429191512
}


