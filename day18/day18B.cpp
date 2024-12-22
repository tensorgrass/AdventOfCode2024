#include <iostream>     // std::cout
#include <vector>       // std::vector
#include <string>
#include <chrono>       // std::chrono
#include <cstdlib>      // std::strtoull


using namespace std;

// #define LOG_OPERACIONES_BASICAS
// #define LOG_ERROR_ENCONTRADO
// #define LOG_INTERMEDIO
// #define LOG_CHECK

//input
#define NUM_BYTES 1024
#define MAPA_SIZE 71
#define PATH_FICHERO "input.txt"

// #define MAPA_SIZE 7
// #define NUM_BYTES 12
// #define PATH_FICHERO "testA1.txt"
// #define PATH_FICHERO "testB1.txt"

int busca_camino(vector<vector<bool>> &mapa, int f, int c, vector<vector<bool>> camino, int &num_filas, int &num_columnas, vector<vector<vector<int>>> &cache, int direccion) {
    #ifdef LOG_CHECK
        cout << "Buscando camino en " << f << ", " << c << endl;
    #endif
    if (f < 0 || f >= MAPA_SIZE || c < 0 || c >= MAPA_SIZE || mapa[f][c] || camino[f][c]) {
        #ifdef LOG_CHECK
            cout << "No se puede ir a " << f << ", " << c << endl;
        #endif
        return 0;
    }
    // if (f == num_filas - 1 && c == num_columnas - 1) {
    if (f == 0 && c == 0) {
        #ifdef LOG_INTERMEDIO
            cout << "Camino encontrado:" << endl;
            for (int i = 0; i < MAPA_SIZE; ++i) {
                for (int j = 0; j < MAPA_SIZE; ++j) {
                    cout << (camino[i][j] ? 'O' : '.') << " ";
                }
                cout << endl;
            }
        #endif
        return 1;
    }
    camino[f][c] = true;
    if (cache[f][c][direccion] != -1) {
        return cache[f][c][direccion];
    }


    int f_siguiente = f;
    int c_siguiente = c + 1;
    int num_pasos = 0;
    int num_pasos_tmp = 0;
    num_pasos_tmp = busca_camino(mapa, f_siguiente, c_siguiente, camino, num_filas, num_columnas, cache, 0);
    if (num_pasos_tmp > 0) {
        cache[f][c][direccion] = num_pasos_tmp + 1;
        return num_pasos_tmp + 1;
    }
    f_siguiente = f + 1;
    c_siguiente = c;
    num_pasos_tmp = 0;
    num_pasos_tmp = busca_camino(mapa, f_siguiente, c_siguiente, camino, num_filas, num_columnas, cache, 1);
    if (num_pasos_tmp > 0 && (num_pasos_tmp < num_pasos || num_pasos == 0)) {
        cache[f][c][direccion] = num_pasos_tmp + 1;
        return num_pasos_tmp + 1;
    }
    f_siguiente = f;
    c_siguiente = c - 1;
    num_pasos_tmp = 0;
    num_pasos_tmp = busca_camino(mapa, f_siguiente, c_siguiente, camino, num_filas, num_columnas, cache, 2);
    if (num_pasos_tmp > 0 && (num_pasos_tmp < num_pasos || num_pasos == 0)) {
        cache[f][c][direccion] = num_pasos_tmp + 1;
        return num_pasos_tmp + 1;
    }
    f_siguiente = f - 1;
    c_siguiente = c;
    num_pasos_tmp = 0;
    num_pasos_tmp = busca_camino(mapa, f_siguiente, c_siguiente, camino, num_filas, num_columnas, cache, 3);
    if (num_pasos_tmp > 0 && (num_pasos_tmp < num_pasos || num_pasos == 0)) {
        cache[f][c][direccion] = num_pasos_tmp + 1;
        return num_pasos_tmp + 1;
    }
    cache[f][c][direccion] = 0;
    return 0;
}

int main()
{
    auto start = std::chrono::steady_clock::now();
    freopen(PATH_FICHERO, "r", stdin);
    string line;
    unsigned long long total = 0;
    int num_filas = 0;
    int num_columnas = 2;
    vector<vector<string>> numeros_str;
    

    while(getline(cin, line))  {
        num_filas++;
        #ifdef LOG_OPERACIONES_BASICAS
            printf("Linea %i: %s\n", num_filas, line.c_str());
        #endif
        int num_numero = -1;
        bool is_numero = false;
        vector<string> numeros_fila;
        for (char c : line){
            //si es un numero
            if (c == '-' || (c >= '0' && c <= '9')){
                if (!is_numero) {
                    numeros_fila.push_back(std::string(1, c));
                    is_numero = true;
                    num_numero++;
                }
                else {
                    numeros_fila[num_numero] += c;
                }
            }
            else if (c == ',') {
                is_numero = false;
            }
        }
        numeros_str.push_back(numeros_fila);
    }
    // cerrar el fichero
    fclose(stdin);
    std::cout << "Lectura fichero: " << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;
    
    vector<vector<int>> coordenadas(num_filas, vector<int>(num_columnas, 0));
    vector<vector<bool>> mapa(MAPA_SIZE, vector<bool>(MAPA_SIZE, false));
    int bit = 0;
    for (int i = 0; i < numeros_str.size(); ++i) {
        bit++;
        int fila = stoi(numeros_str[i][1]);
        int columna = stoi(numeros_str[i][0]);
        cout << bit << " Fila: " << fila << " Columna: " << columna << endl;
        string coordenada_bloqueo = numeros_str[i][0] + "," + numeros_str[i][1];
        coordenadas[i][0] = fila;
        coordenadas[i][1] = columna;
        mapa[fila][columna] = true;


        #ifdef LOG_OPERACIONES_BASICAS
            cout << "Numero de filas: " << num_filas << " Numero de columnas: " << num_columnas << endl;
            for (vector<int> coordenadas_fila : coordenadas) {
                for (int numero : coordenadas_fila) {
                    cout << numero << " ";
                }
                cout << endl;
            }
            cout << "Mapa:" << endl;
            for (int i = 0; i < MAPA_SIZE; ++i) {
                for (int j = 0; j < MAPA_SIZE; ++j) {
                    cout << (mapa[i][j] ? '#' : '.') << " ";
                }
                cout << endl;
            }
        #endif

        vector<vector<bool>> camino(MAPA_SIZE, vector<bool>(MAPA_SIZE, false));
        vector<vector<vector<int>>> cache(MAPA_SIZE, vector<vector<int>>(MAPA_SIZE, vector<int>(4, -1)));
        int map_fila = MAPA_SIZE - 1;
        int map_columna = MAPA_SIZE - 1;
        int mapa_filas = MAPA_SIZE;
        int mapa_columnas = MAPA_SIZE;
        int direccion = 0;
        total = busca_camino(mapa, map_fila, map_columna, camino, mapa_filas, mapa_columnas, cache, direccion);
        if (total == 0) {
            cout << "No se ha encontrado camino por coordenada: " << coordenada_bloqueo << endl;
            break;
        }
    }

    std::cout << "Total: " << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;
    cout << "Total pasos camino: " << total << endl;
    //SOLUCION: 24,30
}


