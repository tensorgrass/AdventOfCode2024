#include <iostream>     // std::cout
#include <vector>       // std::vector
#include <string>
#include <chrono>       // std::chrono

using namespace std;

// #define LOG_OPERACIONES_BASICAS
// #define LOG_ERROR_ENCONTRADO
// #define LOG_CALCULOS
// #define LOG_CALCULOS_INTERMEDIOS
// #define LOG_PARCIAL
int main()
{
    auto start = std::chrono::steady_clock::now();
    freopen("input.txt", "r", stdin);
    // freopen("testB1.txt", "r", stdin);
    string line;
    unsigned long long total = 0;
    int num_lines = 0;


    while(getline(cin, line))  {
        num_lines++;
        vector<int> map;
        #ifdef LOG_OPERACIONES_BASICAS
            printf("Linea %i: %s\n", num_lines, line.c_str());
        #endif
        bool is_file = true;
        int file_number = 0;
        int num_colums = 0;
        for (int i = 0; i < line.size(); i++) {
            if (is_file) {
                //char to int
                int file_size = line[i] - '0';
                for (int j = 0; j < file_size; j++) {
                    //int to char
                    map.push_back(file_number);
                    num_colums++;
                }
                file_number++;
            }
            else {
                int num_spaces = line[i] - '0';
                for (int j = 0; j < num_spaces; j++) {
                    map.push_back(-1);
                    num_colums++;
                }
            }
            is_file = !is_file;
        }
        std::cout << "Lectura fichero " << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;
        #ifdef LOG_CALCULOS
            for (int i = 0; i < map.size(); i++) {
                if (map[i] == -1) {
                    printf(".");
                }
                else {
                    printf("%i", map[i]);
                }
            }
            printf("\n");
            printf("Num colums: %i\n", num_colums);
        #endif
        int file_size_tmp = 0;
        int i_ini = 0;
        int i_fin = num_colums;
        int max_space_size = 10;
        int primer_espacio_libre = 0;
        for (int fn = file_number; fn >= 0; fn--){
            for (int i = i_fin - 1; i >=0; i--) {
                if (map[i] == fn) {
                    int i_ini = i;
                    int i_fin = i;
                    file_size_tmp = 1;
                    while (map[i-1] == fn) {
                        i--;
                        i_ini = i;
                        file_size_tmp++;
                    }
                    if (file_size_tmp <= max_space_size) {
                        max_space_size = 0;
                        bool is_primer_espacio_libre = true;
                        for (int j = is_primer_espacio_libre; j < i; j++) {
                            if (map[j] < 0) {
                                int j_ini = j;
                                int j_fin = j;
                                int space_size = 1;
                                while (map[j+1] < 0) {
                                    j++;
                                    space_size++;
                                    j_fin = j;
                                }
                                if (space_size >= file_size_tmp) {
                                    #ifdef LOG_CALCULOS
                                        printf("Intercambio %i por %i en posicion %i con espacio de %i en %i\n", map[i_ini], j_ini, j_ini, file_size_tmp, space_size);
                                    #endif

                                    for (int k = 0; k < file_size_tmp; k++) {
                                        int valor = map[i_ini + k];
                                        map[j_ini + k] = valor;
                                        map[i_ini + k] = -1;
                                    }

                                    #ifdef LOG_CALCULOS_INTERMEDIOS
                                        for (int i = 0; i < map.size(); i++) {
                                            if (map[i] < 0) {
                                                printf(".");
                                            }
                                            else {
                                                printf("%i", map[i]);
                                            }
                                        }
                                        printf("\n");
                                    #endif
                                    max_space_size = 10;
                                    break;
                                }
                                else {
                                    if (space_size > max_space_size) {
                                        max_space_size = space_size;
                                    }
                                }
                            }
                            else {
                                if (is_primer_espacio_libre) {
                                    primer_espacio_libre = j;
                                }
                                is_primer_espacio_libre = false;
                            }
                        }
                    }
                    break;
                }
            }
        }
        #ifdef LOG_CALCULOS
            for (int i = 0; i < map.size(); i++) {
                if (map[i] < 0) {
                    printf(".");
                }
                else {
                    printf("%i", map[i]);
                }
            }
            printf("\n");
        #endif
        for (int i = 0; i < map.size(); i++) {
            if (map[i] >= 0) {
                total += i * map[i];
            }

        }
    }
    // cerrar el fichero
    fclose(stdin);



    std::cout << "Total " << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;
    printf("Total checksum: %llu\n", total);
    cout << "Total checksum: " << total << endl;
    //SOLUCION: 6359491814941


}

