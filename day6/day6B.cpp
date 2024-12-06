#include <iostream>     // std::cout
#include <vector>       // std::vector
#include <string>
#include <algorithm>    // std::sort1

using namespace std;

// #define LOG_OPERACIONES_BASICAS
// #define LOG_RECORRIDO
// #define LOG_LOOP
// #define LOG_LOOP_VERIFICACION
// #define LOG_LOOP_VERIFICACION2
// #define LOG_LOOP_ENCONTRADO
int main()
{
    freopen("input.txt", "r", stdin);
    // freopen("testB1.txt", "r", stdin);
    string line;
    long total = 0;
    
    vector<vector<bool>> map;
    vector<vector<bool>> map_visited;

    int x_guarda_inicial = 0;
    int y_guarda_inicial = 0;    
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
                    x_guarda_inicial = x;
                    y_guarda_inicial = max_y - 1;
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


    for (int y = 0; y < max_y; y++) {
        for (int x = 0; x < max_x; x++) {
            #ifdef LOG_LOOP
                printf("Comprobando nuevo obstaculo %i, %i\n", x, y);
            #endif
            if (x != x_guarda_inicial || y != y_guarda_inicial) {
            // if (x == 6 && y == 7) {
                x_guarda = x_guarda_inicial;
                y_guarda = y_guarda_inicial;
                direccion_guarda = 0;
                bool salida = false;

                bool infinite_loop = false;
                int num_loop = 0;
                vector<int> x_loop;
                vector<int> y_loop;
                vector<int> d_loop;

                while (!salida) {
                    bool is_obstaculo = false;
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
                        else if (map[y_guarda][x_guarda] || x == x_guarda && y == y_guarda) {
                            #ifdef LOG_LOOP
                                printf("Obstaculo en %i, %i\n", x_guarda, y_guarda);
                            #endif

                            x_loop.push_back(x_guarda);
                            y_loop.push_back(y_guarda);
                            d_loop.push_back(direccion_guarda);
                            num_loop++;
                            is_obstaculo = true;

                            direccion_guarda++;
                            y_guarda++;
                        }
                        else {
                            #ifdef LOG_RECORRIDO
                                printf("Recorrido en %i, %i\n", x_guarda, y_guarda);
                            #endif
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
                        else if (map[y_guarda][x_guarda] || x == x_guarda && y == y_guarda) {
                            #ifdef LOG_LOOP
                                printf("Obstaculo en %i, %i\n", x_guarda, y_guarda);
                            #endif

                            x_loop.push_back(x_guarda);
                            y_loop.push_back(y_guarda);
                            d_loop.push_back(direccion_guarda);
                            num_loop++;
                            is_obstaculo = true;

                            direccion_guarda++;
                            x_guarda--;
                        }
                        else {
                            #ifdef LOG_RECORRIDO
                                printf("Recorrido en %i, %i\n", x_guarda, y_guarda);
                            #endif

                        }
                    }
                    else if (direccion_guarda == 2) {
                        #ifdef LOG_RECORRIDO
                            printf("Direccion S\n");
                        #endif
                        #ifdef LOG_RECORRIDO
                            //imprimir coordenadas
                            printf("Coordenadas: %i, %i\n", x_guarda, y_guarda);
                            //imprimir limintes
                            printf("Limites: %i, %i\n", map[y_guarda].size(), map.size());
                        #endif
                        y_guarda++;
                        if (y_guarda >= max_y) {
                            #ifdef LOG_RECORRIDO
                                printf("Salida en %i, %i\n", x_guarda, y_guarda);
                            #endif
                            salida = true;
                        }
                        else if (map[y_guarda][x_guarda] || x == x_guarda && y == y_guarda) {
                            #ifdef LOG_LOOP
                                printf("Obstaculo en %i, %i\n", x_guarda, y_guarda);
                            #endif

                            x_loop.push_back(x_guarda);
                            y_loop.push_back(y_guarda);
                            d_loop.push_back(direccion_guarda);
                            num_loop++;
                            is_obstaculo = true;

                            direccion_guarda++;
                            y_guarda--;
                        }
                        else {
                            #ifdef LOG_RECORRIDO
                                printf("Recorrido en %i, %i\n", x_guarda, y_guarda);
                            #endif
                        }
                    }
                    else if (direccion_guarda == 3) {
                        #ifdef LOG_RECORRIDO
                            printf("Direccion O\n");
                        #endif
                        x_guarda--;
                        if (x_guarda < 0) {
                            #ifdef LOG_RECORRIDO
                                printf("Salida en %i, %i\n", x_guarda, y_guarda);
                            #endif
                            salida = true;
                        }
                        else if (map[y_guarda][x_guarda] || x == x_guarda && y == y_guarda) {
                            #ifdef LOG_LOOP
                                printf("Obstaculo en %i, %i\n", x_guarda, y_guarda);
                            #endif

                            x_loop.push_back(x_guarda);
                            y_loop.push_back(y_guarda);
                            d_loop.push_back(direccion_guarda);
                            num_loop++;
                            is_obstaculo = true;

                            direccion_guarda = 0;
                            x_guarda++;
                        }
                        else {
                            #ifdef LOG_RECORRIDO
                                printf("Recorrido en %i, %i\n", x_guarda, y_guarda);
                            #endif
                        }
                    }
                    if (is_obstaculo) {
                        for (int i = 0; i < num_loop - 1; i++) {
                            if (x_loop[i] == x_loop[num_loop - 1] &&  y_loop[i] == y_loop[num_loop - 1] && d_loop[i] == d_loop[num_loop - 1]) {
                                salida = true;
                                infinite_loop = true;
                                #ifdef LOG_LOOP_VERIFICACION
                                    printf("Loop encontrado en %i, %i\n", x_guarda, y_guarda);
                                #endif
                                break;
                            }
                        }
                        
                    } 
                }
                if (infinite_loop) {
                    #ifdef LOG_LOOP_ENCONTRADO
                        printf("Infinite loop en %i, %i\n", x, y);
                    #endif
                    total++;
                    #ifdef LOG_LOOP_ENCONTRADO
                        printf("Total infinite loops encontrados: %d\n", total);
                    #endif
                }
                else {
                    #ifdef LOG_LOOP
                        printf("Sin loop en %i, %i\n", x, y);
                    #endif
                }
                    
            }
        }
    }
    

    printf("Total infinite loops encontrados: %d\n", total);
    //SOLUCION: 
}

