#include <iostream>     // std::cout
#include <vector>       // std::vector
#include <string>
#include <chrono>       // std::chrono
#include "day7B_recursiva.h"

using namespace std;

// #define LOG_OPERACIONES_BASICAS
// #define LOG_ERROR_ENCONTRADO
// #define LOG_CALCULOS
// #define LOG_ENCONTRADO
int main()
{
auto start = std::chrono::steady_clock::now();
    freopen("input.txt", "r", stdin);
    // freopen("testB1.txt", "r", stdin);
    string line;
    unsigned long long total = 0;
    int num_lines = 0;

    while(getline(cin, line))  {
        num_lines++;
        #ifdef LOG_OPERACIONES_BASICAS
            printf("Linea %i: %s\n", num_lines, line.c_str());
        #endif
        vector<long> values;
        bool is_value = false;
        long num_values = 0;
        unsigned long long test_value = 0;
        for (int i = 0; i < line.size(); i++) {
            if (line[i] == ':') {
                //substring hasta i - 1 y convertir a numero
                test_value = std::stoull(line.substr(0,i));
                is_value = true;
            }
            else {
                if (!is_value) {
                    if (line[i] >= '0' && line[i] <= '9') {
                        // test_value = test_value * 10 + (line[i] - '0');
                    }
                    else {
                        #ifdef LOG_ERROR_ENCONTRADO
                            printf("Error en la linea %s\n", line.c_str());
                        #endif
                    }
                    int a = 0;
                } 
                else {
                    //Si es un numero lo guardamos
                    if (line[i] >= '0' && line[i] <= '9') {
                        values[num_values-1] = values[num_values-1] * 10 + (line[i] - '0');
                    }
                    else if (line[i] == ' ') {
                        values.push_back(0);
                        num_values++;
                    }
                    else {
                        #ifdef LOG_ERROR_ENCONTRADO
                            printf("Error en la linea %s\n", line.c_str());
                        #endif
                    }
                }
            }
        }
        #ifdef LOG_OPERACIONES_BASICAS
            cout << "test_value: " << test_value << " numero de valores: " << num_values << endl;
            // printf("test_value: %llu numero de valores: %i\n", test_value, num_values);
            for (int i = 0; i < num_values; i++) {
                printf("%i ", values[i]);
            }
            printf("\n");
        #endif

        int posicion_actual = 0;
        int num_valores = values.size();
        unsigned long long subtotal = values[0];
        #ifdef LOG_CALCULOS
            printf("------------test_value: %llu numero de valores: %i\n", test_value, num_valores);
        #endif
        if (generar_operaciones(values, num_valores, posicion_actual + 1, subtotal, test_value)) {
            total+= test_value;
            #ifdef LOG_CALCULOS
                printf("Valor encontrado: %llu total: %llu\n", test_value, total);
            #endif
        }     
    } 
    
    std::cout << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;
    printf("Total operaciones validas: %llu\n", total);
    cout << "Total operaciones validas: " << total << endl;
    //SOLUCION: 97902809384118
}

bool generar_operaciones(std::vector<long> &values, int num_valores, int posicion_actual, unsigned long long subtotal, unsigned long long test_value) {
    int valor_actual = values[posicion_actual];
    unsigned long long valor = 0;

    unsigned long long subtotal_suma = subtotal + valor_actual;
    if (subtotal_suma <= test_value) {
        if (posicion_actual != num_valores - 1) {
            #ifdef LOG_CALCULOS
                printf("posicion intermedia suma: %i\n", posicion_actual);
            #endif

            bool encontrado = generar_operaciones(values, num_valores, (posicion_actual + 1), subtotal_suma, test_value);
            if (encontrado) {
                return true;
            }
        } else {
            #ifdef LOG_CALCULOS
                printf("test_value: %llu subtotal_suma: %llu\n", test_value, subtotal_suma);
            #endif
            if (test_value == subtotal_suma) {
                #ifdef LOG_CALCULOS
                    printf("Valor encontrado: %llu\n", test_value);
                #endif
                return true;
            }
        }
    }

    unsigned long long subtotal_multiplica = subtotal * valor_actual;
    if (subtotal_multiplica <= test_value) {
        if (posicion_actual != num_valores - 1) {
            #ifdef LOG_CALCULOS
                printf("posicion intermedia multiplica: %i\n", posicion_actual);
            #endif

            bool encontrado = generar_operaciones(values, num_valores, (posicion_actual + 1), subtotal_multiplica, test_value);
            if (encontrado) {
                return true;
            }
        } else {
            #ifdef LOG_CALCULOS
                printf("test_value: %llu subtotal_multiplica: %llu\n", test_value, subtotal_multiplica);
            #endif
            if (test_value == subtotal_multiplica) {
                #ifdef LOG_CALCULOS
                    printf("Valor encontrado: %llu\n", test_value);
                #endif
                return true;
            }
        }
    }

    #ifdef LOG_CALCULOS
        printf("CONCATENA subtotal: %llu valor_actual: %i\n", subtotal, valor_actual);
    #endif
    unsigned long long subtotal_concatena = std::stoull(std::to_string(subtotal) + std::to_string(valor_actual));
    if (subtotal_concatena <= test_value) {    
        if (posicion_actual != num_valores - 1) {
            #ifdef LOG_CALCULOS
                printf("posicion intermedia concatena: %i\n", posicion_actual);
            #endif

            bool encontrado = generar_operaciones(values, num_valores, (posicion_actual + 1), subtotal_concatena, test_value);
            if (encontrado) {
                return true;
            }
        } else {
            #ifdef LOG_CALCULOS
                printf("test_value: %llu subtotal_concatena: %llu\n", test_value, subtotal_concatena);
            #endif
            if (test_value == subtotal_concatena) {
                #ifdef LOG_CALCULOS
                    printf("Valor encontrado: %llu\n", test_value);
                #endif
                return true;
            }
        }
    }

    return false;
}
