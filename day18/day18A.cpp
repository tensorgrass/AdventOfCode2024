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

// A utility function to find the vertex with minimum
// distance value, from the set of vertices not yet included
// in shortest path tree
int minDistance(vector<int> &dist, vector<bool> &sptSet, int graph_size) {

    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < graph_size; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// A utility function to print the constructed distance
// array
void printSolution(vector<int> &dist, int graph_size) {
    cout << "Vertex \t Distance from Source" << endl;
    for (int i = 0; i < graph_size; i++)
        cout << i << " \t\t\t\t" << dist[i] << endl;
}

// Function that implements Dijkstra's single source
// shortest path algorithm for a graph represented using
// adjacency matrix representation
int dijkstra(vector<vector<int>> &graph, int src, int graph_size)
{
    vector<int> dist(graph_size); // The output array.  dist[i] will hold the
                 // shortest
    // distance from src to i

    vector<bool> sptSet(graph_size); // sptSet[i] will be true if vertex i is
                    // included in shortest
    // path tree or shortest distance from src to i is
    // finalized

    // Initialize all distances as INFINITE and stpSet[] as
    // false
    for (int i = 0; i < graph_size; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < graph_size - 1; count++) {
        // Pick the minimum distance vertex from the set of
        // vertices not yet processed. u is always equal to
        // src in the first iteration.
        int u = minDistance(dist, sptSet, graph_size);

        // Mark the picked vertex as processed
        sptSet[u] = true;

        // Update dist value of the adjacent vertices of the
        // picked vertex.
        for (int v = 0; v < graph_size; v++)

            // Update dist[v] only if is not in sptSet,
            // there is an edge from u to v, and total
            // weight of path from src to  v through u is
            // smaller than current value of dist[v]
            if (!sptSet[v] && graph[u][v]
                && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v]) {
                int dist_u = dist[u];
                int graph_u_v = graph[u][v];
                dist[v] = dist[u] + graph[u][v];
                }
    }

    // print the constructed distance array
    printSolution(dist, graph_size);
    // return last position
    return dist[graph_size - 1];
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
    for (int i = 0; i < NUM_BYTES; ++i) {
        int fila = stoi(numeros_str[i][1]);
        int columna = stoi(numeros_str[i][0]);
        coordenadas[i][0] = fila;
        coordenadas[i][1] = columna;
        mapa[fila][columna] = true;
    }

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

    vector<vector<int>> mapa_dijkstra(MAPA_SIZE * MAPA_SIZE, vector<int>(MAPA_SIZE * MAPA_SIZE, 0));
    for (int i = 0; i < MAPA_SIZE; ++i) {
        for (int j = 0; j < MAPA_SIZE; ++j) {
            if (!mapa[i][j]) {
                for (int k = 0; k < MAPA_SIZE; ++k) {
                    for (int l = 0; l < MAPA_SIZE; ++l) {
                        if (!mapa[k][l]) {
                            if ((   (k == i + 1 && l == j)
                                 || (k == i - 1 && l == j)
                                 || (k == i && l == j + 1)
                                 || (k == i && l == j - 1))
                                && (!mapa[k][l])) {
                                    int fila_h = (i * MAPA_SIZE) + j;
                                    int columna_h = (k * MAPA_SIZE) + l;
                                    mapa_dijkstra[fila_h][columna_h] = 1;
                                    int fila_v = (k * MAPA_SIZE) + l;
                                    int columna_v = (i * MAPA_SIZE) + j;
                                    mapa_dijkstra[fila_v][columna_v] = 1;
                            }
                        }
                    }
                }
            }
        }
    }
    #ifdef LOG_OPERACIONES_BASICAS
        cout << "Mapa Dijkstra:" << endl;
        for (int i = 0; i < MAPA_SIZE * MAPA_SIZE; ++i) {
            for (int j = 0; j < MAPA_SIZE * MAPA_SIZE; ++j) {
                cout << mapa_dijkstra[i][j] << " ";
            }
            cout << endl;
        }
    #endif

    total = dijkstra(mapa_dijkstra, 0, MAPA_SIZE * MAPA_SIZE);

    std::cout << "Total: " << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;
    cout << "Total pasos camino: " << total << endl;
    //SOLUCION: 336
    //HIGH 416, 356
}


