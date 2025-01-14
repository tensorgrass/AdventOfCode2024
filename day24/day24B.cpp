
#include <iostream>     // std::cout
#include <vector>       // std::vector
#include <string>
#include <chrono>       // std::chrono
#include <cstdlib>      // std::strtoull
#include <assert.h>
#include <unordered_map>
#include <algorithm>    // std::sort

using namespace std;

#define INPUT

// #define LOG_OPERACIONES_BASICAS
// #define LOG_INTERMEDIO
#define LOG_DOT

#define PATH_FICHERO "input.txt"
#define NUM_INPUTS 90
// #define PATH_FICHERO "testA1.txt"
// #define NUM_INPUTS 12
// #define PATH_FICHERO "testA2.txt"

// agrega una clasificación a cada puerta
// cada clasificación tiene otras clasificaciones como sus entradas esperadas
// si esas entradas no coinciden, esas entradas tienen las salidas incorrectas
// imprime una lista ordenada de todas las salidas incorrectas
// no es necesario realizar los intercambios
struct Wire {
    int inputA;
    int inputB;
    int operation;
    int state;
    int classification;
};

// wires are stored here for fast lookups
Wire wireTable[36*36*36] = {0};

// gates
enum {
    AND,
    OR,
    XOR,
    NONE
};

// classifications
enum {
    // XOR gates whose inputs are x00, y00 (part of half adder)
    XOR1,
    // XOR gate whose inputs are other inputs to the system
    XOR2,
    // other XOR gates
    XOR3,
    // AND gate whose inputs are x00, y00 (part of half adder)
    AND1,
    // AND gate whose inputs are other inputs to the system
    AND2,
    // other AND gates
    AND3,
    // any OR gate
    OR1,
    // input
    INPUT1
};

// obtiene una etiqueta de la entrada
void indexToLabel(int index, char label[4]) {
    label[0] = index/1296;
    label[1] = (index/36)%36;
    label[2] = index%36;
    for (int i = 0; i < 3; i++) {
        if (label[i] < 26) {
            label[i] += 'a';
        }
        else if (label[i] >= 26) {
            label[i] -= 26;
            label[i] += '0';
        }
    }
    label[3] = '\0';
}


// imprime una etiqueta desde el índice
void imprimeEtiqueta(int index) {
    char label[4];
    indexToLabel(index, label);
    printf("%s", label);
}

// convierte una etiqueta de 3 caracteres a un número en base 36
int labelToIndex(char* label) {
    int result = 0;
    for (int i = 0; i < 3; i++) {
        result *= 36;
        if (label[i] >= 'a' && label[i] <= 'z') {
            result += label[i] - 'a';
        }
        if (label[i] >= '0' && label[i] <= '9') {
            result += label[i] - '0' + 26;
        }
    }
    assert(result >= 0 && result < 36*36*36);
    return result;
}

// imprime un cable en una forma que coincida con input.txt
void printWire(int index) {
    Wire w = wireTable[index];
    imprimeEtiqueta(w.inputA);
    if (w.operation == OR) {
        printf(" OR ");
    }
    if (w.operation == AND) {
        printf(" AND ");
    }
    if (w.operation == XOR) {
        printf(" XOR ");
    }
    imprimeEtiqueta(w.inputB);
    printf(" -> ");
    imprimeEtiqueta(index);
    printf("\n");
}

// verifica si la lista contiene la etiqueta
int contieneEtiqueta(char list[][4], int size, char label[4]) {
    for (int i = 0; i < size; i++) {
        if (strncmp(label, list[i], 3) == 0) {
            return 1;
        }
    }
    return 0;
}

// agrega un problema a la lista de problemas si no está ya en ella
// imprime el problema solo por diversión
int addProblem(int index, char problemLabels[][4], int numProblems) {
    char label[4];
    indexToLabel(index, label);
    if (!contieneEtiqueta(problemLabels, numProblems, label)) {
        printWire(index);
        strcpy(problemLabels[numProblems++], label);
    }
    return numProblems;
}



int max(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

int comp(const void *a, const void *b) {
    return strcmp((char*)a, (char*)b);
}



int main() {
    FILE* f = fopen(PATH_FICHERO, "r");

    // lista de etiquetas de problemas
    char problemLabels[8][4] = {0};
    int numProblems = 0;

    // las salidas también se almacenan aquí para facilitar el bucle
    int outputWires[50];
    int numOutputs = 0;

    for (int i = 0; i < NUM_INPUTS; i++) {
        char label[3];
        int state = 0;
        fscanf(f, "%3c: %d ", label, &state);
        int index = labelToIndex(label);
        wireTable[index] = {-1, -1, NONE, state, INPUT1};
    }

    int wireList[300];
    int numWires = 0;

    while (!feof(f)) {
        Wire w;
        char label[4];
        char inLabelA[3];
        char inLabelB[3];
        char operationLabel[4];
        fscanf(f, "%s %s %3c -> %3c ", inLabelA, operationLabel, inLabelB, label);
        if (operationLabel[0] == 'A') {
            w.operation = AND;
        }
        else if (operationLabel[0] == 'O') {
            w.operation = OR;
        }
        else if (operationLabel[0] == 'X') {
            w.operation = XOR;
        }
        else {
            assert(0);
        }
        int index = labelToIndex(label);
        w.inputA = labelToIndex(inLabelA);
        w.inputB = labelToIndex(inLabelB);
        w.state = -1;
        // clasificar puerta por entradas
        if (w.inputA == labelToIndex("x00") || w.inputB == labelToIndex("x00")) {
            if (w.operation == XOR) {
                w.classification = XOR1;
            }
            else if (w.operation == AND) {
                w.classification = AND1;
            }
            else {
                assert(0);
            }
        }
        else if (wireTable[w.inputA].classification == INPUT1) {
            if (w.operation == XOR) {
                w.classification = XOR2;
            }
            else if (w.operation == AND) {
                w.classification = AND2;
            }
            else {
                assert(0);
            }
        }
        else {
            if (w.operation == XOR) {
                w.classification = XOR3;
            }
            else if (w.operation == AND) {
                w.classification = AND3;
            }
            else if (w.operation == OR) {
                w.classification = OR1;
            }
            else {
                assert(0);
            }
        }
        wireTable[index] = w;
        wireList[numWires++] = index;
        // output wire
        if (label[0] == 'z') {
            int zIndex = atoi(&label[1]);
            numOutputs = max(numOutputs, zIndex+1);
            outputWires[zIndex] = index;
        }
    }
    
    // verificar cables de salida
    for (int i = 0; i < numOutputs; i++) {
        Wire w = wireTable[outputWires[i]];
        if (i == 0 && w.classification == XOR1) {
            continue;
        }
        if (i == numOutputs-1 && w.classification == OR1) {
            continue;
        }
        if (w.classification == XOR3) {
            continue;
        }
        numProblems = addProblem(outputWires[i], problemLabels, numProblems);
    }
    // verificar otros cables
    for (int i = 0; i < numWires; i++) {
        Wire w = wireTable[wireList[i]];
        Wire a = wireTable[w.inputA];
        Wire b = wireTable[w.inputB];
        // INPUTS tienen que ser  XOR2 y OR1/AND1
        if (w.classification == XOR3 || w.classification == AND3) {
            if (a.classification != XOR2 && a.classification != OR1 && a.classification != AND1) {
                numProblems = addProblem(w.inputA, problemLabels, numProblems);
            }
            if (b.classification != XOR2 && b.classification != OR1 && b.classification != AND1) {
                numProblems = addProblem(w.inputB, problemLabels, numProblems);
            }
        }
        // INPUTS tienen que ser AND2 y AND3
        if (w.classification == OR1) {
            if (a.classification != AND2 && a.classification != AND3) {
                numProblems = addProblem(w.inputA, problemLabels, numProblems);
            }
            if (b.classification != AND2 && b.classification != AND3) {
                numProblems = addProblem(w.inputB, problemLabels, numProblems);
            }
        }
    }
    // ordenar e imprimir problemas
    qsort(problemLabels, numProblems, sizeof(char)*4, comp);
    for (int i = 0; i < numProblems; i++) {
        printf("%s", problemLabels[i]);
        if (i != numProblems-1) {
            printf(",");
        }
    }
    // dck,fgn,nvh,qdg,vvf,z12,z19,z37
    printf("\n");
}
