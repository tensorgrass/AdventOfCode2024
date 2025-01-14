
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

struct Operacion {
    string op1;
    string op2;
    string op3;
    string operacion;
};

int main()
{
    auto start = std::chrono::steady_clock::now();
    freopen(PATH_FICHERO, "r", stdin);
    string line;
    unsigned long long total = 0;

    int num_filas = 0;
    int tipo = 0;
    unordered_map<string, bool> mapa;
    vector<Operacion> operaciones;
    while(getline(cin, line))  {
        num_filas++;
        #ifdef LOG_OPERACIONES_BASICAS
            cout << "Linea " << num_filas << ": " << line << endl;
        #endif
        if (line.size() == 0) {
            tipo++;
        }
        else {
            if (tipo == 0) {
                // mapa[line.substr(0, line.find(" "))] = true;
                mapa[line.substr(0, 3)] = line.substr(5, 1) == "1";
            }
            if (tipo == 1) {

                int a = 0;
                int b = 8;
                int c = 15;
                string operacion = line.substr(4, 3);
                if (operacion == "OR ") {
                    b--;
                    c--;
                }
                string op1 = line.substr(a, 3);
                string op2 = line.substr(b, 3);
                string op3 = line.substr(c, 3);
                #ifdef LOG_OPERACIONES_BASICAS
                    cout << "Operacion: " << operacion << " " << op1 << " " << op2 << " " << op3 << endl;
                #endif
                Operacion ope = {op1, op2, op3, operacion};
                operaciones.push_back(ope);
                if (mapa.find(op3) == mapa.end()) {
                    mapa[op3] = false;
                }
                // if (operacion == "AND") {
                //     mapa[op3] = mapa[op1] && mapa[op2];
                // }
                // else if (operacion == "OR ") {
                //     mapa[op3] = mapa[op1] || mapa[op2];
                // }
                // else {
                //     mapa[op3] = mapa[op1] != mapa[op2];
                // }
                // #ifdef LOG_OPERACIONES_BASICAS
                //     cout << "Resultado: " << mapa[op3] << endl;
                // #endif
            }
        }
    }
    // cerrar el fichero
    fclose(stdin);
    std::cout << "Lectura fichero: " << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;

    bool ordenado = false;
    while (!ordenado) {
        ordenado = true;
        for (int i = 0; i < operaciones.size() - 1; i++) {
            Operacion operacion1 = operaciones[i];
            for (int j = i + 1; j < operaciones.size(); j++) {
                Operacion operacion2 = operaciones[j];
                if (operacion1.op1 == operacion2.op3 || operacion1.op2 == operacion2.op3) {
                    swap(operaciones[i], operaciones[j]);
                    ordenado = false;
                    i = j - 1;
                }
            }
        }
    }

    #ifdef LOG_OPERACIONES_BASICAS
    for (const auto& operacion : operaciones) {
        cout << "Operacion ordenada: " << operacion.operacion << " " << operacion.op1 << " " << operacion.op2 << " " << operacion.op3 << endl;
    }
    #endif
        
    for (Operacion operacion : operaciones) {
        if (operacion.operacion == "AND") {
            mapa[operacion.op3] = mapa[operacion.op1] && mapa[operacion.op2];
        }
        else if (operacion.operacion == "OR ") {
            mapa[operacion.op3] = mapa[operacion.op1] || mapa[operacion.op2];
        }
        else {
            mapa[operacion.op3] = mapa[operacion.op1] != mapa[operacion.op2];
        }
        #ifdef LOG_OPERACIONES_BASICAS
            cout << "Resultado: " << mapa[operacion.op3] << endl;
        #endif
    }

    #ifdef LOG_OPERACIONES_BASICAS
    for (const auto& pair : mapa) {
        cout << pair.first << ": " << (pair.second ? "true" : "false") << endl;
    }
    #endif

    cout << "----RESULTADO----" << endl;
    vector<pair<string, bool>> sorted_map(mapa.begin(), mapa.end());
    sort(sorted_map.rbegin(), sorted_map.rend());

    for (const auto& pair : sorted_map) {
        cout << pair.first << ": " << (pair.second ? "true" : "false") << endl;
    }

    vector <string> binary_value;
    for (const auto& pair : sorted_map) {
        if (pair.first[0] == 'z') {
            binary_value.push_back(pair.second ? "1" : "0");
        }
    }

    cout << "Binary value: ";
    for (const auto& bit : binary_value) {
        cout << bit;
    }
    cout << endl;

    string binary_string;
    for (const auto& bit : binary_value) {
        binary_string += bit;
    }
    unsigned long long decimal_value = std::strtoull(binary_string.c_str(), nullptr, 2);
    total = decimal_value;

    std::cout << "Total: " << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;
    cout << "Resultado: " << total << endl;
    //SOLUCION: 1437
}


