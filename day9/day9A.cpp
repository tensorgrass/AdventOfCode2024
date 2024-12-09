#include <iostream>     // std::cout
#include <vector>       // std::vector
#include <string>
#include <chrono>       // std::chrono

using namespace std;

// #define LOG_OPERACIONES_BASICAS
// #define LOG_ERROR_ENCONTRADO
// #define LOG_CALCULOS
// #define LOG_ENCONTRADO
// #define LOG_PARCIAL
int main()
{
    auto start = std::chrono::steady_clock::now();
    freopen("input.txt", "r", stdin);
    // freopen("testA1.txt", "r", stdin);
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
        std::cout << "Lectura fichero: "<< std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;
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
        int last_possition = 0;
        for (int i = num_colums - 1; i >= 0; i--) {
            if (map[i] >=0) {
                for (int j = last_possition; j < i; j++) {
                    if (map[j] < 0) {
                        #ifdef LOG_CALCULOS
                            printf("Intercambio %i por %i en posicion %i\n", map[i], map[j], j);
                        #endif
                        int file_value = map[i];
                        map[j] = file_value;
                        map[i] = -1;
                        last_possition = j + 1;
                        break;
                    }
                }
            }
        }
        #ifdef LOG_CALCULOS
            for (int i = 0; i < map.size(); i++) {
                if (map[i] >= 0) {
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



    std::cout << "Total: "<< std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;
    printf("Total checksum: %llu\n", total);
    cout << "Total checksum: " << total << endl;
    //SOLUCION: 6330095022244


}

