#include <iostream>     // std::cout
#include <vector>       // std::vector
#include <string>
#include <algorithm>    // std::sort1

using namespace std;

#define LOG_OPERACIONES_BASICAS
#define LOG_LINEAS_INCORRECTAS

int main()
{
    freopen("input.txt", "r", stdin);
    // freopen("error1.txt", "r", stdin);
    string line;
    int total = 0;
    bool enable = true;

    while(getline(cin, line)) {
        #ifdef LOG_OPERACIONES_BASICAS
            //imprimir numero de caracteres de la linea
            printf("Numero de caracteres de la linea: %d\n", line.size());
        #endif
        int total_caracteres = line.size();
        for (int i = 0; i < total_caracteres - 3; i++) {
            int j = i;
            bool operacion_encontrada = false;
            int primer_numero = 0;
            int segundo_numero = 0;
            // mirar que el primer caracter de la linea sea "s", que el segundo sea "u", que el tercero sea "m" y que el cuarto sea "(" que el quito sea un numero, el sexto sea una "," el octabo un numero y el noveno un ")"
            #ifdef LOG_OPERACIONES_BASICAS
                printf("Operacion: %c%c%c%c\n", line[i], line[i + 1], line[i + 2], line[i + 3]);
            #endif
            if (line[j] == 'm' && line[j + 1] == 'u' && line[j + 2] == 'l' && line[j + 3] == '(') {
                #ifdef LOG_OPERACIONES_BASICAS
                    printf("Encontrado mul(\n");
                #endif
                //mirar si el i+5 elemento es un numero
                j = j + 4;
                if (j < total_caracteres && (line[j] == '0' || line[j] == '1' || line[j] == '2' || line[j] == '3' || line[j] == '4' || line[j] == '5' || line[j] == '6' || line[j] == '7' || line[j] == '8' || line[j] == '9')) {
                    primer_numero = line[j] - '0';
                    j++;
                    if (j < total_caracteres && (line[j] == '0' || line[j] == '1' || line[j] == '2' || line[j] == '3' || line[j] == '4' || line[j] == '5' || line[j] == '6' || line[j] == '7' || line[j] == '8' || line[j] == '9')) {
                        primer_numero = primer_numero * 10 + (line[j] - '0');
                        j++;
                        if (j < total_caracteres && (line[j] == '0' || line[j] == '1' || line[j] == '2' || line[j] == '3' || line[j] == '4' || line[j] == '5' || line[j] == '6' || line[j] == '7' || line[j] == '8' || line[j] == '9')) {
                            primer_numero = primer_numero * 10 + (line[j] - '0');
                            j++;
                        }
                    }

                    if (j < total_caracteres && (line[j] == ',')) {
                        j++;
                        if (j < total_caracteres && (line[j] == '0' || line[j] == '1' || line[j] == '2' || line[j] == '3' || line[j] == '4' || line[j] == '5' || line[j] == '6' || line[j] == '7' || line[j] == '8' || line[j] == '9')) {
                            segundo_numero = line[j] - '0';
                            j++;
                            if (j < total_caracteres && (line[j] == '0' || line[j] == '1' || line[j] == '2' || line[j] == '3' || line[j] == '4' || line[j] == '5' || line[j] == '6' || line[j] == '7' || line[j] == '8' || line[j] == '9')) {
                                segundo_numero = segundo_numero * 10 + (line[j] - '0');
                                j++;
                                if (j < total_caracteres && (line[j] == '0' || line[j] == '1' || line[j] == '2' || line[j] == '3' || line[j] == '4' || line[j] == '5' || line[j] == '6' || line[j] == '7' || line[j] == '8' || line[j] == '9')) {
                                    segundo_numero = segundo_numero * 10 + (line[j] - '0');
                                    j++;
                                }
                            }
                            if (j < total_caracteres && (line[j] == ')')) {
                                operacion_encontrada = true;
                            }
                        }
                    }
                }
            }
            // mira que esté la palabra "don't()"
            else if (line[j] == 'd' && line[j + 1] == 'o' && line[j + 2] == 'n' && line[j + 3] == '\'' && line[j + 4] == 't' && line[j + 5] == '(' && line[j + 6] == ')') {
                enable = false;
            }
            // mira que esté la palabra "do()"
            else if (line[j] == 'd' && line[j + 1] == 'o' && line[j + 2] == '(' && line[j + 3] == ')') {
                enable = true;
            }

            if (operacion_encontrada && enable) {
                printf("Operacion encontrada: %d * %d\n", primer_numero, segundo_numero);
                total = total + (primer_numero * segundo_numero);
            }
        }
    }
    //cerrar el fichero
    fclose(stdin);

    printf("Total: %d\n", total);
    //SOLUCION 88811886
}