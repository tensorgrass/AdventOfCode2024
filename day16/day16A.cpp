
#include <iostream>     // std::cout
#include <vector>       // std::vector
#include <string>
#include <chrono>       // std::chrono
#include <cstdlib>      // std::strtoull
#include <assert.h>

using namespace std;


#define PATH_FICHERO "input.txt"
// #define PATH_FICHERO "testA1.txt"

// calcula el resultado para la parte 1, luego usa un dfs para marcar todos los caminos posibles de la longitud mínima

enum {
    NORTE,
    ESTE,
    SUR,
    OESTE
};

struct Move {
    int r;
    int c;
    int direction;
    int score;
};

int min(int a, int b) {
    int valor_min = b;
    if (a < b) {
        valor_min = a;
    }
    return valor_min;
}

// C maneja incorrectamente el módulo con números negativos
int mod(int a, int b) {
    int resultado = a % b;
    if (resultado < 0) {
        resultado += b;
    }
    return resultado;
}

int buscaCaminos(int r, int c, int direction, int score, int destino,vector<Move> &moveQueue, vector<string> &map, vector<vector<int>> &camino_mapa, vector<vector<vector<int>>> &minDistance) {
    if (score == destino && map[r][c] == 'E') {
        camino_mapa[r][c] = 1;
        return 1;
    }
    if (score >= destino) {
        return 0;
    }
    if (map[r][c] == '#') {
        return 0;
    }
    // en Dijkstra, calculamos la puntuación mínima para una fila, columna, dirección, por lo que si estamos por encima de eso, no estamos en el mejor camino
    if (score > minDistance[r][c][direction]) {
        return 0;
    }
    minDistance[r][c][direction] = score;
    int mejor_camino = 0;
    if (direction == NORTE) {
        mejor_camino = buscaCaminos(r-1, c, direction, score+1, destino, moveQueue, map, camino_mapa, minDistance);
    }
    if (direction == ESTE) {
        mejor_camino = buscaCaminos(r, c+1, direction, score+1, destino, moveQueue, map, camino_mapa, minDistance);
    }
    if (direction == SUR) {
        mejor_camino = buscaCaminos(r+1, c, direction, score+1, destino, moveQueue, map, camino_mapa, minDistance);
    }
    if (direction == OESTE) {
        mejor_camino = buscaCaminos(r, c-1, direction, score+1, destino, moveQueue, map, camino_mapa, minDistance);
    }
    if (buscaCaminos(r, c, mod(direction+1,4), score+1000, destino, moveQueue, map, camino_mapa, minDistance)) {
        mejor_camino = 1;
    }
    if (buscaCaminos(r, c, mod(direction-1,4), score+1000, destino, moveQueue, map, camino_mapa, minDistance)) {
        mejor_camino = 1;
    }
    
    if (mejor_camino) {
        camino_mapa[r][c] = 1;
    }
    return mejor_camino;
}

void shiftUp(int index, vector<Move> &moveQueue, int &queueSize) {
    while (index > 0 && moveQueue[(index - 1) / 2].score > moveQueue[index].score) {
        Move temp = moveQueue[index];
        moveQueue[index] = moveQueue[(index - 1) / 2];
        moveQueue[(index - 1) / 2] = temp;
        index = (index-1)/2;
    }
}

void shiftDown(int index, vector<Move> &moveQueue, int &queueSize) {
    int minIndex = index;

    int left = ((2 * index) + 1);
    int right = ((2 * index) + 2);

    if (left < queueSize && moveQueue[left].score < moveQueue[minIndex].score) {
        minIndex = left;
    }
    if (right < queueSize && moveQueue[right].score < moveQueue[minIndex].score) {
        minIndex = right;
    }
    if (minIndex != index) {
        Move temp = moveQueue[index];
        moveQueue[index] = moveQueue[minIndex];
        moveQueue[minIndex] = temp;
        shiftDown(minIndex, moveQueue, queueSize);
    }
}

void insertQueue(Move m, vector<Move> &moveQueue, int &queueSize) {
    moveQueue[queueSize] = m;

    int index = queueSize;
    queueSize ++;

    shiftUp(index, moveQueue, queueSize);
}

Move popQueue(vector<Move> &moveQueue, int &queueSize) {
    Move result = moveQueue[0];

    moveQueue[0] = moveQueue[queueSize-1];
    queueSize --;

    shiftDown(0, moveQueue, queueSize);

    return result;
}


int main() {
    auto start = std::chrono::steady_clock::now();
    freopen(PATH_FICHERO, "r", stdin);
    string line;
    unsigned long long total = 0;

    // vector<vector<char>> map(MEDIDA, vector<char>(MEDIDA));
    vector<string> map;
    int lado_size = 0;

    while(getline(cin, line))  {
        lado_size++;
        #ifdef LOG_OPERACIONES_BASICAS
            printf("Linea %i: %s\n", num_lineas, line.c_str());
        #endif
        map.push_back(line);
    }
    // cerrar el fichero
    fclose(stdin);
    std::cout << "Lectura fichero: " << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;

    vector<Move> moveQueue(lado_size*lado_size*20);
    int queueSize = 0;

    vector<vector<int>> camino_mapa(lado_size, vector<int>(lado_size, 0));
    vector<vector<vector<int>>> minDistance(lado_size, vector<vector<int>>(lado_size, vector<int>(4)));

    int sr, sc;

    for (int r = 0; r < lado_size; r++) {
        for (int c = 0; c < lado_size; c++) {
            for (int d = 0; d < 4; d++) {
                minDistance[r][c][d] = INT_MAX;
            }
            if (map[r][c] == 'S') {
                sr = r;
                sc = c;
            }
        }
    }

    Move start_value = {sr, sc, ESTE, 0};
    insertQueue(start_value, moveQueue, queueSize);

    int score;
    while (queueSize != 0) {
        Move bestMove = popQueue(moveQueue, queueSize);
        int r = bestMove.r;
        int c = bestMove.c;
        int direction = bestMove.direction;
        score = bestMove.score;
        if (map[r][c] == 'E') {
            break;
        }
        if (map[r][c] == '#') {
            continue;
        }
        if (score >= minDistance[r][c][direction]) {
            continue;
        }
        minDistance[r][c][direction] = score;
        Move nextMove = {r, c, mod(direction+1,4),score+1000};
        insertQueue(nextMove, moveQueue, queueSize);
        Move nextMove2 = {r, c, mod(direction-1,4),score+1000};
        insertQueue(nextMove2, moveQueue, queueSize);
        if (direction == NORTE) {
            Move moveNord = {r-1, c, direction, score+1};
            insertQueue(moveNord, moveQueue, queueSize);
        }
        if (direction == ESTE) {
            Move moveEast = {r, c+1, direction, score+1};
            insertQueue(moveEast, moveQueue, queueSize);
        }
        if (direction == SUR) {
            Move moveSouth = {r+1, c, direction, score+1};
            insertQueue(moveSouth, moveQueue, queueSize);
        }
        if (direction == OESTE) {
            Move moveWest = {r, c-1, direction, score+1};
            insertQueue(moveWest, moveQueue, queueSize);
        }

    }
    total = score;


    std::cout << "Total: " << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;
    cout << "Numero posiciones camino: " << total << endl;
    //SOLUCION: 102460
}

