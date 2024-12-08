#include <iostream>     // std::cout
#include <vector>       // std::vector
#include <string>
#include <chrono>       // std::chrono

using namespace std;

// #define LOG_OPERACIONES_BASICAS
// #define LOG_ERROR_ENCONTRADO
// #define LOG_CALCULOS
// #define LOG_ENCONTRADO
// #define LOG_ENCONTRADO_ENCONTRADO
// #define LOG_PARCIAL
int main()
{
    auto start = std::chrono::steady_clock::now();
    freopen("input.txt", "r", stdin);
    // freopen("testB3.txt", "r", stdin);
    string line;
    long total = 0;
    int num_lines = 0;
    int num_columns = 0;
    vector<vector<char>> mapa;
    vector<vector<char>> mapa_antinodos;
    vector<char> mapa_tipo;
    vector<int> mapa_y;
    vector<int> mapa_x;
    while(getline(cin, line))  {
        num_lines++;
        #ifdef LOG_OPERACIONES_BASICAS
            printf("Linea %i: %s\n", num_lines, line.c_str());
        #endif
        if (num_columns == 0) {
            num_columns = line.size();
        }
        vector<char> mapa_xp;
        vector<char> mapa_completo_xp;
        for (int i = 0; i < num_columns; i++) {
            mapa_xp.push_back(line[i]);
            mapa_completo_xp.push_back('.');
            if (line[i] != '.') {
                mapa_tipo.push_back(line[i]);
                mapa_y.push_back(num_lines-1);
                mapa_x.push_back(i);
            }
        }
        mapa.push_back(mapa_xp);
        mapa_antinodos.push_back(mapa_completo_xp);
    }
    // cerrar el fichero
    fclose(stdin);
    #ifdef LOG_OPERACIONES_BASICAS
        printf("Numero de lineas: %i Numero de columnas: %i\n", num_lines, num_columns);
        //imprimir el listado de tipos de antenas

    #endif

    for (int i = 0; i < mapa_tipo.size(); i++) {
        //convertir el int en char

        #ifdef LOG_PARCIAL
            printf("Antena %i: %c en (%i, %i)\n", i, mapa_tipo[i], mapa_y[i], mapa_x[i]);
        #endif
        for (int j = i + 1; j < mapa_tipo.size(); j++) {
            if (mapa_tipo[i] == mapa_tipo[j]) {
                if (mapa_antinodos[mapa_y[i]][mapa_x[i]] == '.') {
                    mapa_antinodos[mapa_y[i]][mapa_x[i]] = '#';
                    total++;
                }
                if (mapa_antinodos[mapa_y[j]][mapa_x[j]] == '.') {
                    mapa_antinodos[mapa_y[j]][mapa_x[j]] = '#';
                    total++;
                }


                int ydif = -(mapa_y[j] - mapa_y[i]);
                int anti_y1 = mapa_y[i];

                int xdif = 0;
                int anti_x1 = mapa_x[i];
                if (mapa_x[i] < mapa_x[j]) {
                    xdif = - (mapa_x[j] - mapa_x[i]);
                } else {
                    xdif = mapa_x[i] - mapa_x[j];
                    // anti_x1 = mapa_x[i] + (mapa_x[i] - mapa_x[j]);
                }

                bool resonancia = false;
                bool fuera = false;
                while (!fuera) {
                    anti_y1 = anti_y1 + ydif;
                    anti_x1 = anti_x1 + xdif;
                    #ifdef LOG_PARCIAL
                        printf("Antinodo1 Antena %i: %c en (%i, %i) Antena %i: %c en (%i, %i) Diferencia (%i, %i)\n", i, mapa_tipo[i], mapa_y[i], mapa_x[i], j, mapa_tipo[j], mapa_y[j], mapa_x[j], anti_y1, anti_x1);
                    #endif
                    if (anti_y1 >= 0 && anti_x1 >= 0 && anti_x1 < num_columns) {
                        resonancia = true;
                        if (mapa_antinodos[anti_y1][anti_x1] == '.') {
                            mapa_antinodos[anti_y1][anti_x1] = '#';
                            total++;
                        }
                        #ifdef LOG_ENCONTRADO
                            printf("Antinodo1 encontrado %i: %c en (%i, %i)\n", total, mapa_tipo[i], anti_y1, anti_x1);
                        #endif

                        //imprimir el mapa de antinodos 
                        #ifdef LOG_ENCONTRADO
                            for (int i = 0; i < num_lines; i++) {
                                for (int j = 0; j < num_columns; j++) {
                                    printf("%c", mapa_antinodos[i][j]);
                                }
                                printf("\n");
                            }
                        #endif
                    }
                    else {
                        fuera = true;
                    }
                }

                ydif = mapa_y[j] - mapa_y[i];
                int anti_y2 = mapa_y[j];
                int anti_x2 = mapa_x[j];
                if (mapa_x[i] < mapa_x[j]) {
                    xdif = mapa_x[j] - mapa_x[i];
                } else {
                    xdif = -(mapa_x[i] - mapa_x[j]);
                }

                fuera = false;
                while (!fuera) {
                    anti_y2 = anti_y2 + ydif;
                    anti_x2 = anti_x2 + xdif;
                    #ifdef LOG_PARCIAL
                        printf("Antinodo2 Antena %i: %c en (%i, %i) Antena %i: %c en (%i, %i) Diferencia (%i, %i)\n", i, mapa_tipo[i], mapa_y[i], mapa_x[i], j, mapa_tipo[j], mapa_y[j], mapa_x[j], anti_y2, anti_x2);
                    #endif
                    if (anti_y2 < num_lines && anti_x2 >= 0 && anti_x2 < num_columns ) {
                        resonancia = true;
                        if (mapa_antinodos[anti_y2][anti_x2] == '.') {
                            mapa_antinodos[anti_y2][anti_x2] = '#';
                            total++;
                        }
                        #ifdef LOG_ENCONTRADO
                            printf("Antinodo2 encontrado %i: %c en (%i, %i)\n", total, mapa_tipo[i], anti_y2, anti_x2);
                        #endif

                        //imprimir el mapa de antinodos 
                        #ifdef LOG_ENCONTRADO
                            for (int i = 0; i < num_lines; i++) {
                                for (int j = 0; j < num_columns; j++) {
                                    printf("%c", mapa_antinodos[i][j]);
                                }
                                printf("\n");
                            }
                        #endif
                    }
                    else {
                        fuera = true;
                    }
                }

            }
                
        }
            
    }
        
    //imprimir el mapa de antinodos 
    #ifdef LOG_ENCONTRADO_ENCONTRADO
        int total_antinodos = 0;
        for (int i = 0; i < num_lines; i++) {
            for (int j = 0; j < num_columns; j++) {
                printf("%c", mapa_antinodos[i][j]);
                if (mapa_antinodos[i][j] == '#') {
                    total_antinodos++;
                }
               
            }
            printf("\n");
        }
        printf("Total antinodos: %i\n", total_antinodos);
    #endif

    std::cout << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;
    printf("Total antinodes: %d\n", total);
    cout << "Total antinodes: " << total << endl;
    //SOLUCION: 766


}

