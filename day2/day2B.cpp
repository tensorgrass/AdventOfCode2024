#include <iostream>     // std::cout
#include <vector>       // std::vector
#include <string>
#include <algorithm>    // std::sort1

using namespace std;

#define LOG_LINEAS_INICIALES
#define LOG_LINEAS_CORRECTAS
#define LOG_LINEAS_INCORRECTAS
#define LOG_LINEAS_INCORRECTAS_FINAL


int main()
{
    // Lee el fichero input.txt
    freopen("input.txt", "r", stdin);
    // freopen("error6.txt", "r", stdin);
    int num_linea = 0;
    string line;
    int valid = 0;

    while(getline(cin, line))
    {
        #ifdef LOG_LINEAS_INICIALES
            printf("Inicio linea %d: %s\n", num_linea, line.c_str());
        #endif
        num_linea++;
        vector<int> numbers_original;

        string temp = "";
        for (int i = 0; i < line.size(); i++) {
            if (line[i] == ' ') {
                numbers_original.push_back(stoi(temp));
                temp = "";
            }
            else {
                temp += line[i];
            }
        }
        numbers_original.push_back(stoi(temp));
        #ifdef LOG_LINEAS_CORRECTAS
            printf("Numero a convertidos: ");
            for (int i = 0; i < numbers_original.size(); i++)
            {
                printf("%d ", numbers_original[i]);
            }
            printf("\n");
        #endif

        bool linea_correcta = false;
        for (int i = 0; i < numbers_original.size() && !linea_correcta; i++) {
            vector<int> numbers;
            bool linea_incrementando = true;
            bool linea_decrementando = true;
            for (int j = 0; j < numbers_original.size(); j++) {
                if (j != i) {
                    numbers.push_back(numbers_original[j]);
                }
            }
            #ifdef LOG_LINEAS_INICIALES
                for (int i = 0; i < numbers.size(); i++)
                {
                    printf("%d ", numbers[i]);
                }
                printf("\n");
            #endif

            for(int i = 0; i < numbers.size() - 1; i++) {
                if(numbers[i] >= numbers[i + 1]) {
                    linea_incrementando = false;
                    #ifdef LOG_LINEAS_INCORRECTAS
                        printf("ERROR linea no incrementa. %i %i\n", numbers[i], numbers[i + 1]);
                    #endif
                    break;
                }
            }
            #ifdef LOG_LINEAS_CORRECTAS
                if (linea_incrementando){
                    printf("linea %d: incrementando\n", num_linea);
                }
            #endif

            for(int i = 0; i < numbers.size() - 1; i++) {
                if(numbers[i] <= numbers[i + 1]) {
                    linea_decrementando = false;
                    #ifdef LOG_LINEAS_INCORRECTAS
                        printf("ERROR linea no decrementa. %i %i\n", numbers[i], numbers[i + 1]);
                    #endif
                    break;
                }
            }
            #ifdef LOG_LINEAS_CORRECTAS
                if (linea_decrementando){
                    printf("linea %d: decrementando\n", num_linea);
                }
            #endif

            if (!linea_incrementando && !linea_decrementando) {
                #ifdef LOG_LINEAS_INCORRECTAS
                    printf("ERROR linea no incrementa ni decrementa\n");
                #endif
            }
            else {
                bool linea_incremento_progresivo = true;
                for(int i = 0; i < numbers.size() - 1; i++)
                {
                    if(linea_incrementando && (numbers[i + 1] - numbers[i]) > 3) {
                        #ifdef LOG_LINEAS_INCORRECTAS
                            printf("ERROR linea incrementa mas de 3. %i - %i = %i\n", numbers[i + 1], numbers[i], numbers[i + 1] - numbers[i]);
                        #endif
                        linea_incremento_progresivo = false;
                        break;
                    }
                    if(linea_decrementando && (numbers[i] - numbers[i + 1]) > 3) {
                        #ifdef LOG_LINEAS_INCORRECTAS
                            printf("ERROR linea decrementa mas de 3. %i - %i = %i\n", numbers[i], numbers[i + 1], numbers[i] - numbers[i + 1]);
                        #endif
                        linea_incremento_progresivo = false;
                        break;
                    }
                }
                if (linea_incremento_progresivo) {
                    #ifdef LOG_LINEAS_CORRECTAS
                        printf("linea %d: incremento progresivo\n", num_linea);
                    #endif
                    valid++;
                    linea_correcta = true;
                }
            }
        }
        if (!linea_correcta) {
            #ifdef LOG_LINEAS_INCORRECTAS_FINAL
                for (int i = 0; i < numbers_original.size(); i++)
                {
                    printf("%d ", numbers_original[i]);
                }
                printf("\n");
            #endif
        }
    }
    //cerrar el archivo
    fclose(stdin);
    
    printf("Numero de lineas validas con safe: %d\n", valid);
    //SOLUCION 689
}