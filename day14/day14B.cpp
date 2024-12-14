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
        
        lista_robots.push_back(robot);

    }
    // cerrar el fichero
    fclose(stdin);
    std::cout << "Lectura fichero: " << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;

    long num_iteracion = 0;
    while(1) {
        num_iteracion++;
        vector<vector<char>> arbol(Y_MAX, vector<char>(X_MAX, ' '));
        for (Robot robot : lista_robots){
            long x_fin = ((robot.vx * num_iteracion) + robot.x) % X_MAX;
            if (x_fin < 0) {
                x_fin = X_MAX + x_fin;
            }
            long y_fin = ((robot.vy * num_iteracion) + robot.y) % Y_MAX;
            if (y_fin < 0) {
                y_fin = Y_MAX + y_fin;
            }
            arbol[y_fin][x_fin] = '*';
        }
        
        int num_seguidos = 0;
        int num_seguidos_max = 0;
        bool encontrado = false;
        for (vector<char> v : arbol){
            for (char c : v){
                if (c == '*'){
                    if (encontrado){
                        num_seguidos++;
                        if (num_seguidos > num_seguidos_max){
                            num_seguidos_max = num_seguidos;
                        }
                    }
                    else {
                        encontrado = true;
                        num_seguidos = 1;
                    }
                    if (num_seguidos > 10){
                        break;
                    }
                } else {
                    encontrado = false;
                }
            }
        }

        if (num_seguidos_max >= 10){
            cout << "-------------------------- " << num_iteracion << " --------------------------" << endl;
            for (vector<char> v : arbol){
                for (char c : v){
                    cout << c;
                }
                cout << endl;
            }
            break;
        }
        // esperar un segundo
        // sleep(1);
        
    }


    std::cout << "Total: " << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;
    cout << "Total robots: " << total << endl;
    //SOLUCION: 219150360    
}


