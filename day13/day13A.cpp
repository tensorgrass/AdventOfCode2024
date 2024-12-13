#include <iostream>     // std::cout
#include <vector>       // std::vector
#include <string>
#include <chrono>       // std::chrono
#include <cstdlib>      // std::strtoull

using namespace std;

// #define LOG_OPERACIONES_BASICAS
// #define LOG_ERROR_ENCONTRADO
// #define LOG_INTERMEDIO

#define PATH_FICHERO "input.txt"
// #define PATH_FICHERO "testA1.txt"
// #define PATH_FICHERO "testA2.txt"
// #define PATH_FICHERO "testA3.txt"

#define FILA1 0
#define FILA2 1
#define FILA3 2
#define FILA4 3

void obtener_valores_botones(std::string &line, int &ax, int &ay, int inicio);

void calcula_movimientos(int ax, int ay, int px, int py, int bx, int by, unsigned long long &total);

int main()
{
    auto start = std::chrono::steady_clock::now();
    freopen(PATH_FICHERO, "r", stdin);
    string line;
    unsigned long long total = 0;
    int num_lines = 0;
    int num_dato = 0;

    int ax = 0;
    int ay = 0;
    int bx = 0;
    int by = 0;
    int px = 0;
    int py = 0;    
    while(getline(cin, line))  {
        num_lines++;
        #ifdef LOG_OPERACIONES_BASICAS
            printf("Linea %i: %s\n", num_lines, line.c_str());
        #endif

        switch (num_dato){
            case FILA1:
                obtener_valores_botones(line, ax, ay, 12);
                #ifdef LOG_OPERACIONES_BASICAS
                    printf("A: (%i, %i)\n", ax, ay);
                #endif
                num_dato = FILA2;
                break;
            case FILA2:
                obtener_valores_botones(line, bx, by, 12);
                #ifdef LOG_OPERACIONES_BASICAS
                    printf("B: (%i, %i)\n", bx, by);
                #endif
                num_dato = FILA3;
                break;  
            case FILA3: 
                obtener_valores_botones(line, px, py, 9);
                #ifdef LOG_OPERACIONES_BASICAS
                    printf("P: (%i, %i)\n", px, py);
                #endif
                #ifdef LOG_OPERACIONES_BASICAS
                    printf("Calculando...\n");
                #endif

                calcula_movimientos(ax, ay, px, py, bx, by, total);

                num_dato = FILA4;
                break;
            case FILA4:
                num_dato = FILA1;
                break;
        }
    }
    // cerrar el fichero
    fclose(stdin);

    std::cout << "Total: " << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;
    cout << "Total precio pulsaciones: " << total << endl;
    //SOLUCION: 38714
}

void calcula_movimientos(int ax, int ay, int px, int py, int bx, int by, unsigned long long &total)
{
    #ifdef LOG_INTERMEDIO
        printf("Calculando: A: %i, %i B: %i, %i P: %i, %i\n", ax, ay, bx, by, px, py);
    #endif
    int subtotal = 0;
    for (int i = 0; i < 100; i++)
    {
        int axt = ax * i;
        int ayt = ay * i;
        if (axt > px | ayt > py)
        {
            break;
        }
        for (int j = 0; j < 100; j++)
        {
            int bxt = bx * j;
            int byt = by * j;
            #ifdef LOG_INTERMEDIO2
                printf("Calculando: %i, %i valores A %i, %i valores B %i, %i\n", i, j, axt, ayt, bxt, byt);
            #endif
            if (bxt > px | byt > py | axt + bxt > px | ayt + byt > py)
            {
                break;
            }
            if (axt + bxt == px & ayt + byt == py)
            {
                #ifdef LOG_INTERMEDIO
                    printf("Encontrado: %i, %i\n", i, j);
                #endif
                int precio = i * 3 + j;
                if (subtotal == 0 || precio < subtotal)
                {
                    subtotal = precio;
                    #ifdef LOG_INTERMEDIO
                        printf("Encontrado precio minimo: %i, %i\n", i, j);
                    #endif
                }

            }
        }
    }
    total += subtotal;
}

void obtener_valores_botones(std::string &line, int &ax, int &ay, int inicio)
{
    ax = 0;
    ay = 0;
    int i = inicio;
    for (i; i < line.size(); i++)
    {
        // es un numero
        if (line[i] >= '0' && line[i] <= '9')
        {
            ax = ax * 10 + (line[i] - '0');
        }
        else
        {
            break;
        }
    }
    i += 4;
    for (i; i < line.size(); i++)
    {
        // es un numero
        if (line[i] >= '0' && line[i] <= '9')
        {
            ay = ay * 10 + (line[i] - '0');
        }
        else
        {
            break;
        }
    }
}
