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

#define PATH_FICHERO "input.txt"
// #define PATH_FICHERO "testB1.txt"

#define PROFUNDIDAD 25

int main()
{
    auto start = std::chrono::steady_clock::now();
    freopen(PATH_FICHERO, "r", stdin);
    string line;
    unsigned long long total = 0;
    int num_lines = 0;
    int num_columns = 0;
    vector<string> mapa;
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
                mapa.push_back(numero_intermedio);
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
        mapa.push_back(numero_intermedio);
        num_columns++;
    }
    // cerrar el fichero
    fclose(stdin);

    std::cout << "Lectura fichero: " << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;
    #ifdef LOG_OPERACIONES_BASICAS
        printf("Numero de lineas: %i Numero de columnas: %i, registro en mapa %d\n", num_lines, num_columns, mapa.size());
        
        for (int i = 0; i < num_columns; i++) {
            cout << mapa[i] << " ";
        }
        printf("\n");
    #endif

    #ifdef LOG_PARCIAL
        for (int i = 0; i < mapa.size(); i++) {
            cout << mapa[i] << " ";
        }
        cout << endl;
    #endif
    try {
        for (int iter = 0; iter < PROFUNDIDAD; iter++) {
            vector<string> mapa_siguiente;
            for (int i = 0; i < mapa.size(); i++) {
                string valor = mapa[i];

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
                    mapa_siguiente.push_back(parte1);
                    mapa_siguiente.push_back(parte2);
                    #ifdef LOG_CALCULOS
                        cout << "SPLIT Parte1: " << parte1 << " Parte2: " << parte2 << endl;
                    #endif
                } 
                else if (std::strtoull(valor.c_str(), NULL, 10) == 0) {
                    mapa_siguiente.push_back("1");
                    #ifdef LOG_CALCULOS
                        cout << "Cambio 0 por 1" << endl; 
                    #endif
                }
                else {
                    unsigned long long val_int = std::strtoull(valor.c_str(), NULL, 10) * 2024;
                    string val_str = to_string(val_int);
                    mapa_siguiente.push_back(val_str);
                    #ifdef LOG_CALCULOS
                        cout << "Multiplicacion por 2024: " << val_str << endl;
                    #endif
                }
            }
            //copiar mapa_siguiente a mapa
            total = mapa_siguiente.size();
            int mapa_size = mapa.size();
            for (int i = 0; i < total; i++) {
                if (i < mapa_size) {
                    mapa[i] = mapa_siguiente[i];
                } else {
                    mapa.push_back(mapa_siguiente[i]);
                }
            }
            #ifdef LOG_PARCIAL
                cout << "Iteracion" << iter << ": " ;
                for (int i = 0; i < mapa.size(); i++) {
                    cout << mapa[i] << " ";
                }
                cout << endl;
            #endif
        }
    } catch (exception& e) {    
        cout << "Error: " << e.what() << endl;
    }
        
    std::cout << "Total: " << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;
    cout << "Total numbers: " << total << endl;
    //SOLUCION: 203609


}
