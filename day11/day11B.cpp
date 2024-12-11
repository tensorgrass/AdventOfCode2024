#include <iostream>     // std::cout
#include <vector>       // std::vector
#include <string>
#include <chrono>       // std::chrono
#include <cstdlib>      // std::strtoull
#include <unordered_map>

using namespace std;

// #define LOG_OPERACIONES_BASICAS
// #define LOG_PARCIAL
// #define LOG_CALCULOS
// #define LOG_TOTAL
// #define LOG_VALORES_SUPERIORES

#define PATH_FICHERO "input.txt"
// #define PATH_FICHERO "testB1.txt"


// #define PROFUNDIDAD 25
#define PROFUNDIDAD 75

void inicializacion_cache(int profundidad, std::vector<std::unordered_map<std::string, unsigned long long>> &cache_valores)
{
    for (int i = 0; i <= profundidad; i++)
    {
        unordered_map<string, unsigned long long> cache;
        cache_valores.push_back(cache);
    }
}

unsigned long long calcula_operacion(std::string valor, int num_iter, std::vector<std::unordered_map<std::string, unsigned long long>> &cache_valores) {
    unsigned long long total = 0;
    if (num_iter > 0) {

        //Si el valor es pair
        if (valor.size() % 2 == 0) {
            //dividir el valor en dos partes
            string parte1 = valor.substr(0, valor.size() / 2);
            //borrar ceros de la izquierda
            while (parte1.size() > 1 && parte1[0] == '0') {
                parte1 = parte1.substr(1, parte1.size());
            }
            string parte2 = valor.substr(valor.size() / 2, valor.size());
            //borrar ceros de la izquierda
            while (parte2.size() > 1 && parte2[0] == '0') {
                parte2 = parte2.substr(1, parte2.size());
            }
            // mira si parte1 existe en el hasmap de cache_valores[num_iter]
            // si existe suma el valor del hashmap
            // sino llama a calcula_operacion y guarda el valor en el hashmap
            if (cache_valores[num_iter].find(parte1) != cache_valores[num_iter].end()) {
                total += cache_valores[num_iter][parte1];
            } else {
                unsigned long long total_itermedio = calcula_operacion(parte1, num_iter - 1, cache_valores);
                total += total_itermedio;
                cache_valores[num_iter][parte1] = total_itermedio;
            }
            //lo mismo para parte2
            if (cache_valores[num_iter].find(parte2) != cache_valores[num_iter].end()) {
                total += cache_valores[num_iter][parte2];
            } else {
                unsigned long long total_itermedio = calcula_operacion(parte2, num_iter - 1, cache_valores);
                total += total_itermedio;
                cache_valores[num_iter][parte2] = total_itermedio;
            }

            #ifdef LOG_CALCULOS
                cout << "SPLIT Parte1: " << parte1 << " Parte2: " << parte2 << endl;
            #endif
        } 
        else if (std::strtoull(valor.c_str(), NULL, 10) == 0) {
            // mira si "1" existe en el hasmap de cache_valores[num_iter]
            // si existe suma el valor del hashmap
            // sino llama a calcula_operacion y guarda el valor en el hashmap
            if (cache_valores[num_iter].find("1") != cache_valores[num_iter].end()) {
                total += cache_valores[num_iter]["1"];
            } else {
                unsigned long long total_itermedio = calcula_operacion("1", num_iter - 1, cache_valores);
                total += total_itermedio;
                cache_valores[num_iter]["1"] = total_itermedio;
            }
            #ifdef LOG_CALCULOS
                cout << "Cambio 0 por 1" << endl; 
            #endif
        }
        else {
            unsigned long long val_int = std::strtoull(valor.c_str(), NULL, 10) * 2024;
            string val_str = to_string(val_int);

            // mira si val_str existe en el hasmap de cache_valores[num_iter]
            // si existe suma el valor del hashmap
            // sino llama a calcula_operacion y guarda el valor en el hashmap
            if (cache_valores[num_iter].find(val_str) != cache_valores[num_iter].end()) {
                total += cache_valores[num_iter][val_str];
            } else {
                unsigned long long total_itermedio = calcula_operacion(val_str, num_iter - 1, cache_valores);
                total += total_itermedio;
                cache_valores[num_iter][val_str] = total_itermedio;
            }
            #ifdef LOG_CALCULOS
                cout << "Multiplicacion por 2024: " << val_str << endl;
            #endif
        }
    }
    else {
        total = 1;
    }

    #ifdef LOG_TOTAL
        cout << "Total parcial: " << total << endl;
    #endif
    return total;
}

int main()
{
    auto start = std::chrono::steady_clock::now();
    freopen(PATH_FICHERO, "r", stdin);
    string line;
    unsigned long long total = 0;
    int num_lines = 0;
    int num_columns = 0;
    vector<string> mapa_inicial;

    while(getline(cin, line))  {
        num_lines++;
        #ifdef LOG_OPERACIONES_BASICAS
            printf("Linea %i: %s\n", num_lines, line.c_str());
        #endif
        string numero_intermedio = "";
        for (int i = 0; i < line.size(); i++) {
            if (line[i] >= '0' && line[i] <= '9') {
                #ifdef LOG_OPERACIONES_BASICAS
                    printf("Numero: %c\n", line[i]);
                #endif
                numero_intermedio = numero_intermedio + line[i];

            } else {
                #ifdef LOG_OPERACIONES_BASICAS
                    cout << "Numero intermedio: " << numero_intermedio << endl;
                #endif
                mapa_inicial.push_back(numero_intermedio);
                numero_intermedio = "";
                num_columns++;
                #ifdef LOG_OPERACIONES_BASICAS
                    printf("Espacio: %c\n", line[i]);
                #endif
            }
        }
        #ifdef LOG_OPERACIONES_BASICAS
            cout << "Numero intermedio: " << numero_intermedio << endl;
        #endif
        mapa_inicial.push_back(numero_intermedio);
        num_columns++;
    }
    // cerrar el fichero
    fclose(stdin);

    std::cout << "Lectura fichero: " << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;
    #ifdef LOG_OPERACIONES_BASICAS
        printf("Numero de lineas: %i Numero de columnas: %i, registro en mapa_inicial %d\n", num_lines, num_columns, mapa_inicial.size());
        
        for (int i = 0; i < num_columns; i++) {
            cout << mapa_inicial[i] << " ";
        }
        printf("\n");
    #endif

    #ifdef LOG_PARCIAL
        for (int i = 0; i < mapa_inicial.size(); i++) {
            cout << mapa_inicial[i] << " ";
        }
        cout << endl;
    #endif
    try {
        vector<unordered_map<string, unsigned long long>> cache_valores;
        for (int i = 0; i <= PROFUNDIDAD; i++)
        {
            unordered_map<string, unsigned long long> cache;
            cache_valores.push_back(cache);
        }

        for (int i = 0; i < mapa_inicial.size(); i++) {
            #ifdef LOG_VALORES_SUPERIORES
                cout << "inicio de: " << mapa_inicial[i] << endl;
            #endif
            total += calcula_operacion(mapa_inicial[i], PROFUNDIDAD, cache_valores);
            #ifdef LOG_VALORES_SUPERIORES
                cout << "fin de: " << mapa_inicial[i] << endl;
            #endif
        }

        
    } catch (exception& e) {    
        cout << "Error: " << e.what() << endl;
    }
        
    std::cout << "Total: " << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;
    cout << "Total numbers: " << total << endl;
    //SOLUCION: 240954878211138

}


