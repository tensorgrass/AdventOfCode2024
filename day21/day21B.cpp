#include <iostream>     // std::cout
#include <vector>       // std::vector
#include <string>
#include <chrono>       // std::chrono
#include <cstdlib>      // std::strtoull
#include <algorithm>    // std::sort
#include <unordered_map>

using namespace std;

// #define LOG_OPERACIONES_BASICAS
// #define LOG_ERROR_ENCONTRADO
// #define LOG_INTERMEDIO
// #define LOG_CHECK
// #define LOG_COMB1
// #define LOG_COMB2
// #define LOG_COMB3


//input
#define PATH_FICHERO "input.txt"
// #define PATH_FICHERO "testA1.txt"
// #define PATH_FICHERO "testA2.txt"
// #define PATH_FICHERO "testA3.txt"
// #define PATH_FICHERO "testA4.txt"

struct BFS_Path
{
    char vecino;
    char direccion;
};

struct Path
{
    char destino;
    string camino;
};


vector<string> bfs(char start, char end, unordered_map<char, vector<BFS_Path>> &pad) {
    // start from the starting point
    vector<Path> queue = {{start, ""}};
    // take note of the shortest path length
    bool shortest_found = false;
    unsigned long long shortest = NULL;
    // store all the paths with the shortest path length
    vector<string> res;
    // while there are still paths to explore
    // for (Path camino_actual : queue) {
    for (int i = 0; i < queue.size(); i++) {
        // get the current position and the path taken to reach the position
        // if we have reached the end
        char tecla_actual = queue[i].destino;
        string camino = queue[i].camino;
        if (tecla_actual == end) {
            // if we have not found the shortest path length, set it
            if (!shortest_found) {
                shortest_found = true;
                shortest = camino.size();
            }
            // if the path length is the same as the shortest path length, add it to the result
            if (camino.size() == shortest) {
                #ifdef LOG_INTERMEDIO
                    cout << "Camino: " << camino << endl;
                #endif
                res.push_back(camino + "A");
            }
        }
        else if (!(shortest_found && camino.size() >= shortest)) {
            // add all the neighbours to the queue
            for (BFS_Path tecla_vecina : pad[tecla_actual]) {
                queue.push_back({tecla_vecina.vecino, camino + tecla_vecina.direccion});
            }
        }
        // else if we have found the shortest path length and the current path length is greater than or equal to the shortest path length, skip
    }
    #ifdef LOG_INTERMEDIO
        cout << "BFS Res: " << endl;
        for (const auto& path : res) {
            cout << path << endl;
        }
    #endif
    return res;
}

unsigned long long encontrar_camino(string &codigo, 
                                    int nivel, 
                                    bool es_numpad, 
                                    unordered_map<string, unsigned long long> &caminos, 
                                    unordered_map<char, vector<BFS_Path>> &d_pad,
                                    unordered_map<char, vector<BFS_Path>> &n_pad) {
    string key = codigo + "_" + to_string(nivel) + "_" + to_string(es_numpad);
    if (caminos.find(key) != caminos.end()) {
        return caminos[key];
    }
    unordered_map<char, vector<BFS_Path>>;
    unsigned long long res = 0;
    //we start at "A"
    char valor_actual = 'A';
    // for each character in the code
    for (char c : codigo) {
        vector<string> bfs_paths;
        //if we are using numpad, use N_PAD, otherwise use D_PAD
        #ifdef LOG_INTERMEDIO
            cout << "Codigo: " << codigo << " Nivel: " << nivel << " Valor actual: " << valor_actual << " C: " << c << endl;
        #endif
        if (es_numpad) {
            bfs_paths = bfs(valor_actual, c, n_pad);
        } else {
            bfs_paths = bfs(valor_actual, c, d_pad);
        }
        //if we are at the last level, add the minimum path length
        if (nivel == 0){
            unsigned long long min_len = 0;
            for (string path : bfs_paths) {
                if (min_len == 0 || path.size() < min_len) {
                    min_len = path.size();
                }
            }
            res += min_len;
            #ifdef LOG_INTERMEDIO
                cout << "Fin Key: " << key << " Res: " << res << endl;
            #endif
        }
        //otherwise, add the minimum path length of the next level
        else {
            unsigned long long min_len = 0;
            for (string path : bfs_paths) {
                unsigned long long camino_siguiente = encontrar_camino(path, nivel - 1, false, caminos, d_pad, n_pad);
                if (min_len == 0 || camino_siguiente < min_len) {
                    min_len = camino_siguiente;
                }
            }
            res += min_len;
            #ifdef LOG_INTERMEDIO
                cout << "Mid Key: " << key << " Res: " << res << endl;
            #endif
        }
        valor_actual = c;
    }
    caminos[key] = res;
    #ifdef LOG_INTERMEDIO
        cout << "Key: " << key << " Res: " << res << endl;
    #endif
    return res;
}

int main()
{
    auto start = std::chrono::steady_clock::now();
    freopen(PATH_FICHERO, "r", stdin);
    string line;
    unsigned long long total = 0;
    int num_lineas = 0;
    int num_columnas = 0;

    unordered_map<char, vector<BFS_Path>> n_pad = {
        {'7', {{'8', '>'}, {'4', 'v'}}},
        {'8', {{'7', '<'}, {'9', '>'}, {'5', 'v'}}},
        {'9', {{'8', '<'}, {'6', 'v'}}},
        {'4', {{'7', '^'}, {'5', '>'}, {'1', 'v'}}},
        {'5', {{'2', 'v'}, {'8', '^'}, {'6', '>'}, {'4', '<'}}},
        {'6', {{'9', '^'}, {'5', '<'}, {'3', 'v'}}},
        {'1', {{'4', '^'}, {'2', '>'}}},
        {'2', {{'1', '<'}, {'5', '^'}, {'3', '>'}, {'0', 'v'}}},
        {'3', {{'2', '<'}, {'6', '^'}, {'A', 'v'}}},
        {'0', {{'2', '^'}, {'A', '>'}}},
        {'A', {{'0', '<'}, {'3', '^'}}},
        
    };

    unordered_map<char, vector<BFS_Path>> d_pad = {
        {'^', {{'A', '>'}, {'v', 'v'}}},
        {'A', {{'^', '<'}, {'>', 'v'}}},
        {'<', {{'v', '>'}}},
        {'v', {{'<', '<'}, {'^', '^'}, {'>', '>'}}},
        {'>', {{'v', '<'}, {'A', '^'}}},
    };

    vector<string> codigos;
    unordered_map<string, unsigned long long> caminos;
    
    while(getline(cin, line))  {
        num_lineas++;
        #ifdef LOG_OPERACIONES_BASICAS
            printf("Linea %i: %s\n", num_lineas, line.c_str());
        #endif
        if (line.size() > 0) {
            codigos.push_back(line);
            int number = std::stoi(line.substr(0, line.size() - 1));
            unsigned long long path_len = encontrar_camino(line, 25, true, caminos, d_pad, n_pad);
            // unsigned long long path_len = encontrar_camino(line, 1, true, caminos, d_pad, n_pad);
            // total += path_len;
            #ifdef LOG_INTERMEDIO
                cout << "Path len: " << path_len << " Number: " << number << endl;
            #endif
            total +=  path_len * number;
        }
    }
    // cerrar el fichero
    fclose(stdin);

    std::cout << "Total: " << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;
    cout << "Total sum: " << total << endl;
    //SOLUCION: 169137886514152

}


