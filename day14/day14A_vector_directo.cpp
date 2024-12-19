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
    vector<vector<vector<Robot>>> p_inicial(X_MAX, vector<vector<Robot>>(Y_MAX, vector<Robot>()));
    vector<vector<vector<Robot>>> p_final(X_MAX, vector<vector<Robot>>(Y_MAX, vector<Robot>()));
  
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
        p_inicial[robot.x][robot.y].push_back(robot);

        Robot robot_final({robot.num_robot, (((robot.vx * NUM_ITERACIONES ) + robot.x) % X_MAX), (((robot.vy * NUM_ITERACIONES ) + robot.y) % Y_MAX), robot.vx, robot.vy});
        #ifdef LOG_INTERMEDIO
            printf("Intermedio1 Robot %i: X: %i, %i, Y: %i, %i\n", num_lines, robot_final.x, robot_final.vx, robot_final.y, robot_final.vy);
        #endif
        if (robot_final.x < 0) {
            robot_final.x = X_MAX + robot_final.x;
        }
        if (robot_final.y < 0){ 
            robot_final.y = Y_MAX + robot_final.y;
        }
        #ifdef LOG_INTERMEDIO
            printf("Intermedio2 Robot %i: X: %i, %i, Y: %i, %i\n", num_lines, robot_final.x, robot_final.vx, robot_final.y, robot_final.vy);
        #endif

        p_final[robot_final.x][robot_final.y].push_back(robot_final);
        #ifdef LOG_INTERMEDIO
            printf("Intermedio3 Robot %i: X: %i, %i, %i, %i, %i, %i\n", num_lines, robot.vx * NUM_ITERACIONES, ((robot.vx * NUM_ITERACIONES ) + robot.x), robot_final.x, robot.vy * NUM_ITERACIONES, ((robot.vy * NUM_ITERACIONES ) + robot.y), robot_final.y);
        #endif
    }
    // cerrar el fichero
    fclose(stdin);
    std::cout << "Lectura fichero: " << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;

    #ifdef LOG_OPERACIONES_BASICAS
        for (int i = 0; i < X_MAX; i++){
            for (int j = 0; j < Y_MAX; j++){
                if (p_inicial[i][j].size() > 0){
                    printf("Posicion INICIAL %i, %i: ", i, j);
                    for (int k = 0; k < p_inicial[i][j].size(); k++){
                        printf("Robot %i: %i, %i, %i, %i ", p_inicial[i][j][k].num_robot, p_inicial[i][j][k].x, p_inicial[i][j][k].y, p_inicial[i][j][k].vx, p_inicial[i][j][k].vy);
                    }
                    printf("\n");
                }
            }
        }
    #endif

    #ifdef LOG_OPERACIONES_BASICAS
        for (int i = 0; i < X_MAX; i++){
            for (int j = 0; j < Y_MAX; j++){
                if (p_final[i][j].size() > 0){
                    printf("Posicion FINAL %i, %i: ", i, j);
                    for (int k = 0; k < p_final[i][j].size(); k++){
                        printf("Robot %i: %i, %i, %i, %i ", p_final[i][j][k].num_robot, p_final[i][j][k].x, p_final[i][j][k].y, p_final[i][j][k].vx, p_final[i][j][k].vy);
                    }
                    printf("\n");
                }
            }
        }
    #endif

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
    for (int i = 0; i < X_MAX; i++){
        for (int j = 0; j < Y_MAX; j++){
            if (p_final[i][j].size() > 0){
                num_total += p_final[i][j].size();
            }
            if (i < x_medio && j < y_medio) {
                cuadrante1 += p_final[i][j].size();
                #ifdef LOG_CUADRANTES
                    printf("Cuadrante 1: %i, %i, %i\n", i, j, p_final[i][j].size());
                #endif
            } else if (i > x_medio && j < y_medio) {
                cuadrante2 += p_final[i][j].size();
                #ifdef LOG_CUADRANTES
                    printf("Cuadrante 2: %i, %i, %i\n", i, j, p_final[i][j].size());
                #endif
            } else if (i < x_medio && j > y_medio) {
                cuadrante3 += p_final[i][j].size();
                // #ifdef LOG_CUADRANTES
                //     printf("Cuadrante 3: %i, %i, %i\n", i, j, p_final[i][j].size());
                // #endif
            } else if (i > x_medio && j > y_medio) {
                cuadrante4 += p_final[i][j].size();
                // #ifdef LOG_CUADRANTES
                //     printf("Cuadrante 4: %i, %i, %i\n", i, j, p_final[i][j].size());
                // #endif
            }
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

