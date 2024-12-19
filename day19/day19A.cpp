#include <iostream>     // std::cout
#include <vector>       // std::vector
#include <string>
#include <chrono>       // std::chrono
#include <cstdlib>      // std::strtoull
#include <algorithm>    // std::sort


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

bool revisar_disenyo_simple(string &disenyo, int num_posicion, vector<string> &patrones, int disenyo_size, int patrones_size);
Respuesta revisar_disenyo(string &disenyo, int num_posicion, vector<string> &patrones, int disenyo_size, int patrones_size);
    

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


    int num_disenyos_erroneos = 0;
    int num_disenyos_correctos = 0;
    try {
        for (string disenyo : disenyos) {
            #ifdef LOG_CHECK
                cout << "Disenyo: " << disenyo << endl;
            #endif
            int disenyo_size = disenyo.size();
            int patrones_size = patrones.size();
            bool disenyo_encontrado = revisar_disenyo_simple(disenyo, 0, patrones, disenyo_size, patrones_size);
            if (!disenyo_encontrado) {
                Respuesta respuesta = revisar_disenyo(disenyo, 0, patrones, disenyo_size, patrones_size);
                disenyo_encontrado = respuesta.encontrado;
            }
            if (disenyo_encontrado) {
                num_disenyos_correctos++;
                #ifdef LOG_CHECK
                    cout << "Diseño encontrado: " << disenyo << " num: " << num_disenyos_correctos << endl;
                #endif
            }
        }
    }
    catch (exception e) {
        cout << "Error: " << e.what() << endl;
    }

    total = num_disenyos_correctos;

    std::cout << "Total: " << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;
    cout << "Total diseños correctos: " << total << endl;
    //SOLUCION: 287
    //LOW 259, 258
    //284, 285
}

bool revisar_disenyo_simple(string &disenyo, int num_posicion, vector<string> &patrones, int disenyo_size, int patrones_size) {
    bool disenyo_encontrado = false;
    if (num_posicion >= disenyo_size) {
        if (num_posicion == disenyo_size) {
            return true;
        }
        else {
            cout << "ERROR ENCONTRADO: " << disenyo << " num_posicion: " << num_posicion << endl;
            return false;
        }
    }

    string patron_encontrado = "";
    for (string patron : patrones) {
        int patron_size = patron.size();
        if (num_posicion + patron_size <= disenyo_size) {
            string dis = disenyo.substr(num_posicion, patron_size);
            if (dis == patron) {
                #ifdef LOG_INTERMEDIO
                    cout << "Encontrado: " << dis << " en posicion: " << num_posicion << endl;
                #endif
                disenyo_encontrado = true;
                patron_encontrado = patron;
                if (disenyo_encontrado) {
                    break;
                }
            }
        }
    }

    if (disenyo_encontrado) {
        return revisar_disenyo_simple(disenyo, num_posicion + patron_encontrado.size(), patrones, disenyo_size, patrones_size);
    }
    else {
        return false;
    }

}

Respuesta revisar_disenyo(string &disenyo, int num_posicion, vector<string> &patrones, int disenyo_size, int patrones_size) {
    Respuesta respuesta = {false, false, 0};
    if (num_posicion >= disenyo_size) {
        if (num_posicion == disenyo_size) {
            respuesta = {true, true};
            return respuesta;
        }
        else {
            cout << "ERROR ENCONTRADO: " << disenyo << " num_posicion: " << num_posicion << endl;
            return respuesta;
        }
    }

    bool encontrado = false;
    for (string patron : patrones) {
        int patron_size = patron.size();
        if (num_posicion + patron_size <= disenyo_size) {
            string dis = disenyo.substr(num_posicion, patron_size);
            if (dis == patron) {
                #ifdef LOG_INTERMEDIO
                    cout << "Encontrado: " << dis << " en posicion: " << num_posicion << endl;
                #endif
                respuesta.con_aciertos = true;
                respuesta.patron_size = patron_size * 2;
                Respuesta respuesta_siguiente = revisar_disenyo(disenyo, num_posicion + patron_size, patrones, disenyo_size, patrones_size);
                if (respuesta_siguiente.encontrado) {
                    respuesta = {true, true};
                    break;
                }
                else {
                    if (respuesta_siguiente.con_aciertos && respuesta_siguiente.patron_size - patron_size <= 0) {
                        respuesta.patron_size = 0;
                        break;
                    }
                }
            }
        }
    }

    return respuesta;
}