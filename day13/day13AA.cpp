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

void obtener_valores_botones(std::string &line, long long &ax, long long &ay, int inicio);

void calcula_movimientos(long long ax, long long ay, long long bx, long long by, long long px, long long py, long long &total);

int main()
{
    auto start = std::chrono::steady_clock::now();
    freopen(PATH_FICHERO, "r", stdin);
    string line;
    long long total = 0;
    int num_lines = 0;
    int num_dato = 0;

    long long ax = 0;
    long long ay = 0;
    long long bx = 0;
    long long by = 0;
    long long px = 0;
    long long py = 0;    
    while(getline(cin, line))  {
        num_lines++;
        #ifdef LOG_OPERACIONES_BASICAS
            printf("Linea %d: %s\n", num_lines, line.c_str());
        #endif

        switch (num_dato){
            case FILA1:
                obtener_valores_botones(line, ax, ay, 12);
                #ifdef LOG_OPERACIONES_BASICAS
                    printf("A: (%l, %l)\n", ax, ay);
                #endif
                num_dato = FILA2;
                break;
            case FILA2:
                obtener_valores_botones(line, bx, by, 12);
                #ifdef LOG_OPERACIONES_BASICAS
                    printf("B: (%l, %l)\n", bx, by);
                #endif
                num_dato = FILA3;
                break;  
            case FILA3: 
                obtener_valores_botones(line, px, py, 9);
                #ifdef LOG_OPERACIONES_BASICAS
                    printf("P: (%l, %l)\n", px, py);
                #endif
                #ifdef LOG_OPERACIONES_BASICAS
                    printf("Calculando...\n");
                #endif

                calcula_movimientos(ax, ay, bx, by, px, py, total);

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

void calcula_movimientos(long long ax, long long ay, long long bx, long long by, long long px, long long py, long long &total)
{
    #ifdef LOG_INTERMEDIO
        cout << "Calculando: A: " << ax << ", " << ay << " B: " << bx << ", " << by << " P: " << px << ", " << py << endl;
    #endif
    // https://en.wikipedia.org/wiki/Cramer%27s_rule
    long long det = ax * by - bx * ay;
    long long x = (px * by - bx * py) / det;
    long long y = (ax * py - px * ay) / det;
    if(x * ax + y * bx == px && x * ay + y * by == py) {
        total += x*3 + y;
        #ifdef LOG_INTERMEDIO
            cout << "Encontrado: " << x << ", " << y << endl;
        #endif
    }
}

void obtener_valores_botones(std::string &line, long long &ax, long long &ay, int inicio)
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
