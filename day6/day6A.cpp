#include <iostream>     // std::cout
#include <vector>       // std::vector
#include <string>
#include <chrono>       // std::chrono

using namespace std;

// #define LOG_OPERACIONES_BASICAS
// #define LOG_ERROR_ENCONTRADO
// #define LOG_RECORRIDO
int main()
{
    auto start = std::chrono::steady_clock::now();
    freopen("input.txt", "r", stdin);
    // freopen("testA1.txt", "r", stdin);
    string line;
    long total = 0;
    
    vector<vector<bool>> map;
    vector<vector<bool>> map_visited;
    
    int x_guarda = 0;
    int y_guarda = 0;
    int direccion_guarda = 0; //0 --> N, 1 --> E, 2 --> S, 3 --> O

    int max_x = 0;
    int max_y = 0;

    int num_obstaculos = 0;

    while(getline(cin, line))
    {
        #ifdef LOG_OPERACIONES_BASICAS
            printf("Linea %i: %s\n", max_y, line.c_str());
        #endif
        if (max_x == 0) {
            max_x = line.size();
        }
        if (line.size() > 0) {
            max_y++;
            vector<bool> x_values;
            vector<bool> x_values_visited;
            for (int x = 0; x < max_x; x++) {
                x_values_visited.push_back(false);
                if (line[x] == '.') {
                    x_values.push_back(false);
                }
                else if (line[x] == '#') {
                    x_values.push_back(true);
                    num_obstaculos++;
                }
                else if (line[x] == '^') {
                    x_values.push_back(false);
                    x_guarda = x;
                    y_guarda = max_y - 1;
                }
                else {
                    #ifdef LOG_OPERACIONES_BASICAS
                        printf("Error en la linea %s\n", line.c_str());
                    #endif
                }
            }
            map.push_back(x_values);
            map_visited.push_back(x_values_visited);
        }
    }
    // cerrar el fichero
    fclose(stdin);

    #ifdef LOG_OPERACIONES_BASICAS
        printf("Guard en %i, %i\n", x_guarda, y_guarda);
        printf("Mapa de %i x %i\n", max_x, max_y);
        printf("Numero de obstaculos: %i\n", num_obstaculos);
    #endif

    bool salida = false;
    while (!salida) {
        if (direccion_guarda == 0) {
            #ifdef LOG_RECORRIDO
                printf("Direccion N\n");
            #endif
            y_guarda--;
            if (y_guarda < 0) {
                #ifdef LOG_RECORRIDO
                    printf("Salida en %i, %i\n", x_guarda, y_guarda);
                #endif
                salida = true;
            }
            else if (map[y_guarda][x_guarda]) {
                #ifdef LOG_RECORRIDO
                    printf("Obstaculo en %i, %i\n", x_guarda, y_guarda);
                #endif
                direccion_guarda++;
                y_guarda++;
            }
            else {
                #ifdef LOG_RECORRIDO
                    printf("Recorrido en %i, %i\n", x_guarda, y_guarda);
                #endif
                if (map_visited[y_guarda][x_guarda]) {
                    #ifdef LOG_RECORRIDO
                        printf("Ya visitado en %i, %i\n", x_guarda, y_guarda);
                    #endif
                }
                else {
                    map_visited[y_guarda][x_guarda] = true;
                    total++;
                }
            }
        }
        else if (direccion_guarda == 1) {
            #ifdef LOG_RECORRIDO
                printf("Direccion E\n");
            #endif
            x_guarda++;
            if (x_guarda >= max_x) {
                salida = true;
                #ifdef LOG_RECORRIDO
                    printf("Salida en %i, %i\n", x_guarda, y_guarda);
                #endif
            }
            else if (map[y_guarda][x_guarda]) {
                direccion_guarda++;
                x_guarda--;
                #ifdef LOG_RECORRIDO
                    printf("Obstaculo en %i, %i\n", x_guarda, y_guarda);
                #endif
            }
            else {
                #ifdef LOG_RECORRIDO
                    printf("Recorrido en %i, %i\n", x_guarda, y_guarda);
                #endif
                if (map_visited[y_guarda][x_guarda]) {
                    #ifdef LOG_RECORRIDO
                        printf("Ya visitado en %i, %i\n", x_guarda, y_guarda);
                    #endif
                }
                else {
                    map_visited[y_guarda][x_guarda] = true;
                    total++;
                }
            }
        }
        else if (direccion_guarda == 2) {
            #ifdef LOG_RECORRIDO
                printf("Direccion S\n");
            #endif
            y_guarda++;
            if (y_guarda >= max_y) {
                salida = true;
                #ifdef LOG_RECORRIDO
                    printf("Salida en %i, %i\n", x_guarda, y_guarda);
                #endif
            }
            else if (map[y_guarda][x_guarda]) {
                direccion_guarda++;
                y_guarda--;
                #ifdef LOG_RECORRIDO
                    printf("Obstaculo en %i, %i\n", x_guarda, y_guarda);
                #endif
            }
            else {
                #ifdef LOG_RECORRIDO
                    printf("Recorrido en %i, %i\n", x_guarda, y_guarda);
                #endif
                if (map_visited[y_guarda][x_guarda]) {
                    #ifdef LOG_RECORRIDO
                        printf("Ya visitado en %i, %i\n", x_guarda, y_guarda);
                    #endif
                }
                else {
                    map_visited[y_guarda][x_guarda] = true;
                    total++;
                }
            }
        }
        else if (direccion_guarda == 3) {
            #ifdef LOG_RECORRIDO
                printf("Direccion O\n");
            #endif
            x_guarda--;
            if (x_guarda < 0) {
                salida = true;
                #ifdef LOG_RECORRIDO
                    printf("Salida en %i, %i\n", x_guarda, y_guarda);
                #endif
            }
            else if (map[y_guarda][x_guarda]) {
                direccion_guarda = 0;
                x_guarda++;
                #ifdef LOG_RECORRIDO
                    printf("Obstaculo en %i, %i\n", x_guarda, y_guarda);
                #endif
            }
            else {
                #ifdef LOG_RECORRIDO
                    printf("Recorrido en %i, %i\n", x_guarda, y_guarda);
                #endif
                if (map_visited[y_guarda][x_guarda]) {
                    #ifdef LOG_RECORRIDO
                        printf("Ya visitado en %i, %i\n", x_guarda, y_guarda);
                    #endif
                }
                else {
                    map_visited[y_guarda][x_guarda] = true;
                    total++;
                }
            }
        }
            
    }
        
    
    std::cout << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;
    printf("Total cuadros recorridos: %d\n", total);
    //SOLUCION: 4789


}

