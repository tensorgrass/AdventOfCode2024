#include <iostream>     // std::cout
#include <vector>       // std::vector
#include <string>
#include <chrono>       // std::chrono
#include <cstdlib>      // std::strtoull

using namespace std;

// #define LOG_OPERACIONES_BASICAS
// #define LOG_ERROR_ENCONTRADO
// #define LOG_INTERMEDIO
#define LOG_CUADRANTES
// #define LOG_CHECK

//input
#define PATH_FICHERO "input.txt"
#define X_MAX 101
#define Y_MAX 103
#define NUM_ITERACIONES 100


//test1
// #define PATH_FICHERO "testA1.txt"
// #define X_MAX 11
// #define Y_MAX 7
// #define NUM_ITERACIONES 100

//test2
// #define PATH_FICHERO "testA2.txt"
// #define X_MAX 11
// #define Y_MAX 7
// #define NUM_ITERACIONES 3

struct Robot{
    int num_robot;
    long x;
    long y;
    int vx;
    int vy;
    long x_fin;
    long y_fin;
};

int main()
{
    auto start = std::chrono::steady_clock::now();
    freopen(PATH_FICHERO, "r", stdin);
    string line;
    unsigned long long total = 0;
    int num_lines = 0;
    int num_columns = 0;
    vector<Robot> lista_robots;

  
    while(getline(cin, line))  {
        num_lines++;
        #ifdef LOG_OPERACIONES_BASICAS
            printf("Linea %i: %s\n", num_lines, line.c_str());
        #endif
        int posicion = 0;
        Robot robot({num_lines, 0, 0, 0, 0});
        vector<string> numeros(4, "");
        int num_numero = 0;
        bool is_numero = false;
        for (char c : line){
            if (c == '-' || (c >= '0' && c <= '9')){
                numeros[num_numero] += c;
                is_numero = true;
            } else {
                if (is_numero){
                    is_numero = false;
                    num_numero++;
                }
            }
        }
        robot.x = stoll(numeros[0]);
        robot.y = stoll(numeros[1]);
        robot.vx = stoll(numeros[2]);
        robot.vy = stoll(numeros[3]);
        #ifdef LOG_CHECK
            printf("Robot %i: %i, %i, %i, %i\n", robot.num_robot, robot.x, robot.y, robot.vx, robot.vy);
        #endif
        long x_fin = ((robot.vx * NUM_ITERACIONES) + robot.x) % X_MAX;
        if (x_fin < 0) {
            x_fin = X_MAX + x_fin;
        }
        long y_fin = ((robot.vy * NUM_ITERACIONES) + robot.y) % Y_MAX;
        if (y_fin < 0) {
            y_fin = Y_MAX + y_fin;
        }
        robot.x_fin = x_fin;
        robot.y_fin = y_fin;
        lista_robots.push_back(robot);

    }
    // cerrar el fichero
    fclose(stdin);
    std::cout << "Lectura fichero: " << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;

    int x_medio = X_MAX / 2;
    int y_medio = Y_MAX / 2;
    #ifdef LOG_CUADRANTES
        printf("Medios: %i, %i\n", x_medio, y_medio);
    #endif
    int cuadrante1 = 0;
    int cuadrante2 = 0;
    int cuadrante3 = 0;
    int cuadrante4 = 0;
    int num_total = 0;
    for (Robot robot: lista_robots){
        #ifdef LOG_CUADRANTES
            printf("Robot %i: %d, %d, %d, %d, %d, %d\n", robot.num_robot, robot.x, robot.y, robot.vx, robot.vy, robot.x_fin, robot.y_fin);
        #endif
        num_total++;
        if (robot.x_fin < x_medio && robot.y_fin < y_medio) {
                cuadrante1++;
        }
        else if (robot.x_fin > x_medio && robot.y_fin < y_medio) {
                cuadrante2++;
        }
        else if (robot.x_fin < x_medio && robot.y_fin > y_medio) {
                cuadrante3++;
        }
        else if (robot.x_fin > x_medio && robot.y_fin > y_medio) {
                cuadrante4++;
        }
    }
    #ifdef LOG_CUADRANTES
        printf("Cuadrante 1: %i\n", cuadrante1);
        printf("Cuadrante 2: %i\n", cuadrante2);
        printf("Cuadrante 3: %i\n", cuadrante3);
        printf("Cuadrante 4: %i\n", cuadrante4);
        printf("Total cuadrantes: %i\n", cuadrante1 + cuadrante2 + cuadrante3 + cuadrante4);
        printf("Total: %i\n", num_total);
    #endif
    total = cuadrante1 * cuadrante2 * cuadrante3 * cuadrante4;


    std::cout << "Total: " << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;
    cout << "Total robots: " << total << endl;
    //SOLUCION: 219150360    
}


