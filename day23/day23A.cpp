
#include <iostream>     // std::cout
#include <vector>       // std::vector
#include <string>
#include <chrono>       // std::chrono
#include <cstdlib>      // std::strtoull
#include <assert.h>

using namespace std;


#define LOG_OPERACIONES_BASICAS
#define LOG_INTERMEDIO

#define PATH_FICHERO "input.txt"
// #define PATH_FICHERO "testA1.txt"

struct Conexion {
    string nodo1;
    string nodo2;
};

void busca_conexion(int i, int map_size, std::vector<Conexion> &map, std::string &nodo2, std::string &nodo3, std::vector<std::vector<std::string>> &trios, std::string &nodo1)
{
    for (int k = i; k < map_size; k++)
    {
        Conexion e = map[k];
        if ((nodo2 == e.nodo1 && nodo3 == e.nodo2) || (nodo2 == e.nodo2 && nodo3 == e.nodo1))
        {
            trios.push_back({nodo1, nodo2, nodo3});
            break;
        }
    }
}

int main()
{
    auto start = std::chrono::steady_clock::now();
    freopen(PATH_FICHERO, "r", stdin);
    string line;
    unsigned long long total = 0;

    vector<Conexion> map;
    int num_filas = 0;

    while(getline(cin, line))  {
        num_filas++;
        #ifdef LOG_OPERACIONES_BASICAS
            cout << "Linea " << num_filas << ": " << line << endl;
        #endif
        Conexion c = {line.substr(0, 2), line.substr(3, 2)};
        
        map.push_back(c);
    }
    // cerrar el fichero
    fclose(stdin);
    std::cout << "Lectura fichero: " << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;

    #ifdef LOG_OPERACIONES_BASICAS
        for (const auto& conexion : map) {
            cout << "Conexion: " << conexion.nodo1 << " - " << conexion.nodo2 << endl;
        }
    #endif

    vector<vector<string>> trios;
    int map_size = map.size();
    for (int i = 0; i < map_size; i++) {
        Conexion c = map[i];
        for (int j = i; j < map_size; j++) {
            Conexion d = map[j];
            if (c.nodo1 == d.nodo1 && c.nodo2 != d.nodo2) {
                string nodo1 = c.nodo1;
                string nodo2 = c.nodo2;
                string nodo3 = d.nodo2;
                busca_conexion(i, map_size, map, nodo2, nodo3, trios, nodo1);
            }
            if (c.nodo1 == d.nodo2 && c.nodo2 != d.nodo1) {
                string nodo1 = c.nodo1;
                string nodo2 = c.nodo2;
                string nodo3 = d.nodo1;
                busca_conexion(i, map_size, map, nodo2, nodo3, trios, nodo1);
            }
            if (c.nodo2 == d.nodo1 && c.nodo1 != d.nodo2) {
                string nodo1 = c.nodo2;
                string nodo2 = c.nodo1;
                string nodo3 = d.nodo2;
                busca_conexion(i, map_size, map, nodo2, nodo3, trios, nodo1);
            }
            if (c.nodo2 == d.nodo2 && c.nodo1 != d.nodo1) {
                string nodo1 = c.nodo2;
                string nodo2 = c.nodo1;
                string nodo3 = d.nodo1;
                busca_conexion(i, map_size, map, nodo2, nodo3, trios, nodo1);
            }
        }
    }

    #ifdef LOG_INTERMEDIO
        for (const auto& trio : trios) {
            cout << "Trio: " << trio[0] << " - " << trio[1] << " - " << trio[2] << endl;
        }
    #endif

    vector<vector<string>> trios_sin_repeticiones;
    vector<int> trios_indices_repetidos;
    for (int i = 0; i < trios.size(); i++) {
        bool repetido = false;
        for (int indice_repetido : trios_indices_repetidos) {
            if (i == indice_repetido) {
                repetido = true;
                break;
            }
        }
        if (repetido) {
            continue;
        }
        vector<string> trio_ini = trios[i];
        for (int j = i; j < trios.size(); j++) {
            vector<string> trio_fin = trios[j];
            if (   (trio_ini[0] == trio_fin[0] || trio_ini[0] == trio_fin[1] || trio_ini[0] == trio_fin[2]) 
                && (trio_ini[1] == trio_fin[0] || trio_ini[1] == trio_fin[1] || trio_ini[1] == trio_fin[2]) 
                && (trio_ini[2] == trio_fin[0] || trio_ini[2] == trio_fin[1] || trio_ini[2] == trio_fin[2])) {
                trios_indices_repetidos.push_back(j);
            }
        }
        trios_sin_repeticiones.push_back(trio_ini);
    }

    #ifdef LOG_INTERMEDIO
        for (const auto& trio : trios_sin_repeticiones) {
            cout << "Trio sin repeticiones: " << trio[0] << " - " << trio[1] << " - " << trio[2] << endl;
        }
    #endif

    for (vector<string> trio_sin_repeticion : trios_sin_repeticiones) {
        if (trio_sin_repeticion[0][0] == 't' || trio_sin_repeticion[1][0] == 't' || trio_sin_repeticion[2][0] == 't') {
            total++;
        }
    }


    std::cout << "Total: " << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;
    cout << "Numero grupos jugadores: " << total << endl;
    //SOLUCION: 1437
}


