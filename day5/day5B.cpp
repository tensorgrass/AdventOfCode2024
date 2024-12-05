#include <iostream>     // std::cout
#include <vector>       // std::vector
#include <string>
#include <algorithm>    // std::sort1

using namespace std;

#define LOG_OPERACIONES_BASICAS
#define LOG_ERROR_ENCONTRADO
#define LOG_TOTAL_INTERMEDIO

int main()
{
    freopen("input.txt", "r", stdin);
    // freopen("testB1.txt", "r", stdin);
    string line;
    long total = 0;
    
    vector<vector<int>> rules;
    vector<vector<int>> pages;
    bool is_pages = false;
    while(getline(cin, line))
    {
        #ifdef LOG_OPERACIONES_BASICAS
            printf("Linea: %s\n", line.c_str());
        #endif
        int num_caracteres = line.size();
        if (num_caracteres > 0 && (line[0] == '0' || line[0] == '1' || line[0] == '2' || line[0] == '3' || line[0] == '4' || line[0] == '5' || line[0] == '6' || line[0] == '7' || line[0] == '8' || line[0] == '9')) {
            if (!is_pages) {
                vector<int> rule_numbers;
                rule_numbers.push_back(((line[0] - '0') * 10) + (line[1] - '0'));
                rule_numbers.push_back(((line[3] - '0') * 10) + (line[4] - '0'));
                #ifdef LOG_OPERACIONES_BASICAS
                    printf("Rules  %i|%i\n", rule_numbers[0], rule_numbers[1]);
                #endif
                rules.push_back(rule_numbers);
            }
            else {
                vector<int> page_numbers;
                for (int i = 0; i < num_caracteres; i += 3) {
                    page_numbers.push_back(((line[i] - '0') * 10) + (line[i + 1] - '0'));
                    #ifdef LOG_OPERACIONES_BASICAS
                        printf("Page %i,", page_numbers[page_numbers.size() - 1]);
                    #endif
                }
                printf("\n");
                pages.push_back(page_numbers);
            }
        }
        else {
            is_pages = true;
            #ifdef LOG_OPERACIONES_BASICAS
                printf("Cambio a las paginas\n");
            #endif
        }
    }
    // cerrar el fichero
    fclose(stdin);

    
    for (int i = 0; i < pages.size(); i++) {
        bool error_page = false;
        for (int j = 0; j < pages[i].size(); j++) {
            for (int k = j + 1; k < pages[i].size(); k++) {
                bool tmp_error_page = true;
                while (tmp_error_page) {
                    tmp_error_page = false;
                    for (int l = 0; l < rules.size() && !tmp_error_page; l++) {
                        if (rules[l][1] == pages[i][j] && rules[l][0] == pages[i][k]) {
                            error_page = true;
                            tmp_error_page = true;
                            #ifdef LOG_ERROR_ENCONTRADO
                                printf("Error en la pagina %i, rule %i no puede estar antes de rule %i\n", i, pages[i][j], pages[i][k]);
                            #endif
                            int valor1 = pages[i][j];
                            int valor2 = pages[i][k];
                            pages[i][j] = valor2;
                            pages[i][k] = valor1;
                        }
                    }
                }
            }
        }
        if (error_page) {
            int pagina_intermedia = pages[i][(pages[i].size()/2)];
            total += pagina_intermedia;
            #ifdef LOG_TOTAL_INTERMEDIO
                printf("La pagina %i con pagina intermedia %i con total %d\n", i, pagina_intermedia, total);
            #endif
        }
    }
        
    

    printf("Total suma paginas intermedias de actualizaciones correctas: %d\n", total);
    //SOLUCION: 4030
}

