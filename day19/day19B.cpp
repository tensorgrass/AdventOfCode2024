#include <iostream>     // std::cout
#include <vector>       // std::vector
#include <string>
#include <chrono>       // std::chrono
#include <cstdlib>      // std::strtoull
#include <algorithm>    // std::sort
#include <unordered_map>


using namespace std;

struct Respuesta {
    bool encontrado;
    bool con_aciertos;
    int patron_size;
};

#define LOG_OPERACIONES_BASICAS
// #define LOG_ERROR_ENCONTRADO
// #define LOG_INTERMEDIO
#define LOG_CHECK

//input
#define PATH_FICHERO "input.txt"
// #define PATH_FICHERO "testA1.txt"
// #define PATH_FICHERO "testA2.txt"



unsigned long long revisar_disenyo(string disenyo, vector<string> &patrones, int patrones_size, unordered_map<string, unsigned long long> &cache) {
    if (disenyo.size() == 0) {
        return 1;
    }

    if (cache.find(disenyo) != cache.end()) {
        return cache[disenyo];
    }

    unsigned long long subtotal = 0;
    for (string patron : patrones) {
        if (disenyo.find(patron) == 0) {
            string remaining_disenyo = disenyo.substr(patron.size());
            subtotal += revisar_disenyo(remaining_disenyo, patrones, patrones_size, cache);
        }
    }
    cache[disenyo] = subtotal;
    return subtotal;
}
    

int main() {
    auto start = std::chrono::steady_clock::now();
    freopen(PATH_FICHERO, "r", stdin);
    string line;
    unsigned long long total = 0;
    int num_lineas = 0;
    int num_patrones = 1;
    int num_disenyos = 0;


    vector<string> patrones;
    vector<string> disenyos;
    

    while(getline(cin, line))  {
        num_lineas++;
        #ifdef LOG_OPERACIONES_BASICAS
            printf("Linea %i: %s\n", num_lineas, line.c_str());
        #endif
        if (num_lineas == 1) {
            for (char c : line) {

                if (c == ',' ) {
                    num_patrones++;
                }
                else if (c == ' ') {
                    //no hacemos nada
                }
                else {
                    if (patrones.size() < num_patrones) {
                        patrones.push_back(string(1, c));
                    }
                    else {
                        patrones[num_patrones - 1] += c;
                    }
                }
            }
        }
        else if (num_lineas > 2) {
            num_disenyos++;
            disenyos.push_back(line);
        }  
    }
    num_disenyos--;
    // cerrar el fichero
    fclose(stdin);
    std::cout << "Lectura fichero: " << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;

    bool todo_ordenador = false;
    while (!todo_ordenador) {
        todo_ordenador = true;
        for (int i = 0; i < patrones.size() - 1; i++) {
            if (patrones[i].size() < patrones[i+1].size()) {
                string temp = patrones[i];
                patrones[i] = patrones[i+1];
                patrones[i+1] = temp;
                todo_ordenador = false;
            }
        }
    }

    #ifdef LOG_OPERACIONES_BASICAS
        std::cout << "Patrones: " << num_patrones << std::endl;
        for (string patron : patrones) {
            std::cout << patron << ",";
        }
        cout << std::endl;

        std::cout << "Disenyos:" << num_disenyos << std::endl;
        for (string diseny : disenyos) {
            std::cout << diseny << std::endl;
        }
    #endif



    unordered_map<string, unsigned long long> cache;
    int patrones_size = patrones.size();

    try {
        for (string disenyo : disenyos) {
            #ifdef LOG_CHECK
                cout << "Disenyo: " << disenyo << endl;
            #endif
            total += revisar_disenyo(disenyo, patrones, patrones_size, cache);
            #ifdef LOG_CHECK
                cout << "Total: " << total << endl;
            #endif
        }
    }
    catch (exception e) {
        cout << "Error: " << e.what() << endl;
    }

    std::cout << "Total: " << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;
    cout << "Total diseños correctos: " << total << endl;
    //SOLUCION: 571894474468161
}

