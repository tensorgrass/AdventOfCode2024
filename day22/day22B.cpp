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
    map<string, int> secuencias;
    vector<map<string, int>> secuencias_por_vendedor;
    while(getline(cin, line))  {
        num_lineas++;
        #ifdef LOG_OPERACIONES_BASICAS
            printf("Linea %i: %s\n", num_lineas, line.c_str());
        #endif
        if (line.size() > 0) {
            vector<SecretBanana> secret_bananas;
            unsigned long long secret_number = std::stoull(line);
            for (int i = 0; i < 2000; i++) {
                int ini_banana = secret_number % 10;
                secret_number = calcular_numero_secreto(secret_number);
                #ifdef LOG_INTERMEDIO
                    cout << "secret_number: " << secret_number << endl;
                #endif
                int fin_banana = secret_number % 10;
                secret_bananas.push_back({secret_number, fin_banana - ini_banana});
               
            }
            // total += secret_number;

            set<string> secuencias_vendedor;
            for (int i = 0; i < secret_bananas.size() - 3; i++) {
                string key = "";
                for (int j = 0; j < 4; j++) {
                    key += to_string(secret_bananas[i + j].num_bananas) + ",";
                }


                if (secuencias_vendedor.find(key) == secuencias_vendedor.end()) {
                    secuencias_vendedor.insert(key);
                    if (secuencias.find(key) == secuencias.end()) {
                        secuencias[key] = secret_bananas[i + 3].secret_number % 10;
                    }
                    else {
                        secuencias[key] += secret_bananas[i + 3].secret_number % 10;
                    }
                }

            }
            // secuencias_por_vendedor.push_back(secuencias_vendedor);


        }
    }
    // cerrar el fichero
    fclose(stdin);
    std::cout << "Lectura fichero: " << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;

    #ifdef LOG_CHECK
        cout << "Num secuencias: " << secuencias.size() << endl; 
        cout << "Num secuencias por vendedor: " << secuencias_por_vendedor.size() << endl;
    #endif

    string max_key = "";
    for (const auto& pair : secuencias) {
        if (pair.second > total) {
            total = pair.second;
            max_key = pair.first;
        }
    }

    cout << "Max key: " << max_key << " with value: " << total << endl;

    std::cout << "Total: " << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;
    cout << "Total diseños correctos: " << total << endl;
    //SOLUCION: 1582
    
}


