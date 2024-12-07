#include <iostream>     // std::cout
#include <vector>       // std::vector
#include <string>
#include <chrono>       // std::chrono

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

        vector<int> operations;
        for (int i = 0; i < num_values - 1; i++) {
            operations.push_back(0);
        }
        bool final = false;
        bool encontrado = false;
        unsigned long long  tmp_test_value = 0;
        while (!final && !encontrado){
            #ifdef LOG_CALCULOS
                for (int i = 0; i < num_values - 1; i++) {
                    printf("%i ", operations[i]);
                }
                printf("\n");
            #endif
            for (int i = 0; i < num_values -1; i++) {
                if (operations[i] == 0) {
                    if (i == 0) {
                        tmp_test_value = values[i] + values[i+1];
                    }
                    else {
                        tmp_test_value = tmp_test_value + values[i+1];
                    }
                }
                else if (operations[i] == 1) {
                    if (i == 0) {
                        tmp_test_value = values[i] * values[i+1];
                    }
                    else {
                        tmp_test_value = tmp_test_value * values[i+1];
                    }
                }
                else {
                    if (i == 0) {
                        tmp_test_value = std::stoull(std::to_string(values[i]) + std::to_string(values[i+1]));
                    }
                    else {
                        tmp_test_value = std::stoull(std::to_string(tmp_test_value) + std::to_string(values[i+1]));
                    }
                }
            }
            #ifdef LOG_CALCULOS
                printf("Calculo: %llu\n", tmp_test_value);
            #endif
            if (tmp_test_value == test_value) {
                encontrado = true;
                total += test_value;
                #ifdef LOG_ENCONTRADO
                    printf("Encontrado: %llu\n", test_value);
                #endif
            }
            else {
                final = true;
                for (int i = 0; i < num_values - 1; i++) {
                    if (operations[i] != 2) {
                        final = false;
                        break;
                    }
                }
                if (final) {
                    #ifdef LOG_ENCONTRADO
                        printf("No encontrado %llu\n", test_value);
                    #endif
                }
                else {
                    for (int i = 0; i < num_values - 1; i++) {
                        if (operations[i] == 0) {
                            operations[i] = 1;
                        }
                        else if(operations[i] == 1) {
                            operations[i] = 2;
                            break;
                        }
                        else {
                            operations[i] = 0;
                        }
                    }
                }
            }
        }
    }
    // cerrar el fichero
    fclose(stdin);

        
    
    std::cout << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;
    printf("Total cuadros recorridos: %llu\n", total);
    cout << "Total cuadros recorridos: " << total << endl;
    //SOLUCION: 97902809384118


}

